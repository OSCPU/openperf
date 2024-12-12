_MCF_SRCS = main.c mcf.c pqueue.c ./configs/$(mainargs)-config.c
MCF_SRCS := $(addprefix src/mcf/, $(_MCF_SRCS)) 
MCF_INCPATH += src/common/openlibm/include \
               src/common/openlibm/src \
               src/mcf/include \
               src/common/bench/include

MCF_CFLAGS := $(CFLAGS) $(AM_CFLAGS) $(addprefix -I, $(MCF_INCPATH))
MCF_LDFLAGS := $(LDFLAGS) $(AM_LDFLAGS)

$(eval $(call ADD_IMAGE,$(BUILDDIR)/images/mcf,MCF_))

