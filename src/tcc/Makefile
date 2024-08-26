NAME = riscv-tcc

BENCH_LIBS = bench openlibm soft-fp

SRCS := tcc.c resources.S my_qsort.c fs.c

INC_PATH += 	../common/openlibm/include \
			../common/openlibm/src \
			./include \
			../common/bench/include

CFLAGS += -D__BENCH_TEST__
ASFLAGS += -D__BENCH_TEST__

include $(AM_HOME)/Makefile

BENCH_LINKAGE += $(addsuffix -$(ARCH).a, $(join \
					 $(addsuffix /build/, $(addprefix $(WORK_DIR)/../common/, $(BENCH_LIBS))), \
					 $(BENCH_LIBS) ))
#override variable LINKAGE, we should link soft-fp first.
LINKAGE   = $(OBJS)  $(BENCH_LINKAGE)\
  $(addsuffix -$(ARCH).a, $(join \
    $(addsuffix /build/, $(addprefix $(AM_HOME)/, $(LIBS))), \
    $(LIBS) ))
