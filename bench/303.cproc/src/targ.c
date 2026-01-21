#include "cc.h"
#include "util.h"
#include <stdbool.h>
#include <string.h>

const struct target *targ;

static const struct target alltargs[] = {
  {
    .name = "x86_64-sysv",
    .typewchar = &typeint,
    .typevalist =
        &(struct type){
          .kind = TYPEARRAY,
          .align = 8,
          .size = 24,
          .base =
              &(struct type){
                .kind = TYPESTRUCT,
                .align = 8,
                .size = 24,
              },
        },
    .signedchar = 1,
  },
  {
    .name = "aarch64",
    .typevalist =
        &(struct type){
          .kind = TYPESTRUCT,
          .align = 8,
          .size = 32,
          .u.structunion.tag = "va_list",
        },
    .typewchar = &typeuint,
  },
  {
    .name = "riscv64",
    .typevalist =
        &(struct type){
          .kind = TYPEPOINTER,
          .prop = PROPSCALAR,
          .align = 8,
          .size = 8,
          .base = &typevoid,
        },
    .typewchar = &typeint,
  },
  {
    .name = "riscv32",
    .typevalist =
        &(struct type){
          .kind = TYPEPOINTER,
          .prop = PROPSCALAR,
          .align = 4,
          .size = 4,
          .base = &typevoid,
        },
    .typewchar = &typeint,
  },
};

void targinit(const char *name) {
  size_t i;
  enum typequal qual;

  targ = NULL;
  if (!name) {
    /* TODO: provide a way to set this default */
    targ = &alltargs[0];
  }
  for (i = 0; i < LEN(alltargs) && !targ; ++i) {
    if (strcmp(alltargs[i].name, name) == 0)
      targ = &alltargs[i];
  }
  if (!targ)
    fatal("unknown target '%s'", name);

  if (strcmp(targ->name, "riscv32") == 0) {
    typelong.size = 4;
    typelong.align = 4;
    typeulong.size = 4;
    typeulong.align = 4;
    typenullptr.size = 4;
    typenullptr.align = 4;
  } else {
    typelong.size = 8;
    typelong.align = 8;
    typeulong.size = 8;
    typeulong.align = 8;
    typenullptr.size = 8;
    typenullptr.align = 8;
  }

  typechar.u.basic.issigned = targ->signedchar;
  qual = QUALNONE;
  typeadjvalist = typeadjust(targ->typevalist, &qual);
}
