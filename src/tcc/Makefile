NAME = riscv-tcc

BENCH_LIBS = bench openlibm soft-fp

SRCS := tcc.c resources.S my_qsort.c fs.c

INC_PATH += 	../common/openlibm/include \
			../common/openlibm/src \
			./include \
			../common/bench/include

ifeq ($(mainargs), test)
CFLAGS += -D__BENCH_TEST__
ASFLAGS += -D__BENCH_TEST__
else ifeq ($(mainargs), train)
CFLAGS += -D__BENCH_TRAIN__
ASFLAGS += -D__BENCH_TRAIN__
else ifeq ($(mainargs), huge)
CFLAGS += -D__BENCH_HUGE__
ASFLAGS += -D__BENCH_HUGE__
else
CFLAGS += -D__BENCH_REF__
ASFLAGS += -D__BENCH_REF__
endif

include $(AM_HOME)/Makefile

BENCH_LINKAGE += $(addsuffix -$(ARCH).a, $(join \
					 $(addsuffix /build/, $(addprefix $(WORK_DIR)/../common/, $(BENCH_LIBS))), \
					 $(BENCH_LIBS) ))
#override variable LINKAGE, we should link soft-fp first.
LINKAGE   = $(OBJS)  $(BENCH_LINKAGE)\
  $(addsuffix -$(ARCH).a, $(join \
    $(addsuffix /build/, $(addprefix $(AM_HOME)/, $(LIBS))), \
    $(LIBS) ))
