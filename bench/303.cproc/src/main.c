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
         {"input/train-Block.i", 0x92a2f606, 0},
         {"input/ref-quickjs.i", 0x5bfc4c0f, 0},
         {"input/huge.c", 0x959014ac, 0},
};

void obuf_init();
void obuf_display();
uint32_t obuf_checksum();
void obuf_exit();

static void usage(void) {
  fprintf(stderr, "usage: %s [input]\n", argv0);
  exit(2);
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

  targinit(target);

  //if (output && !freopen(output, "w", stdout))
  //  fatal("open %s:", output);

  if (argc) {
    while (argc--)
      scanfrom(argv[argc], NULL);
    scanopen();
  } else {
    scanfrom("<stdin>", stdin);
  }

  obuf_init();
}

uint64_t bench_run() {
  ppinit();
  scopeinit();
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
  return 0;
}

int bench_validate() {
  obuf_display();
  uint32_t cs = obuf_checksum();
  printf("cs = 0x%08x\n", cs);
  obuf_exit();

  fflush(stdout);
  if (ferror(stdout))
    fatal("write failed");

  int wrong = (cs != ps->cs);
  return wrong;
}
