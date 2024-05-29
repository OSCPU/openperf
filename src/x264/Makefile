NAME = x264
SRCS = 	main.c resources.S \
		../common/strings/strings.c \
		../common/fs/fs.c \
		../common/malloc/my_malloc.c

SRCS += $(shell find ../common/openlibm -name "*.c")

SRCS += $(shell find ../common/soft-fp/ -name "*.c")

SRCS += common/osdep.c common/base.c common/cpu.c common/tables.c \
       	encoder/api.c

SRCS += common/mc.c common/predict.c common/pixel.c common/macroblock.c \
		common/frame.c common/dct.c common/cabac.c \
		common/common.c common/rectangle.c \
		common/set.c common/quant.c common/deblock.c common/vlc.c \
		common/mvpred.c common/bitstream.c \
		encoder/analyse.c encoder/me.c encoder/ratecontrol.c \
		encoder/set.c encoder/macroblock.c encoder/cabac.c \
		encoder/cavlc.c encoder/encoder.c encoder/lookahead.c

CFLAGS += 	-I../common/openlibm/include \
			-I../common/openlibm/src \
			-I../common/fs \
			-I../common/malloc \
			-I../common/strings 

include $(AM_HOME)/Makefile

