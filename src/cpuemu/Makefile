_CPUEMU_SRCS := main.cc resource.S test/top.cc test/mm.cc train/emu.cc configs/$(mainargs)-config.cc
CPUEMU_SRCS := $(addprefix src/cpuemu/, $(_CPUEMU_SRCS))

CPUEMU_INCPATH += src/common/openlibm/include \
                  src/common/openlibm/src \
                  src/cpuemu/include \
                  src/common/bench/include

CPUEMU_CFLAGS := $(CFLAGS) $(AM_CFLAGS) $(addprefix -I, $(CPUEMU_INCPATH))
CPUEMU_CXXFLAGS := $(CXXFLAGS) $(AM_CFLAGS) $(addprefix -I, $(CPUEMU_INCPATH)) -Wno-c++20-compat -std=c++17
CPUEMU_LDFLAGS := $(LDFLAGS) $(AM_LDFLAGS)
CPUEMU_ASFLAGS := $(AM_CFLAGS) -Isrc/cpuemu

$(eval $(call ADD_IMAGE,$(BUILDDIR)/images/cpuemu-$(mainargs),CPUEMU_))
