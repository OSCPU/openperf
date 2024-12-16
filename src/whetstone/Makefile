_WHETSTONE_SRCS = whetstone.c ./configs/$(mainargs)-config.c
WHETSTONE_SRCS := $(addprefix src/whetstone/, $(_WHETSTONE_SRCS))
WHETSTONE_INCPATH += src/common/openlibm/include \
                   src/common/openlibm/src \
                   src/whetstone/include \
                   src/common/bench/include

WHETSTONE_CFLAGS := $(CFLAGS) $(AM_CFLAGS) $(addprefix -I, $(WHETSTONE_INCPATH))
WHETSTONE_LDFLAGS := $(LDFLAGS) $(AM_LDFLAGS)

$(eval $(call ADD_IMAGE,$(BUILDDIR)/images/whetstone-$(mainargs),WHETSTONE_))

