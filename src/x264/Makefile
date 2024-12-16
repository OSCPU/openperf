_X264_SRCS := main.c resources/resources-$(mainargs).S configs/$(mainargs)-config.c fs.c
X264_SRCS := $(addprefix src/x264/, $(_X264_SRCS))
X264_SRCS += $(shell find src/x264/common/ -name "*.c")
X264_SRCS += $(shell find src/x264/encoder/ -name "*.c" -not -name "rdo.c" -not -name "slicetype.c")

X264_INCPATH += src/common/openlibm/include \
                src/common/openlibm/src \
                src/x264/include \
                src/common/bench/include

X264_CFLAGS := $(CFLAGS) $(AM_CFLAGS) $(addprefix -I, $(X264_INCPATH))
X264_LDFLAGS := $(LDFLAGS) $(AM_LDFLAGS)
X264_ASFLAGS := $(AM_ASFLAGS) -Isrc/x264

$(eval $(call ADD_IMAGE,$(BUILDDIR)/images/x264-$(mainargs),X264_))

