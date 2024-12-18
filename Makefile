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
### (Cross) compilers, e.g., mips-linux-gnu-g++
CC ?= $(CROSS_COMPILE)gcc
CXX ?= $(CROSS_COMPILE)g++
AR ?= $(CROSS_COMPILE)ar
OBJCOPY ?= $(CROSS_COMPILE)objcopy
# $(AS) does not do preprocessing. Since we are using includes
# in assembly source code, we need to use $(CC) as frontend
# to invoke assembler.
AS := $(CC)
# We use $(CC) as a frontend to invoke $(LD)
LD := 


ARCH ?= # Note that ARCH must be provided
# setup directories
WORK_DIR  ?= $(shell pwd)
DST_DIR   ?= $(WORK_DIR)/build
BUILDDIR ?= $(DST_DIR)
LIB_BUILDDIR ?= $(DST_DIR)/lib
INSTALLDIR ?= $(WORK_DIR)/build/install/$(ARCH)
LIB_INSTALLDIR ?= $(INSTALLDIR)/lib
INC_INSTALLDIR ?= $(INSTALLDIR)/include

# Find dependency
AM_ROOT ?= $(AM_HOME)/build/install/$(ARCH)
# Set PKG_CONFIG_PATH to look in AM_ROOT first, then system paths
PKG_CONFIG_PATH := $(AM_ROOT)/lib/pkgconfig:$(PKG_CONFIG_PATH)
export PKG_CONFIG_PATH
AM_CFLAGS := $(shell pkg-config --cflags abstract-machine)
AM_LDFLAGS := $(shell pkg-config --libs abstract-machine)
$(info AM_CFLAGS = $(AM_CFLAGS))
$(info AM_LDFLAGS = $(AM_LDFLAGS))

include $(AM_ROOT)/lib/make/rules.mk

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
$(addsuffix -$(mainargs).elf, $(addprefix $(BUILDDIR)/images/, $(IMAGES))): %: $(addprefix $(LIB_BUILDDIR)/, $(LIBS))
all: $(addsuffix -$(mainargs).bin, $(addprefix $(BUILDDIR)/images/, $(IMAGES)))

test_config.yaml:
	cp test_config.example.yaml test_config.yaml

run: all test_config.yaml
	@echo "OpenPerf [$(words $(ALL)) item(s)]:" $(ALL)
	@if [ -z "$(mainargs)" ]; then \
		echo "Empty mainargs, use \"ref\" by default"; \
		echo "====== Running OpenPerf [input *ref*] ======"; \
	else \
		echo "====== Running OpenPerf [input *$${mainargs}*] ======"; \
	fi
	python3 scripts/run.py test_config.yaml

.PHONY: $(BENCH_LIBS) $(CLEAN_ALL) $(ALL) all run clean

clean:
	$(RM) -r $(BUILDDIR)

