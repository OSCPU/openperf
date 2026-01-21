#include "arg.h"
#include "cc.h"
#include "util.h"
#include <bench.h>
#include <stdbool.h>

static const struct {
  const char *src;
  uint32_t cs;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {"input/test-dummy.c", 0x28963ccb, 0},
         {"input/train-Block.i", 0x92a2f606, 181},
         {"input/ref-quickjs.i", 0x5bfc4c0f, 59464},
         {"input/huge.c", 0x959014ac, 6196850},
};

void decl_init();
void qbe_init();
void scan_init();
void token_init();
void scanclose();

void obuf_init();
void obuf_display();
uint32_t obuf_checksum();
void obuf_exit();

static void usage(void) {
  fprintf(stderr, "usage: %s [input]\n", argv0);
  bench_exit(2);
}

void bench_init(int setting) {
  ps = &settings[setting];
  //bool pponly = false;
  char /**output = NULL,*/ *target = NULL;
  char *args[] = {"cproc-qbe", (char *)(ps->src), NULL};
  char **argv = args;
  int argc = 2;

  argv0 = progname(argv[0], "cproc-qbe");
  ARGBEGIN {
    //case 'E': pponly = true; break;
    //case 't': target = EARGF(usage()); break;
    //case 'o': output = EARGF(usage()); break;
    default: usage();
  }
  ARGEND

  obuf_init();
  targinit(target);

  //if (output && !freopen(output, "w", stdout))
  //  fatal("open %s:", output);

  scan_init();
  if (argc) {
    while (argc--)
      scanfrom(argv[argc], NULL);
    scanopen();
  } else {
    scanfrom("<stdin>", stdin);
  }

  decl_init();
  qbe_init();
  token_init();

  ppinit();
  scopeinit();
}

uint64_t bench_run() {
  next();
  while (tok.kind != TEOF) {
    if (tok.kind == T__ASM__) {
      next();
      expect(TLPAREN, "after __asm__");
      tokencheck(&tok, TSTRINGLIT, "in asm statement");
      struct stringlit asmstr;
      struct type *t = stringconcat(&asmstr, false);
      if (t->size != 1)
        error(&tok.loc, "asm string must be a narrow string literal");
      emitasm(asmstr.data);
      expect(TRPAREN, "after asm string");
      expect(TSEMICOLON, "after asm statement");
      continue;
    }
    if (!decl(&filescope, NULL)) {
      if (tok.kind == TSEMICOLON)
        error(&tok.loc, "unexpected ';' at top-level");
      error(&tok.loc, "expected declaration or function definition");
    }
  }
  emittentativedefns();
  return ps->ref_time;
}

int bench_validate() {
  obuf_display();
  uint32_t cs = obuf_checksum();
  printf("cs = 0x%08x\n", cs);
  obuf_exit();
  scanclose();

  fflush(stdout);
  if (ferror(stdout))
    fatal("write failed");

  int wrong = (cs != ps->cs);
  return wrong;
}
