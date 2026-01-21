#include "cc.h"
#include "stdio.h"
#include "stdlib.h"
#include <bench.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

int my_putchar(int c);
int my_fputc(int c, FILE *fp);
int my_fputs(const char *s, FILE *fp);
int my_puts(const char *s);
int my_printf(const char *fmt, ...);

struct value {
  enum {
    VALUE_NONE,
    VALUE_GLOBAL,
    VALUE_INTCONST,
    VALUE_FLTCONST,
    VALUE_DBLCONST,
    VALUE_TEMP,
    VALUE_TYPE,
    VALUE_LABEL,
    VALUE_STRING,

    VALUE_THREAD = 1 << 4,
  } kind;
  unsigned id;
  union {
    char *name;
    unsigned long long i;
  } u;
};

struct lvalue {
  struct value *addr;
  struct bitfield bits;
  char *asmname;
};

enum instkind {
  INONE,

#define OP(op, name) op,
#include "ops.h"
#undef OP

  IARG,
  IVARARG,
};

struct qbetype {
  char base, data;
  enum instkind load, store;
};

struct inst {
  enum instkind kind;
  int class;
  struct value res, *arg[2];
};

struct jump {
  enum {
    JUMP_NONE,
    JUMP_JMP,
    JUMP_JNZ,
    JUMP_RET,
    JUMP_HLT,
  } kind;
  struct value *arg;
  struct block *blk[2];
};

struct block {
  struct value label;
  struct array insts;
  struct {
    int class;
    struct block *blk[2];
    struct value *val[2];
    struct value res;
  } phi;
  struct jump jump;

  struct block *next;
};

struct switchcase {
  struct treenode node;
  struct block *body;
};

struct func {
  struct decl *decl, *namedecl;
  char *name;
  struct value *paramtemps;
  struct type *type;
  struct block *start, *end;
  struct map gotos;
  unsigned lastid;
};

static const int ptrclass = 'w';
static unsigned mkblock_id;
static unsigned mkglobal_id;
static unsigned emittype_id;

static char *strip_quotes(char *s);
static const char *get_ret_reg(void);
static struct lvalue funclval(struct func *f, struct expr *e);
static struct value *funcstore(struct func *f, struct type *t, enum typequal tq, struct lvalue lval, struct value *v);
struct value *funcexpr(struct func *f, struct expr *e);

void switchcase(struct switchcases *cases, unsigned long long i, struct block *b) {
  struct switchcase *c;

  c = treeinsert(&cases->root, i, sizeof(*c));
  if (!c->node.new)
    error(&tok.loc, "multiple 'case' labels with same value");
  c->body = b;
}

/* values */

struct block *mkblock(char *name) {
  struct block *b;

  b = xmalloc(sizeof(*b));
  b->label.kind = VALUE_LABEL;
  b->label.u.name = name;
  b->label.id = ++mkblock_id;
  b->insts = (struct array){0};
  b->jump.kind = JUMP_NONE;
  b->phi.res.kind = VALUE_NONE;
  b->next = NULL;

  return b;
}

struct value *mkglobal(struct decl *d) {
  struct value *v;

  v = xmalloc(sizeof(*v));
  v->kind = VALUE_GLOBAL;
  if (d->kind == DECLOBJECT && d->u.obj.storage == SDTHREAD)
    v->kind |= VALUE_THREAD;
  if (d->asmname) {
    v->u.name = d->asmname;
    v->id = 0;
  } else {
    v->u.name = d->name;
    v->id = d->linkage == LINKNONE ? ++mkglobal_id : 0;
  }

  return v;
}

struct value *mkintconst(unsigned long long n) {
  struct value *v;

  v = xmalloc(sizeof(*v));
  v->kind = VALUE_INTCONST;
  v->u.i = n;

  return v;
}

static struct value *mkstring(char *s) {
  struct value *v;

  v = xmalloc(sizeof(*v));
  v->kind = VALUE_STRING;
  v->u.name = s;

  return v;
}

static struct qbetype qbetype(struct type *t) {
  static const struct qbetype ub = {'w', 'b', ILOADUB, ISTOREB}, sb = {'w', 'b', ILOADSB, ISTOREB},
                              uh = {'w', 'h', ILOADUH, ISTOREH}, sh = {'w', 'h', ILOADSH, ISTOREH},
                              w = {'w', 'w', ILOADW, ISTOREW}, l = {'l', 'l', ILOADL, ISTOREL}, v = {0};

  if (t == &typevoid)
    return v;
  if (!(t->prop & PROPSCALAR))
    return l;
  switch (t->size) {
    case 1: return t->u.basic.issigned ? sb : ub;
    case 2: return t->u.basic.issigned ? sh : uh;
    case 4: return w;
    case 8: return l;
    case 16: fatal("int128 is not yet supported");
  }
  assert(0);
}

/* functions */

static void emittype(struct type *);
static void emitname(struct value *);
static void emitvalue(struct value *);

static void functemp(struct func *f, struct value *v) {
  v->kind = VALUE_TEMP;
  v->u.name = NULL;
  v->id = ++f->lastid;
}

static const char *const instname[] = {
#define OP(op, name) [op] = name,
#include "ops.h"
#undef OP
};

static struct inst *mkinst(struct func *f, int op, int class, struct value *arg0, struct value *arg1) {
  struct inst *inst;

  inst = xmalloc(sizeof(*inst));
  inst->kind = op;
  inst->class = class;
  inst->arg[0] = arg0;
  inst->arg[1] = arg1;
  if (class && op != IARG)
    functemp(f, &inst->res);
  else
    inst->res.kind = VALUE_NONE;
  return inst;
}

static struct value *funcinst(struct func *f, int op, int class, struct value *arg0, struct value *arg1) {
  struct inst *inst;
  struct block *b;

  if (f->end->jump.kind) {
    b = mkblock("dead");
    funclabel(f, b);
  }
  inst = mkinst(f, op, class, arg0, arg1);
  arrayaddptr(&f->end->insts, inst);
  return &inst->res;
}

static char *xstrdup(const char *s) {
  if (!s)
    return NULL;
  size_t len = strlen(s);
  char *new_s = xmalloc(len + 1);
  strcpy(new_s, s);
  return new_s;
}

static char **process_asm_string(const char *s, size_t *num_lines) {
  if (!s || *s == '\0') {
    if (num_lines)
      *num_lines = 0;
    return NULL;
  }

  char **lines_array = NULL;
  size_t lines_capacity = 4;
  size_t lines_count = 0;

  lines_array = xmalloc(lines_capacity * sizeof(char *));

  const char *current_pos = s;
  while (*current_pos != '\0') {
    const char *line_start_in_s = current_pos;
    const char *line_end_in_s = strchr(current_pos, '\n');
    size_t raw_line_len;

    if (line_end_in_s == NULL) {
      raw_line_len = strlen(current_pos);
    } else {
      raw_line_len = line_end_in_s - current_pos;
    }

    char *stripped_line_buf = xmalloc(raw_line_len + 1);
    char *d = stripped_line_buf;

    enum {
      NORMAL_STATE,
      IN_STRING_STATE,
      IN_LINE_COMMENT_STATE
    } state = NORMAL_STATE;

    for (size_t i = 0; i < raw_line_len; ++i) {
      char c = line_start_in_s[i];

      switch (state) {
        case NORMAL_STATE:
          if (c == '"') {
            state = IN_STRING_STATE;
            *d++ = c;
          } else if (i + 1 < raw_line_len && c == '/' && line_start_in_s[i + 1] == '/') { // Found // comment
            state = IN_LINE_COMMENT_STATE;
            i++;
          } else {
            *d++ = c;
          }
          break;
        case IN_STRING_STATE:
          *d++ = c;
          if (c == '\\' && i + 1 < raw_line_len) {
            *d++ = line_start_in_s[++i];
          } else if (c == '"') {
            state = NORMAL_STATE;
          }
          break;
        case IN_LINE_COMMENT_STATE: break;
      }
    }
    *d = '\0';

    char *trimmed_start = stripped_line_buf;
    while (*trimmed_start && isspace((unsigned char)*trimmed_start)) {
      trimmed_start++;
    }
    char *trimmed_end = trimmed_start + strlen(trimmed_start);
    while (trimmed_end > trimmed_start && isspace((unsigned char)trimmed_end[-1])) {
      trimmed_end--;
    }
    *trimmed_end = '\0';

    if (*trimmed_start != '\0') {
      if (lines_count == lines_capacity) {
        lines_capacity *= 2;
        lines_array = xreallocarray(lines_array, lines_capacity, sizeof(char *));
      }
      lines_array[lines_count++] = xstrdup(trimmed_start);
    }

    free(stripped_line_buf);

    if (line_end_in_s == NULL) {
      break;
    } else {
      current_pos = line_end_in_s + 1;
    }
  }

  if (num_lines)
    *num_lines = lines_count;

  if (lines_count == 0) {
    free(lines_array);
    return NULL;
  }
  lines_array = xreallocarray(lines_array, lines_count, sizeof(char *));
  return lines_array;
}

static const char *get_ret_reg(void) {
  if (strcmp(targ->name, "x86_64-sysv") == 0)
    return "%rax";
  if (strcmp(targ->name, "aarch64") == 0)
    return "x0";
  if (strncmp(targ->name, "riscv", 5) == 0)
    return "a0";
  return "unknown_reg";
}

static const char *get_arg_reg(int i) {
  static char buf[4];
  if (i >= 0 && i < 8) {
    snprintf(buf, sizeof(buf), "a%d", i);
    return buf;
  }
  return "UNKNOWN";
}

static char *get_asmname(struct expr *e) {
  while (e->kind == EXPRCAST)
    e = e->base;
  if (e->kind == EXPRIDENT && e->u.ident.decl)
    return e->u.ident.decl->asmname;
  return NULL;
}

void funcasm(struct func *f, char *s, struct asm_operand *outputs, struct asm_operand *inputs,
             struct asm_operand *clobbers) {
  if (!outputs && !inputs && !clobbers) {
    size_t num_lines;
    char **asm_lines = process_asm_string(s, &num_lines);

    for (size_t i = 0; i < num_lines; ++i) {
      funcinst(f, IASM, 0, mkstring(asm_lines[i]), NULL);
    }

    if (asm_lines) {
      free(asm_lines);
    }
    return;
  }

  if (outputs && outputs->next)
    error(NULL, "multiple outputs in asm not supported");

  int n_outputs = (outputs != NULL);
  struct array pre = {0}, post = {0};

  int i = 0;
  for (struct asm_operand *op = inputs; op; op = op->next) {
    char *reg = get_asmname(op->expr);
    if (reg) {
      char *rname = reg;
      size_t len = strlen(reg);
      if (len >= 2 && reg[0] == '"' && reg[len - 1] == '"') {
        rname = xmalloc(len - 1);
        memcpy(rname, reg + 1, len - 2);
        rname[len - 2] = '\0';
      }

      char buf[64];
      snprintf(buf, sizeof(buf), "mv %s, %s; ", rname, get_arg_reg(i));
      arrayaddbuf(&pre, buf, strlen(buf));

      struct asm_operand *clob = xmalloc(sizeof(*clob));
      clob->constraint = rname;
      clob->next = clobbers;
      clobbers = clob;
    }
    i++;
  }

  size_t len = strlen(s);
  char *buf = xmalloc(len * 2 + 32);
  char *p = buf;
  while (*s) {
    if (*s == '%') {
      s++;
      if (*s == '%') {
        *p++ = '%';
        s++;
      } else if (isdigit((unsigned char)*s)) {
        int op_idx = 0;
        while (isdigit((unsigned char)*s)) {
          op_idx = op_idx * 10 + (*s - '0');
          s++;
        }

        if (op_idx < n_outputs) {
          const char *reg = get_ret_reg();
          while (*reg)
            *p++ = *reg++;
        } else {
          int input_idx = op_idx - n_outputs;
          struct asm_operand *op = inputs;
          for (int k = 0; k < input_idx && op; k++)
            op = op->next;

          char *reg_name = op ? get_asmname(op->expr) : NULL;
          if (reg_name) {
            char *rname = strip_quotes(reg_name);
            char *r = rname;
            while (*r)
              *p++ = *r++;
            free(rname);
          } else {
            const char *reg = get_arg_reg(input_idx);
            while (*reg)
              *p++ = *reg++;
          }
        }
      } else {
        *p++ = '%';
      }
    } else {
      *p++ = *s++;
    }
  }
  *p = '\0';

  struct array final = {0};
  if (pre.len)
    arrayaddbuf(&final, pre.val, pre.len);
  arrayaddbuf(&final, buf, strlen(buf));
  if (post.len)
    arrayaddbuf(&final, post.val, post.len);
  arrayaddbuf(&final, "", 1);

  int class = 0;
  if (outputs)
    class = qbetype(outputs->expr->type).base;

  int n_inputs = 0;
  for (struct asm_operand *op = inputs; op; op = op->next)
    n_inputs++;

  struct value **arg_vals = xmalloc(n_inputs * sizeof(struct value *));
  int *arg_cls = xmalloc(n_inputs * sizeof(int));

  i = 0;
  for (struct asm_operand *op = inputs; op; op = op->next) {
    arg_vals[i] = funcexpr(f, op->expr);
    arg_cls[i] = qbetype(op->expr->type).base;
    i++;
  }

  struct value *res = funcinst(f, ICALLASM, class, mkstring((char *) final.val), NULL);

  for (i = 0; i < n_inputs; ++i) {
    funcinst(f, IARG, arg_cls[i], arg_vals[i], NULL);
  }

  free(arg_vals);
  free(arg_cls);
  free(buf);
  if (pre.val)
    free(pre.val);
  if (post.val)
    free(post.val);

  if (outputs) {
    struct expr *lhs = outputs->expr;
    if (lhs->kind == EXPRTEMP) {
      lhs->u.temp = res;
    } else {
      struct lvalue lval = funclval(f, lhs);
      funcstore(f, lhs->type, lhs->qual, lval, res);
    }
  }
}

static struct value *convert(struct func *f, struct type *dst, struct type *src, struct value *l) {
  enum instkind op = INONE;
  struct value *r = NULL;
  int class = 'w';

  if (src->kind == TYPEPOINTER)
    src = &typeulong;
  if (dst->kind == TYPEPOINTER)
    dst = &typeulong;
  if (dst->kind == TYPEVOID)
    return NULL;
  if (!(src->prop & PROPREAL) || !(dst->prop & PROPREAL))
    fatal("internal error; unsupported conversion");
  if (dst->kind == TYPEBOOL) {
    class = 'w';
    if (src->prop & PROPINT) {
      r = mkintconst(0);
      switch (src->size) {
        case 1: op = ICNEW, l = funcinst(f, IEXTUB, 'w', l, NULL); break;
        case 2: op = ICNEW, l = funcinst(f, IEXTUH, 'w', l, NULL); break;
        case 4: op = ICNEW; break;
        case 8: op = ICNEL; break;
        default: fatal("internal error; unknown integer conversion"); return NULL; /* unreachable */
      }
    } else {
      fatal("internal error; unknown non-integer conversion");
      return NULL; /* unreachable */
    }
  } else if (dst->prop & PROPINT) {
    class = dst->size == 8 ? 'l' : 'w';
    if (src->prop & PROPINT) {
      if (dst->size <= src->size)
        return l;
      switch (src->size) {
        case 4: op = src->u.basic.issigned ? IEXTSW : IEXTUW; break;
        case 2: op = src->u.basic.issigned ? IEXTSH : IEXTUH; break;
        case 1: op = src->u.basic.issigned ? IEXTSB : IEXTUB; break;
        default: fatal("internal error; unknown integer conversion"); return NULL; /* unreachable */
      }
    } else {
      fatal("internal error; unknown float conversion");
    }
  } else {
    fatal("internal error; unknown float conversion");
  }

  return funcinst(f, op, class, l, r);
}

static void calcvla(struct func *f, struct type *t) {
  struct value *length, *basesize;

  if (!(t->prop & PROPVM))
    return;
  if (t->base)
    calcvla(f, t->base);
  if (t->kind == TYPEFUNC || t->size)
    return;
  assert(t->kind == TYPEARRAY);
  if (!t->u.array.size) {
    assert(t->base->size || t->base->kind == TYPEARRAY);
    assert(t->u.array.length);
    length = convert(f, &typeulong, t->u.array.length->type, funcexpr(f, t->u.array.length));
    basesize = t->base->size ? mkintconst(t->base->size) : t->base->u.array.size;
    t->u.array.size = funcinst(f, IMUL, 'l', length, basesize);
  }
}

static void funcalloc(struct func *f, struct decl *d) {
  enum instkind op;
  struct block *end;
  struct value *v;
  int align;

  assert(!d->type->incomplete);
  calcvla(f, d->type);
  end = f->end;
  if (d->type->size) {
    f->end = f->start;
    v = mkintconst(d->type->size);
  } else {
    assert(d->type->kind == TYPEARRAY);
    assert(d->type->u.array.size);
    v = d->type->u.array.size;
  }
  align = d->u.obj.align;
  switch (align) {
    case 1:
    case 2:
    case 4: op = IALLOC4; break;
    case 8: op = IALLOC8; break;
    default: v = funcinst(f, IADD, ptrclass, v, mkintconst(align - 16)); /* fallthrough */
    case 16: op = IALLOC16; break;
  }
  v = funcinst(f, op, ptrclass, v, NULL);
  if (align > 16) {
    /* TODO: implement alloc32 in QBE and use that instead */
    v = funcinst(f, IADD, ptrclass, v, mkintconst(align - 16));
    v = funcinst(f, IAND, ptrclass, v, mkintconst(-align));
  }
  d->value = v;
  f->end = end;
}

static struct value *funcbits(struct func *f, struct type *t, struct value *v, struct bitfield b) {
  int class, bits;

  class = t->size <= 4 ? 'w' : 'l';
  bits = b.after;
  if (bits) {
    bits += (t->size + 3 & ~3) - t->size << 3;
    v = funcinst(f, ISHL, class, v, mkintconst(bits));
  }
  bits += b.before;
  if (bits)
    v = funcinst(f, t->u.basic.issigned ? ISAR : ISHR, class, v, mkintconst(bits));
  return v;
}

static void funccopy(struct func *f, struct value *dst, struct value *src, unsigned long long size, int align) {
  enum instkind load, store;
  int class;
  struct value *tmp, *inc;
  unsigned long long off;

  assert((align & align - 1) == 0);
  class = 'w';
  switch (align) {
    case 1: load = ILOADUB, store = ISTOREB; break;
    case 2: load = ILOADUH, store = ISTOREH; break;
    case 4: load = ILOADW, store = ISTOREW; break;
    default: load = ILOADL, store = ISTOREL, align = 8, class = 'l'; break;
  }
  inc = mkintconst(align);
  off = 0;
  for (;;) {
    tmp = funcinst(f, load, class, src, NULL);
    funcinst(f, store, 0, tmp, dst);
    off += align;
    if (off >= size)
      break;
    src = funcinst(f, IADD, ptrclass, src, inc);
    dst = funcinst(f, IADD, ptrclass, dst, inc);
  }
}

static char *strip_quotes(char *s) {
  size_t len = strlen(s);
  if (len >= 2 && s[0] == '"' && s[len - 1] == '"') {
    char *r = xmalloc(len - 1);
    memcpy(r, s + 1, len - 2);
    r[len - 2] = 0;
    return r;
  }
  char *r = xmalloc(len + 1);
  strcpy(r, s);
  return r;
}

static struct value *funcstore(struct func *f, struct type *t, enum typequal tq, struct lvalue lval, struct value *v) {
  struct value *r;
  enum typeprop tp;
  unsigned long long mask;
  struct qbetype qt;
  int bits;

  if (lval.asmname) {
    char *rname = strip_quotes(lval.asmname);

    char *asm_str = xmalloc(64);
    snprintf(asm_str, 64, "mv %s, a0", rname);

    qt = qbetype(t);
    funcinst(f, ICALLASM, 0, mkstring(asm_str), NULL);
    funcinst(f, IARG, qt.base, v, NULL);
    free(rname);
  }

  if (tq & QUALVOLATILE) {
    //error(&tok.loc, "volatile store is not yet supported");
    warn("volatile store is treated as normal store");
    tq = tq & ~QUALVOLATILE;
  }
  if (tq & QUALRESTRICT) {
    warn("restrict store is treated as normal store");
    tq = tq & ~QUALRESTRICT;
  }
  if (tq & QUALCONST)
    error(&tok.loc, "cannot store to 'const' object");
  tp = t->prop;
  assert(!lval.bits.before && !lval.bits.after || tp & PROPINT);
  r = v;
  switch (t->kind) {
    case TYPESTRUCT:
    case TYPEUNION:
    case TYPEARRAY: funccopy(f, lval.addr, v, t->size, t->align); break;
    case TYPEPOINTER:
      t = &typeulong;
      /* fallthrough */
    default:
      assert(tp & PROPSCALAR);
      qt = qbetype(t);
      bits = lval.bits.before + lval.bits.after;
      if (bits) {
        mask = 0xffffffffffffffffu >> 64 - t->size * 8 + bits << lval.bits.before;
        v = funcinst(f, ISHL, qt.base, v, mkintconst(lval.bits.before));
        r = funcbits(f, t, v, lval.bits);
        v = funcinst(f, IAND, qt.base, v, mkintconst(mask));
        v = funcinst(f, IOR, qt.base, v,
                     funcinst(f, IAND, qt.base, funcinst(f, qt.load, qt.base, lval.addr, NULL), mkintconst(~mask)));
      }
      funcinst(f, qt.store, 0, v, lval.addr);
      break;
  }
  return r;
}

static struct value *funcload(struct func *f, struct type *t, struct lvalue lval) {
  struct value *v;
  struct qbetype qt;

  if (lval.asmname) {
    char *rname = strip_quotes(lval.asmname);

    if (strcmp(rname, get_ret_reg()) == 0) {
      free(rname);
      goto load_memory;
    }

    char *asm_str = xmalloc(64);
    snprintf(asm_str, 64, "mv a0, %s", rname);

    qt = qbetype(t);
    v = funcinst(f, ICALLASM, qt.base, mkstring(asm_str), NULL);
    free(rname);
    return funcbits(f, t, v, lval.bits);
  }

load_memory:
  switch (t->kind) {
    case TYPESTRUCT:
    case TYPEUNION:
    case TYPEARRAY: return lval.addr;
  }
  qt = qbetype(t);
  v = funcinst(f, qt.load, qt.base, lval.addr, NULL);
  return funcbits(f, t, v, lval.bits);
}

struct func *mkfunc(struct decl *decl, char *name, struct type *t, struct scope *s) {
  struct func *f;
  struct decl *d;
  struct value *v;

  f = xmalloc(sizeof(*f));
  f->decl = decl;
  f->name = name;
  f->type = t;
  f->start = f->end = mkblock("start");
  f->lastid = 0;
  mapinit(&f->gotos, 8);
  emittype(t->base);

  /* allocate space for parameters */
  f->paramtemps = xreallocarray(NULL, t->u.func.nparam, sizeof *f->paramtemps);
  for (d = t->u.func.params, v = f->paramtemps; d; d = d->next, ++v) {
    emittype(d->type);
    functemp(f, v);
    if (!d->name)
      continue;
    if (d->type->value) {
      d->value = v;
    } else {
      funcalloc(f, d);
      funcstore(f, d->type, QUALNONE, (struct lvalue){d->value}, v);
    }
  }

  t = mkarraytype(&typechar, QUALCONST, strlen(name) + 1);
  d = mkdecl("__func__", DECLOBJECT, t, QUALNONE, LINKNONE);
  d->u.obj.storage = SDSTATIC;
  d->value = mkglobal(d);
  scopeputdecl(s, d);
  f->namedecl = d;

  funclabel(f, mkblock("body"));

  return f;
}

void delfunc(struct func *f) {
  struct block *b;
  struct inst **inst;

  while (b = f->start) {
    f->start = b->next;
    arrayforeach(&b->insts, inst) free(*inst);
    free(b->insts.val);
    free(b);
  }
  mapfree(&f->gotos, free);
  free(f);
}

struct type *functype(struct func *f) {
  return f->type;
}

void funclabel(struct func *f, struct block *b) {
  f->end->next = b;
  f->end = b;
}

void funcjmp(struct func *f, struct block *l) {
  struct block *b = f->end;

  if (!b->jump.kind) {
    b->jump.kind = JUMP_JMP;
    b->jump.blk[0] = l;
  }
}

void funcjnz(struct func *f, struct value *v, struct type *t, struct block *l1, struct block *l2) {
  struct block *b = f->end;

  if (b->jump.kind)
    return;
  if (t) {
    assert(t->prop & PROPSCALAR);
    /*
		Ideally we would just do this conversion unconditionally,
		but QBE is not currently able to optimize the conversion
		away for int.
		*/
    if (t->prop & PROPINT && t->size < 4)
      v = convert(f, &typeint, t, v);
    else if (t->size > 4)
      v = convert(f, &typebool, t, v);
  }
  b->jump.kind = JUMP_JNZ;
  b->jump.arg = v;
  b->jump.blk[0] = l1;
  b->jump.blk[1] = l2;
}

void funcret(struct func *f, struct value *v) {
  struct block *b = f->end;

  if (!b->jump.kind) {
    b->jump.kind = JUMP_RET;
    b->jump.arg = v;
  }
}

void funchlt(struct func *f) {
  struct block *b = f->end;

  if (!b->jump.kind)
    b->jump.kind = JUMP_HLT;
}

struct gotolabel *funcgoto(struct func *f, char *name) {
  void **entry;
  struct gotolabel *g;
  struct mapkey key;

  mapkey(&key, name, strlen(name));
  entry = mapput(&f->gotos, &key);
  g = *entry;
  if (!g) {
    g = xmalloc(sizeof(*g));
    g->label = mkblock(name);
    *entry = g;
  }

  return g;
}

static struct lvalue funclval(struct func *f, struct expr *e) {
  struct lvalue lval = {0};
  struct decl *d;

  if (e->kind == EXPRBITFIELD) {
    lval.bits = e->u.bitfield.bits;
    e = e->base;
  }
  switch (e->kind) {
    case EXPRIDENT:
      d = e->u.ident.decl;
      if (d->kind != DECLOBJECT && d->kind != DECLFUNC)
        error(&tok.loc, "identifier '%s' is not an object or function", d->name);
      if (d == f->namedecl) {
        my_fputs("data ", stdout);
        emitname(d->value);
        my_printf(" = { b \"%s\", b 0 }\n", f->name);
        f->namedecl = NULL;
      }
      lval.addr = d->value;
      lval.asmname = d->asmname;
      break;
    case EXPRSTRING:
      d = stringdecl(e);
      lval.addr = d->value;
      break;
    case EXPRCOMPOUND:
      if (e->toeval)
        funcexpr(f, e->toeval);
      d = e->u.compound.decl;
      funcinit(f, d, e->u.compound.init, true);
      lval.addr = d->value;
      break;
    case EXPRUNARY:
      if (e->op != TMUL)
        error(&tok.loc, "expression is not an object");
      lval.addr = funcexpr(f, e->base);
      break;
    default:
      if (e->type->kind != TYPESTRUCT && e->type->kind != TYPEUNION)
        error(&tok.loc, "expression is not an object");
      lval.addr = funcexpr(f, e);
  }
  return lval;
}

struct value *funcexpr(struct func *f, struct expr *e) {
  enum instkind op = INONE;
  struct decl *d;
  struct value *l, *r, *v, **argvals;
  struct lvalue lval;
  struct expr *arg;
  struct block *b[3];
  struct type *t, *functype;
  size_t i;

  calcvla(f, e->type);
  switch (e->kind) {
    case EXPRIDENT:
      d = e->u.ident.decl;
      switch (d->kind) {
        case DECLOBJECT: return funcload(f, e->type, (struct lvalue){.addr = d->value, .asmname = d->asmname});
        case DECLCONST: return d->value;
        default: fatal("unimplemented declaration kind %d", d->kind);
      }
      break;
    case EXPRCONST:
      t = e->type;
      if (t->prop & PROPINT || t->kind == TYPEPOINTER)
        return mkintconst(e->u.constant.u);
      fatal("floating point constants not supported");
    case EXPRBITFIELD:
    case EXPRCOMPOUND: lval = funclval(f, e); return funcload(f, e->type, lval);
    case EXPRINCDEC:
      lval = funclval(f, e->base);
      l = funcload(f, e->base->type, lval);
      t = e->type;
      if (t->kind == TYPEPOINTER) {
        r = mkintconst(t->base->size);
      } else if (t->prop & PROPINT) {
        r = mkintconst(1);
      } else {
        fatal("not a scalar");
        return NULL; /* unreachable */
      }
      v = funcinst(f, e->op == TINC ? IADD : ISUB, qbetype(t).base, l, r);
      v = funcstore(f, e->type, e->qual, lval, v);
      return e->u.incdec.post ? l : v;
    case EXPRCALL:
      argvals = xreallocarray(NULL, e->u.call.nargs, sizeof(argvals[0]));
      for (arg = e->u.call.args, i = 0; arg; arg = arg->next, ++i) {
        emittype(arg->type);
        argvals[i] = funcexpr(f, arg);
      }
      t = e->type;
      emittype(t);
      v = funcinst(f, ICALL, qbetype(t).base, funcexpr(f, e->base), t->value);
      functype = e->base->type->base;
      for (arg = e->u.call.args, i = 0; arg; arg = arg->next, ++i) {
        if (functype->u.func.isvararg && i == functype->u.func.nparam)
          funcinst(f, IVARARG, 0, NULL, NULL);
        t = arg->type;
        funcinst(f, IARG, qbetype(t).base, argvals[i], t->value);
      }
      e = e->base;
      if (e->kind == EXPRUNARY && e->op == TBAND) {
        e = e->base;
        if (e->kind == EXPRIDENT && e->u.ident.decl->u.func.isnoreturn)
          funchlt(f);
      }
      return v;
    case EXPRUNARY:
      switch (e->op) {
        case TBAND: lval = funclval(f, e->base); return lval.addr;
        case TMUL: r = funcexpr(f, e->base); return funcload(f, e->type, (struct lvalue){r});
        case TSUB:
          r = funcexpr(f, e->base);
          l = mkintconst(0);
          return funcinst(f, ISUB, qbetype(e->type).base, l, r);
      }
      fatal("internal error; unknown unary expression");
      break;
    case EXPRCAST:
      if (e->toeval)
        funcexpr(f, e->toeval);
      l = funcexpr(f, e->base);
      return convert(f, e->type, e->base->type, l);
    case EXPRBINARY:
      l = funcexpr(f, e->u.binary.l);
      if (e->op == TLOR || e->op == TLAND) {
        b[0] = mkblock("logic_right");
        b[1] = mkblock("logic_join");
        t = e->u.binary.l->type;
        if (e->op == TLOR) {
          funcjnz(f, l, t, b[1], b[0]);
          b[1]->phi.val[0] = mkintconst(1);
        } else {
          funcjnz(f, l, t, b[0], b[1]);
          b[1]->phi.val[0] = mkintconst(0);
        }
        b[1]->phi.blk[0] = f->end;
        funclabel(f, b[0]);
        r = funcexpr(f, e->u.binary.r);
        b[1]->phi.val[1] = convert(f, &typebool, e->u.binary.r->type, r);
        b[1]->phi.blk[1] = f->end;
        funclabel(f, b[1]);
        functemp(f, &b[1]->phi.res);
        b[1]->phi.class = 'w';
        return &b[1]->phi.res;
      }
      r = funcexpr(f, e->u.binary.r);
      t = e->u.binary.l->type;
      if (t->kind == TYPEPOINTER)
        t = &typeulong;
      switch (e->op) {
        case TMUL: op = IMUL; break;
        case TDIV: op = !(t->prop & PROPINT) || t->u.basic.issigned ? IDIV : IUDIV; break;
        case TMOD: op = t->u.basic.issigned ? IREM : IUREM; break;
        case TADD: op = IADD; break;
        case TSUB: op = ISUB; break;
        case TSHL: op = ISHL; break;
        case TSHR: op = t->u.basic.issigned ? ISAR : ISHR; break;
        case TBOR: op = IOR; break;
        case TBAND: op = IAND; break;
        case TXOR: op = IXOR; break;
        case TLESS:
          if (t->size <= 4)
            op = t->u.basic.issigned ? ICSLTW : ICULTW;
          else
            op = t->u.basic.issigned ? ICSLTL : ICULTL;
          break;
        case TGREATER:
          if (t->size <= 4)
            op = t->u.basic.issigned ? ICSGTW : ICUGTW;
          else
            op = t->u.basic.issigned ? ICSGTL : ICUGTL;
          break;
        case TLEQ:
          if (t->size <= 4)
            op = t->u.basic.issigned ? ICSLEW : ICULEW;
          else
            op = t->u.basic.issigned ? ICSLEL : ICULEL;
          break;
        case TGEQ:
          if (t->size <= 4)
            op = t->u.basic.issigned ? ICSGEW : ICUGEW;
          else
            op = t->u.basic.issigned ? ICSGEL : ICUGEL;
          break;
        case TEQL: op = t->size <= 4 ? ICEQW : ICEQL; break;
        case TNEQ: op = t->size <= 4 ? ICNEW : ICNEL; break;
      }
      if (op == INONE)
        fatal("internal error; unimplemented binary expression");
      return funcinst(f, op, qbetype(e->type).base, l, r);
    case EXPRCOND:
      b[0] = mkblock("cond_true");
      b[1] = mkblock("cond_false");
      b[2] = mkblock("cond_join");

      v = funcexpr(f, e->base);
      funcjnz(f, v, e->base->type, b[0], b[1]);

      funclabel(f, b[0]);
      b[2]->phi.val[0] = funcexpr(f, e->u.cond.t);
      b[2]->phi.blk[0] = f->end;
      funcjmp(f, b[2]);

      funclabel(f, b[1]);
      b[2]->phi.val[1] = funcexpr(f, e->u.cond.f);
      b[2]->phi.blk[1] = f->end;

      funclabel(f, b[2]);
      if (e->type == &typevoid)
        return NULL;
      functemp(f, &b[2]->phi.res);
      b[2]->phi.class = qbetype(e->type).base;
      return &b[2]->phi.res;
    case EXPRASSIGN:
      r = funcexpr(f, e->u.assign.r);
      if (e->u.assign.l->kind == EXPRTEMP) {
        e->u.assign.l->u.temp = r;
      } else {
        lval = funclval(f, e->u.assign.l);
        r = funcstore(f, e->u.assign.l->type, e->u.assign.l->qual, lval, r);
      }
      return r;
    case EXPRCOMMA:
      for (e = e->base; e->next; e = e->next)
        funcexpr(f, e);
      return funcexpr(f, e);
    case EXPRBUILTIN:
      switch (e->u.builtin.kind) {
        case BUILTINVASTART:
          l = funcexpr(f, e->base);
          funcinst(f, IVASTART, 0, l, NULL);
          break;
        case BUILTINVAARG:
          if (e->toeval)
            funcexpr(f, e->toeval);
          /* https://todo.sr.ht/~mcf/cproc/52 */
          if (!(e->type->prop & PROPSCALAR))
            error(&tok.loc, "va_arg with non-scalar type is not yet supported");
          l = funcexpr(f, e->base);
          return funcinst(f, IVAARG, qbetype(e->type).base, l, NULL);
        case BUILTINALLOCA: l = funcexpr(f, e->base); return funcinst(f, IALLOC16, ptrclass, l, NULL);
        case BUILTINUNREACHABLE: return NULL;
        default: fatal("internal error: unimplemented builtin");
      }
      return NULL;
    case EXPRTEMP:
      if (e->type == &typevoid)
        return NULL;
      assert(e->u.temp);
      return e->u.temp;
    case EXPRSIZEOF:
      t = e->u.szof.type;
      assert(t->kind == TYPEARRAY);
      calcvla(f, t);
      /* if the sizeof operand has VLA type, we must evaluate it */
      if (e->base)
        funcexpr(f, e->base);
      return t->u.array.size;
  }
  fatal("unimplemented expression %d", e->kind);
  return NULL;
}

static void zero(struct func *func, struct value *addr, int align, unsigned long long offset, unsigned long long end) {
  static const enum instkind store[] = {
    [1] = ISTOREB,
    [2] = ISTOREH,
    [4] = ISTOREW,
    [8] = ISTOREL,
  };
  static struct value z = {.kind = VALUE_INTCONST};
  struct value *tmp;
  int a = 1;

  while (offset < end) {
    if ((align - (offset & align - 1)) & a) {
      tmp = offset ? funcinst(func, IADD, ptrclass, addr, mkintconst(offset)) : addr;
      funcinst(func, store[a], 0, &z, tmp);
      offset += a;
    }
    if (a < align)
      a <<= 1;
  }
}

void funcinit(struct func *func, struct decl *d, struct init *init, bool hasinit) {
  struct lvalue dst;
  struct value *src, *v;
  unsigned long long offset = 0, max = 0;
  size_t i, w;

  dst.asmname = d->asmname;
  funcalloc(func, d);
  if (!hasinit)
    return;
  for (; init; init = init->next) {
    zero(func, d->value, d->type->align, offset, init->start);
    dst.bits = init->bits;
    if (init->expr->kind == EXPRSTRING) {
      w = init->expr->type->base->size;
      for (i = 0; i < init->expr->u.string.size && i * w < init->end - init->start; ++i) {
        v = mkintconst(init->start + i * w);
        dst.addr = funcinst(func, IADD, ptrclass, d->value, v);
        switch (w) {
          case 1: v = mkintconst(((unsigned char *)init->expr->u.string.data)[i]); break;
          case 2: v = mkintconst(((uint16_t *)init->expr->u.string.data)[i]); break;
          case 4: v = mkintconst(((uint32_t *)init->expr->u.string.data)[i]); break;
        }
        funcstore(func, init->expr->type->base, QUALNONE, dst, v);
      }
      offset = init->start + i * w;
    } else {
      if (offset < init->end && (dst.bits.before || dst.bits.after))
        zero(func, d->value, d->type->align, offset, init->end);
      dst.addr = d->value;
      /*
			QBE's memopt does not eliminate the store for ptr + 0,
			so only emit the add if the offset is non-zero
			*/
      if (init->start > 0)
        dst.addr = funcinst(func, IADD, ptrclass, dst.addr, mkintconst(init->start));
      src = funcexpr(func, init->expr);
      funcstore(func, init->expr->type, QUALNONE, dst, src);
      offset = init->end;
    }
    if (max < offset)
      max = offset;
  }
  zero(func, d->value, d->type->align, max, d->type->size);
}

static void casesearch(struct func *f, int class, struct value *v, struct switchcase *c, struct block *defaultlabel) {
  struct value *res, *key;
  struct block *label[3];

  if (!c) {
    funcjmp(f, defaultlabel);
    return;
  }
  label[0] = mkblock("switch_ne");
  label[1] = mkblock("switch_lt");
  label[2] = mkblock("switch_gt");

  /* XXX: linear search if c->node.height < 4 */
  key = mkintconst(c->node.key);
  res = funcinst(f, class == 'w' ? ICEQW : ICEQL, 'w', v, key);
  funcjnz(f, res, NULL, c->body, label[0]);
  funclabel(f, label[0]);
  res = funcinst(f, class == 'w' ? ICULTW : ICULTL, 'w', v, key);
  funcjnz(f, res, NULL, label[1], label[2]);
  funclabel(f, label[1]);
  casesearch(f, class, v, c->node.child[0], defaultlabel);
  funclabel(f, label[2]);
  casesearch(f, class, v, c->node.child[1], defaultlabel);
}

void funcswitch(struct func *f, struct value *v, struct switchcases *c, struct block *defaultlabel) {
  casesearch(f, qbetype(c->type).base, v, c->root, defaultlabel);
}

/* emit */

static void emitname(struct value *v) {
  static const char sigil[] = {
    [VALUE_TEMP] = '%',
    [VALUE_GLOBAL] = '$',
    [VALUE_TYPE] = ':',
    [VALUE_LABEL] = '@',
  };
  int kind;

  kind = v->kind & 0xf;
  if (kind >= LEN(sigil) || !sigil[kind])
    fatal("invalid value");
  my_putchar(sigil[kind]);
  if (kind == VALUE_GLOBAL && v->id)
    my_fputs(".L", stdout);
  if (v->u.name)
    my_fputs(v->u.name, stdout);
  if (v->id)
    my_printf(".%u", v->id);
}

static void emitvalue(struct value *v) {
  switch (v->kind & 0xf) {
    case VALUE_INTCONST: my_printf("%llu", v->u.i); break;
    case VALUE_STRING:
      my_fputc('"', stdout);
      for (const char *p = v->u.name; *p; ++p) {
        unsigned char c = *p;
        switch (c) {
          case '\n': my_fputs("\\n", stdout); break;
          case '\t': my_fputs("\\t", stdout); break;
          case '\r': my_fputs("\\r", stdout); break;
          case '\\': my_fputs("\\\\", stdout); break;
          case '"': my_fputs("\\\"", stdout); break;
          default:
            if (isprint(c)) {
              my_putchar(c);
            } else {
              my_printf("\\%03o", c);
            }
            break;
        }
      }
      my_fputc('"', stdout);
      break;
    case VALUE_GLOBAL:
      if (v->kind & VALUE_THREAD)
        my_fputs("thread ", stdout);
      /* fallthrough */
    default: emitname(v); break;
  }
}

static void emitclass(int class, struct value *v) {
  if (v && v->kind == VALUE_TYPE)
    emitname(v);
  else if (class)
    my_putchar(class);
  else
    fatal("type has no QBE representation");
}

/* XXX: need to consider _Alignas on struct members */
static void emittype(struct type *t) {
  struct member *m, *other;
  struct type *sub;
  unsigned long long off;

  if (t->value || t->kind != TYPESTRUCT && t->kind != TYPEUNION)
    return;
  t->value = xmalloc(sizeof(*t->value));
  t->value->kind = VALUE_TYPE;
  t->value->u.name = t->u.structunion.tag;
  t->value->id = ++emittype_id;
  for (m = t->u.structunion.members; m; m = m->next) {
    for (sub = m->type; sub->kind == TYPEARRAY; sub = sub->base)
      ;
    emittype(sub);
  }
  my_fputs("type ", stdout);
  emitname(t->value);
  if (t == targ->typevalist) {
    my_printf(" = align %d { %llu }\n", t->align, t->size);
    return;
  }
  my_fputs(" = { ", stdout);
  for (m = t->u.structunion.members, off = 0; m;) {
    if (t->kind == TYPESTRUCT) {
      /* look for a subsequent member with a larger storage unit */
      for (other = m->next; other; other = other->next) {
        if (other->offset >= ALIGNUP(m->offset + 1, 8))
          break;
        if (other->offset <= m->offset)
          m = other;
      }
      off = m->offset + m->type->size;
    } else {
      my_fputs("{ ", stdout);
    }
    for (sub = m->type; sub->kind == TYPEARRAY; sub = sub->base)
      ;
    emitclass(qbetype(sub).data, sub->value);
    if (m->type->size > sub->size)
      my_printf(" %llu", m->type->size / sub->size);
    if (t->kind == TYPESTRUCT) {
      my_fputs(", ", stdout);
      /* skip subsequent members contained within the same storage unit */
      do
        m = m->next;
      while (m && m->offset < off);
    } else {
      my_fputs(" } ", stdout);
      m = m->next;
    }
  }
  my_puts("}");
}

static struct inst **emitinst(struct inst **instp, struct inst **instend) {
  int op, first;
  struct inst *inst = *instp;

  my_putchar('\t');
  assert(inst->kind < LEN(instname));
  if (inst->res.kind) {
    emitvalue(&inst->res);
    my_fputs(" =", stdout);
    emitclass(inst->class, inst->arg[1]);
    my_putchar(' ');
  }
  my_fputs(instname[inst->kind], stdout);
  my_putchar(' ');
  emitvalue(inst->arg[0]);
  ++instp;
  op = inst->kind;
  switch (op) {
    case ICALL:
    case ICALLASM:
      my_putchar('(');
      for (first = 1; instp != instend; ++instp) {
        inst = *instp;
        if (inst->kind == IVARARG) {
          my_fputs(", ...", stdout);
          continue;
        }
        if (inst->kind != IARG)
          break;
        if (first)
          first = 0;
        else
          my_fputs(", ", stdout);
        emitclass(inst->class, inst->arg[1]);
        my_putchar(' ');
        emitvalue(inst->arg[0]);
      }
      my_putchar(')');
      break;
    default:
      if (inst->arg[1]) {
        my_fputs(", ", stdout);
        emitvalue(inst->arg[1]);
      }
  }
  my_putchar('\n');
  return instp;
}

static void emitjump(struct jump *j) {
  switch (j->kind) {
    case JUMP_NONE: break;
    case JUMP_RET:
      my_fputs("\tret", stdout);
      if (j->arg) {
        my_fputc(' ', stdout);
        emitvalue(j->arg);
      }
      my_putchar('\n');
      break;
    case JUMP_JMP:
      my_fputs("\tjmp ", stdout);
      emitname(&j->blk[0]->label);
      my_putchar('\n');
      break;
    case JUMP_JNZ:
      my_fputs("\tjnz ", stdout);
      emitvalue(j->arg);
      my_fputs(", ", stdout);
      emitname(&j->blk[0]->label);
      my_fputs(", ", stdout);
      emitname(&j->blk[1]->label);
      my_putchar('\n');
      break;
    case JUMP_HLT: my_fputs("\thlt\n", stdout); break;
    default: assert(0);
  }
}

void emitfunc(struct func *f, bool global) {
  struct block *b;
  struct inst **inst, **instend;
  struct decl *p;
  struct value *v;

  if (f->end->jump.kind == JUMP_NONE) {
    v = NULL;
    /* implicitly return 0 from main if we reach the end of the function */
    if (strcmp(f->name, "main") == 0 && f->type->base == &typeint)
      v = mkintconst(0);
    funcret(f, v);
  }
  if (global)
    my_puts("export");
  my_fputs("function ", stdout);
  if (f->type->base != &typevoid) {
    emitclass(qbetype(f->type->base).base, f->type->base->value);
    my_putchar(' ');
  }
  emitname(f->decl->value);
  my_putchar('(');
  for (p = f->type->u.func.params, v = f->paramtemps; p; p = p->next, ++v) {
    if (p != f->type->u.func.params)
      my_fputs(", ", stdout);
    emitclass(qbetype(p->type).base, p->type->value);
    my_putchar(' ');
    emitname(v);
  }
  if (f->type->u.func.isvararg) {
    if (f->type->u.func.params)
      my_fputs(", ", stdout);
    my_fputs("...", stdout);
  }
  my_puts(") {");
  for (b = f->start; b; b = b->next) {
    emitname(&b->label);
    my_putchar('\n');
    if (b->phi.res.kind) {
      my_putchar('\t');
      emitvalue(&b->phi.res);
      my_printf(" =%c phi ", b->phi.class);
      emitname(&b->phi.blk[0]->label);
      my_putchar(' ');
      emitvalue(b->phi.val[0]);
      my_fputs(", ", stdout);
      emitname(&b->phi.blk[1]->label);
      my_putchar(' ');
      emitvalue(b->phi.val[1]);
      my_putchar('\n');
    }
    instend = (struct inst **)((char *)b->insts.val + b->insts.len);
    for (inst = b->insts.val; inst != instend;)
      inst = emitinst(inst, instend);
    emitjump(&b->jump);
  }
  my_puts("}");
}

static void dataitem(struct expr *expr, unsigned long long size) {
  struct decl *decl;
  size_t i, w;
  unsigned c;

  switch (expr->kind) {
    case EXPRUNARY:
      if (expr->op != TBAND)
        fatal("not a address expr");
      expr = expr->base;
      if (expr->kind != EXPRIDENT)
        error(&tok.loc, "initializer is not a constant expression");
      decl = expr->u.ident.decl;
      if (decl->kind == DECLOBJECT && decl->u.obj.storage != SDSTATIC)
        error(&tok.loc, "initializer is not a constant expression");
      emitname(decl->value);
      break;
    case EXPRBINARY:
      if (expr->op != TADD || expr->u.binary.l->kind != EXPRUNARY || expr->u.binary.r->kind != EXPRCONST)
        error(&tok.loc, "initializer is not a constant expression");
      dataitem(expr->u.binary.l, 0);
      my_fputs(" + ", stdout);
      dataitem(expr->u.binary.r, 0);
      break;
    case EXPRCONST: my_printf("%llu", expr->u.constant.u); break;
    case EXPRSTRING:
      w = expr->type->base->size;
      if (w == 1) {
        my_fputc('"', stdout);
        for (i = 0; i < expr->u.string.size && i < size; ++i) {
          c = ((unsigned char *)expr->u.string.data)[i];
          if (isprint(c) && c != '"' && c != '\\')
            my_putchar(c);
          else
            my_printf("\\%03o", c);
        }
        my_fputc('"', stdout);
      } else {
        for (i = 0; i < expr->u.string.size && i * w < size; ++i) {
          switch (w) {
            case 2: my_printf("%u ", ((uint16_t *)expr->u.string.data)[i]); break;
            case 4: my_printf("%u ", ((uint32_t *)expr->u.string.data)[i]); break;
            default: assert(0);
          }
        }
      }
      if (i * w < size)
        my_printf(", z %llu", size - (unsigned long long)i * w);
      break;
    default: error(&tok.loc, "initializer is not a constant expression");
  }
}

void emitdata(struct decl *d, struct init *init) {
  struct init *cur;
  struct type *t;
  unsigned long long offset = 0, start, end, bits = 0;
  size_t i;
  int align;

  align = d->u.obj.align;
  for (cur = init; cur; cur = cur->next)
    cur->expr = eval(cur->expr);
  if (d->u.obj.storage == SDTHREAD)
    my_fputs("thread ", stdout);
  if (d->linkage == LINKEXTERN)
    my_fputs("export ", stdout);
  my_fputs("data ", stdout);
  emitname(d->value);
  my_printf(" = align %d { ", align);

  while (init) {
    cur = init;
    while ((init = init->next) && init->start * 8 + init->bits.before < cur->end * 8 - cur->bits.after) {
      /*
			XXX: Currently, if multiple union members are
			initialized, these assertions may not hold.
			(https://todo.sr.ht/~mcf/cproc/38)
			*/
      assert(cur->expr->kind == EXPRSTRING);
      assert(init->expr->kind == EXPRCONST);
      i = (init->start - cur->start) / cur->expr->type->base->size;
      switch (cur->expr->type->base->size) {
        case 1: ((unsigned char *)cur->expr->u.string.data)[i] = init->expr->u.constant.u; break;
        case 2: ((uint16_t *)cur->expr->u.string.data)[i] = init->expr->u.constant.u; break;
        case 4: ((uint32_t *)cur->expr->u.string.data)[i] = init->expr->u.constant.u; break;
      }
    }
    start = cur->start + cur->bits.before / 8;
    end = cur->end - (cur->bits.after + 7) / 8;
    if (offset < start && bits) {
      my_printf("b %u, ", (unsigned)bits); /* unfinished byte from previous bit-field */
      ++offset;
      bits = 0;
    }
    if (offset < start)
      my_printf("z %llu, ", start - offset);
    if (cur->bits.before || cur->bits.after) {
      /* little-endian target specific */
      assert(cur->expr->type->prop & PROPINT);
      assert(cur->expr->kind == EXPRCONST);
      bits |= cur->expr->u.constant.u << cur->bits.before % 8;
      for (offset = start; offset < end; ++offset, bits >>= 8)
        my_printf("b %u, ", (unsigned)bits & 0xff);
      /*
			clear the upper `after` bits in the last byte,
			or all bits when `after` is 0 (we ended on a
			byte boundary).
			*/
      bits &= 0x7f >> (cur->bits.after + 7) % 8;
    } else {
      t = cur->expr->type;
      if (t->kind == TYPEARRAY)
        t = t->base;
      my_printf("%c ", qbetype(t).data);
      dataitem(cur->expr, cur->end - cur->start);
      my_fputs(", ", stdout);
    }
    offset = end;
  }
  if (bits) {
    my_printf("b %u, ", (unsigned)bits);
    ++offset;
  }
  assert(offset <= d->type->size);
  if (offset < d->type->size)
    my_printf("z %llu ", d->type->size - offset);
  my_puts("}");
}

void emitasm(char *s) {
  size_t num_lines;
  char **asm_lines = process_asm_string(s, &num_lines);

  my_puts("#APP");
  for (size_t i = 0; i < num_lines; ++i) {
    my_fputs("\t", stdout);
    my_puts(asm_lines[i]);
    free(asm_lines[i]);
  }
  my_puts("#NO_APP");

  if (asm_lines) {
    free(asm_lines);
  }
}

void qbe_init() {
  mkblock_id = 0;
  mkglobal_id = 0;
  emittype_id = 0;
}
