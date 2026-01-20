#include "arg.h"
#include "cc.h"
#include "util.h"
#include <bench.h>
#include <stdbool.h>

static void usage(void) {
  fprintf(stderr, "usage: %s [input]\n", argv0);
  exit(2);
}

void bench_init(int setting) {
  //bool pponly = false;
  char *output = NULL, *target = NULL;
  char *args[] = {"cproc-qbe", "input/dummy.c", NULL};
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

  if (output && !freopen(output, "w", stdout))
    fatal("open %s:", output);

  if (argc) {
    while (argc--)
      scanfrom(argv[argc], NULL);
    scanopen();
  } else {
    scanfrom("<stdin>", stdin);
  }
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
  fflush(stdout);
  if (ferror(stdout))
    fatal("write failed");
  return 0;
}
