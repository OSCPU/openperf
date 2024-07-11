NAME = x264

BENCH_LIBS = openlibm soft-fp


SRCS = 	main.c resources.S printf.c my_malloc.c fs.c strings.c
SRCS += $(shell find ./common/ -name "*.c")
SRCS += $(shell find ./encoder/ -name "*.c" -not -name "rdo.c" -not -name "slicetype.c")

INC_PATH += ../common/openlibm/include \
			../common/openlibm/src \
			./include 


include $(AM_HOME)/Makefile

LINKAGE += $(addsuffix -$(ARCH).a, $(join \
					 $(addsuffix /build/, $(addprefix $(WORK_DIR)/../common/, $(BENCH_LIBS))), \
					 $(BENCH_LIBS) ))

