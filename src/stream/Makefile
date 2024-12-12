_STREAM_SRCS := stream.c configs/$(mainargs)-config.c
STREAM_SRCS := $(addprefix src/stream/, $(_STREAM_SRCS))
STREAM_INCPATH += src/common/openlibm/include \
                  src/common/openlibm/src \
                  src/stream/include \
                  src/common/bench/include

STREAM_CFLAGS := $(CFLAGS) $(AM_CFLAGS) $(addprefix -I, $(STREAM_INCPATH))
STREAM_LDFLAGS := $(LDFLAGS) $(AM_LDFLAGS)

$(eval $(call ADD_IMAGE,$(BUILDDIR)/images/stream,STREAM_))

