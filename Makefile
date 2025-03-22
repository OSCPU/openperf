ifeq ($(wildcard $(BENCH_HOME)/libbench/bench.c),)
	$(error $$BENCH_HOME is not set correctly)
endif

LIBBENCH_PATH = $(BENCH_HOME)/libbench
LIBBENCH_A = $(LIBBENCH_PATH)/build/libbench-$(TARGET).a

INC_PATH += $(LIBBENCH_PATH)/include
LINKAGE += $(LIBBENCH_A)

include $(NAVY_HOME)/Makefile

$(LIBBENCH_A): force
	@$(MAKE) -s -C $(LIBBENCH_PATH) archive
