INSTALL_PATH := "$OPENPERF_HOME/install/bin"

_compile:
    {{COMPILER}} -e _start -static -nostdlib -fno-builtin -fno-stack-protector -fdata-sections -ffunction-sections \
    -ffast-math -nostartfiles -g -Og -march=rv64ima -mabi=lp64 \
    -I$OPENPERF_HOME/src/common/klib/include \
    -I$OPENPERF_HOME/src/common/am/include \
    -I$OPENPERF_HOME/src/common/openlibm/include \
    -I$OPENPERF_HOME/src/common/openlibm/src \
    -o $OPENPERF_HOME/src/{{NAME}}/build/{{NAME}} {{SRC}} \
    `find $OPENPERF_HOME/src/common/am -name '*.c'` \
    `find $OPENPERF_HOME/src/common/soft-fp -name '*.c'` \
    `find $OPENPERF_HOME/src/common/klib -name '*.c'` \
    `find $OPENPERF_HOME/src/common/openlibm -name '*.c'` \
    `find $OPENPERF_HOME/src/common/am -name '*.S'` \
    -T$OPENPERF_HOME/src/common/am/src/linker.ld

run:
    spike ./build/{{NAME}}
