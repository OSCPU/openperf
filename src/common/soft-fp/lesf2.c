#include "soft-fp.h"
#include "single.h"

CMPtype
__lesf2 (SFtype a, SFtype b)
{
  FP_DECL_EX;
  FP_DECL_S (A);
  FP_DECL_S (B);
  CMPtype r;

  FP_INIT_EXCEPTIONS;
  FP_UNPACK_RAW_S (A, a);
  FP_UNPACK_RAW_S (B, b);
  FP_CMP_S (r, A, B, 2, 2);
  FP_HANDLE_EXCEPTIONS;

  return r;
}

strong_alias (__lesf2, __ltsf2);

