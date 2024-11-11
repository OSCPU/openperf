NAME = cpuemu-$(mainargs)

mainargs ?= ref

BENCH_LIBS = bench openlibm soft-fp
# SRCS = test/top.cc resource.S test/mm.cc
# SRCS = train/emu.cc train/lshrdi3.c resource.S bench.cc

SRCS = main.cc resource.S test/top.cc test/mm.cc train/emu.cc ./configs/$(mainargs)-config.c

INC_PATH += 	../common/openlibm/include \
			../common/openlibm/src \
			./include \
			../common/bench/include

CXXFLAGS += -Wno-c++20-compat


include $(AM_HOME)/Makefile

BENCH_LINKAGE += $(addsuffix -$(ARCH).a, $(join \
					 $(addsuffix /build/, $(addprefix $(WORK_DIR)/../common/, $(BENCH_LIBS))), \
					 $(BENCH_LIBS) ))
#override variable LINKAGE, we should link soft-fp first.
LINKAGE   = $(OBJS)  $(BENCH_LINKAGE)\
  $(addsuffix -$(ARCH).a, $(join \
    $(addsuffix /build/, $(addprefix $(AM_HOME)/, $(LIBS))), \
    $(LIBS) ))

