# OpenPerf Project

OpenPerf is an open source benchmark aims to test the performance of the microarchitechture in processor core, developed and be mantained by [One Student One Chip Project](https://ysyx.org).

# How to use

This project is planning to integrate with [YSYX's workbench](https://github.com/OSCPU/ysyx-workbench) and [NJU ProjectN](https://github.com/NJU-ProjectN).

To use openperf in baseline practice, clone it into your project's [AbstractMachine Kernels](https://github.com/NJU-ProjectN/am-kernels).

```sh
cd am-kernels
git clone git@github.com:OSCPU/openperf.git
cd openperf
make ARCH= ... # NOTICE: `...` is not a part of the make command and you need to write it by yourself.
```

The make recipe just like other benchmark programs in `am-kernel` that you can decide the Architectures and the test scale.

## Benchmark Programs

<!-- [stress-ng - GPL 2.0 Licence](https://github.com/ColinIanKing/stress-ng) -->
<!---->
<!-- [Anybench - MIT Licence](https://github.com/EntityFX/anybench) -->
<!---->
<!-- ### Memory access patterns -->
<!---->
<!-- #### Stream access -->
<!---->
<!-- [STREAM - Custom Licence, but Open Source friendly](https://github.com/jeffhammond/STREAM) -->
<!---->
<!-- [RRZE-HPC/TheBandwidthBenchmark - MIT Licence](https://github.com/RRZE-HPC/TheBandwidthBenchmark?tab=readme-ov-file) -->
<!---->
<!-- #### Other patterns -->
<!---->
<!-- [emilk/ram_bench - No Licence](https://github.com/emilk/ram_bench) -->
<!---->
<!-- ### Integer Arithmetic -->
<!---->
<!-- [shaswata56/BenchUtil - WTFPL license](https://github.com/shaswata56/BenchUtil?tab=readme-ov-file) -->
<!---->
<!-- ### Floating-point Arithmetic -->
<!---->
<!-- [shaswata56/BenchUtil - WTFPL license](https://github.com/shaswata56/BenchUtil?tab=readme-ov-file) -->
<!---->
<!-- ### Branch Prediction -->
<!---->
<!-- Verilator Model -->
<!---->

* Stream Memory Access: STREAM
* Irregular Memory Access: mcf
* Float Memory: GEMM
* Footprint: Gsim and essent which verilate various RISC-V processor cores like riscv-mini, Nutshell, Rocket Core, BOOM and XiangShan
* Branch Prediction: TCC
* Floating-point Arithmetic: Linpack, Whetstone
* Utils: soft-fp(cyl), abstract-machine, openlibm

## Ranking (Coming Soon)

One Student One Chip Project is planning to build a rank for students! You can run OpenPerf with your NEMU or NPC to figure out the performance, and compare to others.

## Contribute Guide

### Roadmap

- [x] Transplant benchmark programs
- [ ] Test the sensitivity of different programs
- [ ] Early Access
