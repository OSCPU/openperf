NAME = rtlsim

mainargs ?= ref

SIM_CORE ?= minimal-xiangshan

ifeq ($(mainargs),ref)
	SIM_CORE = minimal-xiangshan
else ifeq ($(mainargs), train)
	SIM_CORE = rocket
else ifeq ($(mainargs), test)
	SIM_CORE = NutShell
endif

SRC_PATH = $(SIM_CORE) emu

SRCS := $(foreach x, $(SRC_PATH), $(wildcard $(x)/*.cpp) $(wildcard $(x)/*.c) $(wildcard $(x)/*.S))
INC_PATH += $(SIM_CORE) include

include $(AM_HOME)/Makefile

BENCH_LINKAGE = $(addsuffix -$(ARCH).a, $(join \
					 $(addsuffix /build/, $(addprefix $(WORK_DIR)/../common/, $(BENCH_LIBS))), \
					 $(BENCH_LIBS) ))

#override variable LINKAGE, we should link soft-fp first.
LINKAGE   = $(OBJS)  $(BENCH_LINKAGE)\
  $(addsuffix -$(ARCH).a, $(join \
    $(addsuffix /build/, $(addprefix $(AM_HOME)/, $(LIBS))), \
    $(LIBS) ))
