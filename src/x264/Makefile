NAME = x264-$(mainargs)

BENCH_LIBS = bench openlibm soft-fp

mainargs ?= ref

SRCS = 	main.c ./resources/resources-$(mainargs).S ./configs/$(mainargs)-config.c fs.c
SRCS += $(shell find ./common/ -name "*.c")
SRCS += $(shell find ./encoder/ -name "*.c" -not -name "rdo.c" -not -name "slicetype.c")

INC_PATH += ../common/openlibm/include \
			../common/openlibm/src \
			./include \
			../common/bench/include

DST_DIR   := $(WORK_DIR)/build/$(ARCH)-$(mainargs)

include $(AM_HOME)/Makefile

CFLAGS += -Wno-array-bounds

BENCH_LINKAGE += $(addsuffix -$(ARCH).a, $(join \
					 $(addsuffix /build/, $(addprefix $(WORK_DIR)/../common/, $(BENCH_LIBS))), \
					 $(BENCH_LIBS) ))
#override variable LINKAGE, we should link soft-fp first.
LINKAGE   = $(OBJS)  $(BENCH_LINKAGE)\
  $(addsuffix -$(ARCH).a, $(join \
    $(addsuffix /build/, $(addprefix $(AM_HOME)/, $(LIBS))), \
    $(LIBS) ))
