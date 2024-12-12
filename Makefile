COLOR_RED   = \033[1;31m
COLOR_GREEN = \033[1;32m
COLOR_NONE  = \033[0m

RESULT = .result
$(shell > $(RESULT))

KEEP_LOG_FAILED ?= true
KEEP_LOG_SUCCEED ?= false
TIME := $(shell date --iso=seconds)

ifeq ($(mainargs),ref)
IMAGES := mcf x264 tcc stream linpack gemm whetstone
else
IMAGES := cpuemu mcf x264 tcc stream linpack gemm whetstone
endif

# Toolchain settings
AS := $(CC)

ARCH ?= # Note that ARCH must be provided
# dependency
AM_ROOT ?= $(AM_HOME)/build/install/$(ARCH)
# setup directories
WORK_DIR  ?= $(shell pwd)
DST_DIR   ?= $(WORK_DIR)/build
BUILDDIR ?= $(DST_DIR)
LIB_BUILDDIR ?= $(DST_DIR)/lib
INSTALLDIR ?= $(WORK_DIR)/build/install/$(ARCH)
LIB_INSTALLDIR ?= $(INSTALLDIR)/lib
INC_INSTALLDIR ?= $(INSTALLDIR)/include

include $(AM_ROOT)/lib/make/rules.mk
include $(AM_ROOT)/lib/make/flags-$(ARCH).mk

# Rules to build common libraries
BENCH_SRCS := $(shell find src/common/bench -name "*.c")
BENCH_CFLAGS := $(CFLAGS) $(AM_CFLAGS) -I$(shell realpath ./src/common/bench/include)

$(eval $(call ADD_LIBRARY,$(LIB_BUILDDIR)/libbench.a,BENCH_))

OPENLIBM_SRCS := $(shell find src/common/openlibm/src -name "*.c")
OPENLIBM_CFLAGS := $(CFLAGS) $(AM_CFLAGS) -I$(shell realpath ./src/common/openlibm/include)

$(eval $(call ADD_LIBRARY,$(LIB_BUILDDIR)/libopenlibm.a,OPENLIBM_))

SOFTFP_SRCS := $(shell find src/common/soft-fp -name "*.c")
SOFTFP_CFLAGS := $(CFLAGS) $(AM_CFLAGS)

$(eval $(call ADD_LIBRARY,$(LIB_BUILDDIR)/libsoftfp.a,SOFTFP_))

LIBS := libbench.a libopenlibm.a libsoftfp.a
libs: $(addprefix $(LIB_BUILDDIR)/, $(LIBS))

LDFLAGS += -L$(LIB_BUILDDIR) -lbench -lopenlibm -lsoftfp 

include $(addsuffix /Makefile, $(addprefix src/, $(IMAGES)))

# Add libs to dependency of every image
$(addsuffix .elf, $(addprefix $(BUILDDIR)/images/, $(IMAGES))): %: $(addprefix $(LIB_BUILDDIR)/, $(LIBS))
all: $(addsuffix .bin, $(addprefix $(BUILDDIR)/images/, $(IMAGES)))
	@echo "OpenPerf [$(words $(ALL)) item(s)]:" $(ALL)
	@if [ -z "$(mainargs)" ]; then \
		echo "Empty mainargs, use \"ref\" by default"; \
		echo "====== Running OpenPerf [input *ref*] ======"; \
	else \
		echo "====== Running OpenPerf [input *$${mainargs}*] ======"; \
	fi

$(ALL): %: $(BENCH_LIBS)
	@{\
		  TMP=$*.tmp;\
	    $(MAKE) -C ./src/$* ARCH=$(ARCH) run 2>&1 | tee -a $$TMP;\
     if [ $${PIPESTATUS[0]} -eq 0 ]; then \
		    printf "[%14s] $(COLOR_GREEN)PASS$(COLOR_NONE) " $* >> $(RESULT); \
		    cat $$TMP | grep -E -i -e "OpenPerf time: ([0-9]*\.)?[0-9]*" >> $(RESULT); \
				if $(KEEP_LOG_SUCCEED); then \
					mkdir -p "logs/$(TIME)/"; \
					mv $$TMP "logs/$(TIME)/"; \
				else \
					rm $$TMP; \
				fi \
	    else \
			  printf "[%14s] $(COLOR_RED)***FAIL***$(COLOR_NONE)\n" $* >> $(RESULT); \
				if $(KEEP_LOG_FAILED); then \
					mkdir -p "logs/$(TIME)/"; \
					mv $$TMP "logs/$(TIME)/"; \
				else \
					rm $$TMP; \
				fi \
	    fi \
	}

run: $(BENCH_LIBS) all
	@cat $(RESULT)
	@echo "============================================="
	@awk '\
		BEGIN {total_us = 0 } \
		{ \
			h = min = s = ms = us = 0;\
			if (match($$0, /([0-9]+) h/, arr)) h = arr[1]; \
    	if (match($$0, /([0-9]+) min/, arr)) min = arr[1]; \
    	if (match($$0, /([0-9]+) s/, arr)) s = arr[1]; \
			if (match($$0, /([0-9]+)\.([0-9]*) ms/, arr)) {ms = arr[1]; us = arr[2];} \
    	total_us += h * 3600 * 1000 * 1000 + min * 60 * 1000 * 1000 + s * 1000 * 1000 + ms * 1000 + us; \
		} \
		END { \
			printf "Total time: %d h %d min %d s %d.%d ms\n", \
        int(total_us / (3600 * 1000 * 1000)), \
        int((total_us % (3600 * 1000 * 1000)) / (60 * 1000 * 1000)), \
        int((total_us % (60 * 1000 * 1000)) / (1000 * 1000)), \
        int((total_us % (1000 * 1000) / 1000)), \
				total_us % 1000; \
	} \
	' $(RESULT)
	@if grep -q -i -e "fail" "$(RESULT)"; then \
		echo "OpenPerf FAIL"; \
		rm $(RESULT); \
		exit 1; \
	else \
		echo "OpenPerf PASS"; \
		rm $(RESULT); \
		exit 0; \
	fi

.PHONY: $(BENCH_LIBS) $(CLEAN_ALL) $(ALL) all run clean

clean:
	$(RM) -r $(BUILDDIR)

