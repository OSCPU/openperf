LINPACK_SRCS := src/linpack/linpack.c src/linpack/configs/$(mainargs)-config.c
LINPACK_INCPATH += src/common/openlibm/include \
                   src/common/openlibm/src \
                   src/linpack/include \
                   src/common/bench/include

LINPACK_CFLAGS := $(CFLAGS) $(AM_CFLAGS) $(addprefix -I, $(LINPACK_INCPATH))
LINPACK_LDFLAGS := $(LDFLAGS) $(AM_LDFLAGS)

$(eval $(call ADD_IMAGE,$(BUILDDIR)/images/linpack,LINPACK_))

