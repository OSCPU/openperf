_GEMM_SRCS := gemm.c matmul.c ./configs/$(mainargs)-config.c
GEMM_SRCS := $(addprefix src/gemm/, $(_GEMM_SRCS))
GEMM_INCPATH += src/common/openlibm/include \
                src/common/openlibm/src \
                src/gemm/include \
                src/common/bench/include

GEMM_CFLAGS := $(CFLAGS) $(AM_CFLAGS) $(addprefix -I, $(GEMM_INCPATH))
GEMM_LDFLAGS := $(LDFLAGS) $(AM_LDFLAGS)

$(eval $(call ADD_IMAGE,$(BUILDDIR)/images/gemm-$(mainargs),GEMM_))

