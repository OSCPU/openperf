ARCH ?= # Note that ARCH must be provided
AM_ROOT ?= $(AM_HOME)/build/install/$(ARCH)

include $(AM_ROOT)/lib/make/rules.mk
include $(AM_ROOT)/lib/make/flags-$(ARCH).mk

DUMMY_SRCS := dummy.c
DUMMY_OBJS := /home/xin/repo/openperf/build/lib/libbench.a 
DUMMY_CFLAGS := $(AM_CFLAGS) -I/home/xin/repo/openperf/src/common/bench/include
DUMMY_LDFLAGS := $(AM_LDFLAGS) -L/home/xin/repo/openperf/build/lib -lbench

BUILDDIR := /home/xin/repo/openperf/src/test/build
$(eval $(call ADD_IMAGE,$(BUILDDIR)/add,DUMMY_))

