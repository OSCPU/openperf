#include "cc.h"
#include "stdio.h"
#include "stdlib.h"
#include "util.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

/* 6.8.1 Labeled statements */
static bool label(struct func *f, struct scope *s) {
  char *name;
  struct gotolabel *g;
  struct block *b;
  unsigned long long i;

  attr(NULL, 0);
  switch (tok.kind) {
    case TCASE:
      next();
      if (!s->switchcases)
        error(&tok.loc, "'case' label must be in switch");
      b = mkblock("switch_case");
      funclabel(f, b);
      i = intconstexpr(s, true);
      switchcase(s->switchcases, i, b);
      expect(TCOLON, "after case expression");
      break;
    case TDEFAULT:
      next();
      if (!s->switchcases)
        error(&tok.loc, "'default' label must be in switch");
      if (s->switchcases->defaultlabel)
        error(&tok.loc, "multiple 'default' labels");
      expect(TCOLON, "after 'default'");
      s->switchcases->defaultlabel = mkblock("switch_default");
      funclabel(f, s->switchcases->defaultlabel);
      break;
    case TIDENT:
      name = tok.lit;
      if (!peek(TCOLON))
        return false;
      g = funcgoto(f, name);
      g->defined = true;
      funclabel(f, g->label);
      break;
    default: return false;
  }
  return true;
}

static void labelstmt(struct func *f, struct scope *s) {
  while (label(f, s))
    ;
  stmt(f, s, NULL);
}

/* 6.8 Statements and blocks */
struct value *stmt(struct func *f, struct scope *s, struct type **rt) {
  char *name;
  struct expr *e;
  struct type *t;
  struct value *v;
  struct block *b[4];
  struct switchcases swtch;

  attr(NULL, 0);
  switch (tok.kind) {
    /* 6.8.2 Compound statement */
    case TLBRACE:
      next();
      s = mkscope(s);
      while (tok.kind != TRBRACE) {
        if (!label(f, s) && !decl(s, f))
          stmt(f, s, NULL);
      }
      s = delscope(s);
      next();
      break;

    /* 6.8.3 Expression statement */
    case TSEMICOLON: next(); break;
    default:
      e = expr(s);
      v = funcexpr(f, e);
      if (rt)
        *rt = e->type;
      delexpr(e);
      expect(TSEMICOLON, "after expression statement");
      return v;

    /* 6.8.4 Selection statement */
    case TIF:
      next();
      s = mkscope(s);
      expect(TLPAREN, "after 'if'");
      e = expr(s);
      t = e->type;
      if (!(t->prop & PROPSCALAR))
        error(&tok.loc, "controlling expression of if statement must have scalar type");
      v = funcexpr(f, e);
      delexpr(e);
      expect(TRPAREN, "after expression");

      b[0] = mkblock("if_true");
      b[1] = mkblock("if_false");
      funcjnz(f, v, t, b[0], b[1]);

      funclabel(f, b[0]);
      s = mkscope(s);
      labelstmt(f, s);
      s = delscope(s);

      if (consume(TELSE)) {
        b[2] = mkblock("if_join");
        funcjmp(f, b[2]);
        funclabel(f, b[1]);
        s = mkscope(s);
        labelstmt(f, s);
        s = delscope(s);
        funclabel(f, b[2]);
      } else {
        funclabel(f, b[1]);
      }
      s = delscope(s);
      break;
    case TSWITCH:
      next();

      s = mkscope(s);
      expect(TLPAREN, "after 'switch'");
      e = expr(s);
      expect(TRPAREN, "after expression");

      if (!(e->type->prop & PROPINT))
        error(&tok.loc, "controlling expression of switch statement must have integer type");
      e = exprpromote(e);

      swtch.root = NULL;
      swtch.type = e->type;
      swtch.defaultlabel = NULL;

      b[0] = mkblock("switch_cond");
      b[1] = mkblock("switch_join");

      v = funcexpr(f, e);
      funcjmp(f, b[0]);
      s = mkscope(s);
      s->breaklabel = b[1];
      s->switchcases = &swtch;
      labelstmt(f, s);
      funcjmp(f, b[1]);

      funclabel(f, b[0]);
      funcswitch(f, v, &swtch, swtch.defaultlabel ? swtch.defaultlabel : b[1]);
      s = delscope(s);

      funclabel(f, b[1]);
      s = delscope(s);
      break;

    /* 6.8.5 Iteration statements */
    case TWHILE:
      next();
      s = mkscope(s);
      expect(TLPAREN, "after 'while'");
      e = expr(s);
      t = e->type;
      if (!(t->prop & PROPSCALAR))
        error(&tok.loc, "controlling expression of loop must have scalar type");
      expect(TRPAREN, "after expression");

      b[0] = mkblock("while_cond");
      b[1] = mkblock("while_body");
      b[2] = mkblock("while_join");

      funclabel(f, b[0]);
      v = funcexpr(f, e);
      funcjnz(f, v, t, b[1], b[2]);
      funclabel(f, b[1]);
      s = mkscope(s);
      s->continuelabel = b[0];
      s->breaklabel = b[2];
      labelstmt(f, s);
      s = delscope(s);
      funcjmp(f, b[0]);
      funclabel(f, b[2]);
      s = delscope(s);
      break;
    case TDO:
      next();

      b[0] = mkblock("do_body");
      b[1] = mkblock("do_cond");
      b[2] = mkblock("do_join");

      s = mkscope(s);
      s = mkscope(s);
      s->continuelabel = b[1];
      s->breaklabel = b[2];
      funclabel(f, b[0]);
      labelstmt(f, s);
      s = delscope(s);

      expect(TWHILE, "after 'do' statement");
      expect(TLPAREN, "after 'while'");
      funclabel(f, b[1]);
      e = expr(s);
      t = e->type;
      if (!(t->prop & PROPSCALAR))
        error(&tok.loc, "controlling expression of loop must have scalar type");
      expect(TRPAREN, "after expression");

      v = funcexpr(f, e);
      funcjnz(f, v, t, b[0], b[2]);
      funclabel(f, b[2]);
      s = delscope(s);
      expect(TSEMICOLON, "after 'do' statement");
      break;
    case TFOR:
      next();
      expect(TLPAREN, "after while");
      s = mkscope(s);
      if (!decl(s, f)) {
        if (tok.kind != TSEMICOLON) {
          e = expr(s);
          funcexpr(f, e);
          delexpr(e);
        }
        expect(TSEMICOLON, NULL);
      }

      b[0] = mkblock("for_cond");
      b[1] = mkblock("for_body");
      b[2] = mkblock("for_cont");
      b[3] = mkblock("for_join");

      funclabel(f, b[0]);
      if (tok.kind != TSEMICOLON) {
        e = expr(s);
        t = e->type;
        if (!(t->prop & PROPSCALAR))
          error(&tok.loc, "controlling expression of loop must have scalar type");
        v = funcexpr(f, e);
        funcjnz(f, v, t, b[1], b[3]);
        delexpr(e);
      }
      expect(TSEMICOLON, NULL);
      e = tok.kind == TRPAREN ? NULL : expr(s);
      expect(TRPAREN, NULL);

      funclabel(f, b[1]);
      s = mkscope(s);
      s->breaklabel = b[3];
      s->continuelabel = b[2];
      labelstmt(f, s);
      s = delscope(s);

      funclabel(f, b[2]);
      if (e) {
        funcexpr(f, e);
        delexpr(e);
      }
      funcjmp(f, b[0]);
      funclabel(f, b[3]);
      s = delscope(s);
      break;

    /* 6.8.6 Jump statements */
    case TGOTO:
      next();
      name = expect(TIDENT, "after 'goto'");
      funcjmp(f, funcgoto(f, name)->label);
      expect(TSEMICOLON, "after 'goto' statement");
      break;
    case TCONTINUE:
      next();
      if (!s->continuelabel)
        error(&tok.loc, "'continue' statement must be in loop");
      funcjmp(f, s->continuelabel);
      expect(TSEMICOLON, "after 'continue' statement");
      break;
    case TBREAK:
      next();
      if (!s->breaklabel)
        error(&tok.loc, "'break' statement must be in loop or switch");
      funcjmp(f, s->breaklabel);
      expect(TSEMICOLON, "after 'break' statement");
      break;
    case TRETURN:
      next();
      t = functype(f);
      if (t->base != &typevoid) {
        e = exprassign(expr(s), t->base);
        v = funcexpr(f, e);
        delexpr(e);
      } else {
        v = NULL;
      }
      funcret(f, v);
      expect(TSEMICOLON, "after 'return' statement");
      break;

    case T__ASM__:
      next();
      if (tok.kind == TVOLATILE)
        next();
      attr(NULL, 0);
      expect(TLPAREN, "after __asm__");
      tokencheck(&tok, TSTRINGLIT, "in asm statement");
      {
        struct stringlit asmstr;
        struct asm_operand *outputs = NULL, **next_out = &outputs;
        struct asm_operand *inputs = NULL, **next_in = &inputs;
        struct asm_operand *clobbers = NULL, **next_clob = &clobbers;
        struct type *t = stringconcat(&asmstr, false);

        if (t->size != 1)
          error(&tok.loc, "asm string must be a narrow string literal");

        if (tok.kind == TCOLON) {
          next();
          while (tok.kind != TCOLON && tok.kind != TRPAREN) {
            struct asm_operand *op = xmalloc(sizeof(*op));
            memset(op, 0, sizeof(*op));
            if (tok.kind == TLBRACK) {
              next();
              expect(TIDENT, "asm operand name");
              expect(TRBRACK, "asm operand name");
            }
            tokencheck(&tok, TSTRINGLIT, "asm constraint");
            op->constraint = tok.lit;
            next();
            expect(TLPAREN, "before asm operand expr");
            op->expr = assignexpr(s);
            expect(TRPAREN, "after asm operand expr");
            *next_out = op;
            next_out = &op->next;
            if (tok.kind == TCOMMA)
              next();
          }
        }
        if (tok.kind == TCOLON) {
          next();
          while (tok.kind != TCOLON && tok.kind != TRPAREN) {
            struct asm_operand *op = xmalloc(sizeof(*op));
            memset(op, 0, sizeof(*op));
            if (tok.kind == TLBRACK) {
              next();
              expect(TIDENT, "asm operand name");
              expect(TRBRACK, "asm operand name");
            }
            tokencheck(&tok, TSTRINGLIT, "asm constraint");
            op->constraint = tok.lit;
            next();
            expect(TLPAREN, "before asm operand expr");
            op->expr = assignexpr(s);
            expect(TRPAREN, "after asm operand expr");
            *next_in = op;
            next_in = &op->next;
            if (tok.kind == TCOMMA)
              next();
          }
        }
        if (tok.kind == TCOLON) {
          next();
          while (tok.kind != TRPAREN) {
            struct asm_operand *op = xmalloc(sizeof(*op));
            memset(op, 0, sizeof(*op));
            tokencheck(&tok, TSTRINGLIT, "asm clobber");
            op->constraint = tok.lit;
            next();
            *next_clob = op;
            next_clob = &op->next;
            if (tok.kind == TCOMMA)
              next();
          }
        }
        funcasm(f, asmstr.data, outputs, inputs, clobbers);
      }
      expect(TRPAREN, "after asm string");
      expect(TSEMICOLON, "after asm statement");
      break;
  }
  return NULL;
}

struct value *stmt_expr(struct func *f, struct scope *s, struct type **rt) {
  struct value *v = NULL, *last_v = NULL;
  struct type *last_t = &typevoid, *t;

  expect(TLBRACE, "start of statement expression");
  s = mkscope(s);
  s->func = f;
  while (tok.kind != TRBRACE) {
    if (!label(f, s) && !decl(s, f)) {
      v = stmt(f, s, &t);
      if (v) {
        last_v = v;
        last_t = t;
      } else {
        last_v = NULL;
        last_t = &typevoid;
      }
    } else {
      last_v = NULL;
      last_t = &typevoid;
    }
  }
  s = delscope(s);
  next();

  if (rt)
    *rt = last_t;
  return last_v;
}
