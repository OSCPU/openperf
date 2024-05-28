NAME = mcf
SRCS = main.c mcf.c pqueue.c test.c

SRCS = 	main.c mcf.c pqueue.c test.c \
		../common/malloc/my_malloc.c

SRCS += $(shell find ../common/openlibm -name "*.c")
SRCS += $(shell find ../common/soft-fp/ -name "*.c")

CFLAGS += 	-I../common/openlibm/include \
			-I../common/openlibm/src \
			-I../common/malloc

include $(AM_HOME)/Makefile

