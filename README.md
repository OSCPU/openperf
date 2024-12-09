# OpenPerf Project

OpenPerf is an open source benchmark for evaluating test the performance of the microarchitecture in processor core, developed and be maintained by [One Student One Chip Project](https://ysyx.org).

# How to use

This project plans to integrate with [YSYX's workbench](https://github.com/OSCPU/ysyx-workbench) and [NJU ProjectN](https://github.com/NJU-ProjectN).

To use openperf in baseline practice, clone it into your project's [AbstractMachine Kernels](https://github.com/NJU-ProjectN/am-kernels).

```sh
cd am-kernels
git clone git@github.com:OSCPU/openperf.git
cd openperf
make ARCH= ... # NOTICE: `...` is not a part of the make command and you need to write it by yourself.
```

The make recipe, like other benchmark programs in `am-kernel`, allows you to choose the architectures and the test scale.

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
* Footprint: Gsim and essent which simulate various RISC-V processor cores such as riscv-mini, Nutshell, Rocket Core, BOOM and XiangShan
* Branch Prediction: TCC
* Floating-point Arithmetic: Linpack, Whetstone
* Utils: soft-fp(cyl), abstract-machine, openlibm

## Ranking (Coming Soon)

The One Student One Chip Project is planning to build a ranking system for students! You can run OpenPerf with your NEMU or NPC to find out your performance and compare with others.

## Contribute Guide

### Roadmap

- [x] Transplant benchmark programs
- [ ] Test the sensitivity of various programs
- [ ] Collect performance data from various open source processor cores
- [ ] Get early access
