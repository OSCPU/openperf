_TCC_SRCS := tcc.c my_qsort.c fs.c ./configs/$(mainargs)-config.c ./resources/resources-$(mainargs).S
TCC_SRCS := $(addprefix src/tcc/, $(_TCC_SRCS))

TCC_INCPATH += src/common/openlibm/include \
               src/common/openlibm/src \
               src/tcc/include \
               src/common/bench/include

TCC_CFLAGS := $(CFLAGS) $(AM_CFLAGS) $(addprefix -I, $(TCC_INCPATH))
TCC_LDFLAGS := $(LDFLAGS) $(AM_LDFLAGS)
TCC_ASFLAGS := $(AM_ASFLAGS) -Isrc/tcc

$(eval $(call ADD_IMAGE,$(BUILDDIR)/images/tcc-$(mainargs),TCC_))

