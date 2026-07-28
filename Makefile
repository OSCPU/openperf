ifeq ($(wildcard $(BENCH_HOME)/libbench/bench.c),)
	$(error $$BENCH_HOME is not set correctly)
endif

LIBBENCH_PATH = $(BENCH_HOME)/libbench
INC_PATH += $(LIBBENCH_PATH)/include

ifdef ARCH
LIBBENCH_A = $(LIBBENCH_PATH)/build/libbench-$(ARCH).a
MK = $(AM_HOME)/Makefile
else ifdef TARGET
LIBBENCH_A = $(LIBBENCH_PATH)/build/libbench-$(TARGET).a
MK = $(NAVY_HOME)/Makefile
else ifeq ($(MAKECMDGOALS),clean)
MK = $(AM_HOME)/Makefile
else
$(error Should specify ARCH=xxx for AM or TARGET=xxx for Navy-apps)
endif

ifdef diskfilelist
$(shell bash $(BENCH_HOME)/scripts/select-input.sh "$(diskfilelist)" "$(mainargs)")
endif

LINKAGE += $(LIBBENCH_A)
include $(MK)

ifneq ($(MAKECMDGOALS),archive)
$(LIBBENCH_A): force
	@$(MAKE) -s -C $(LIBBENCH_PATH) archive
endif
