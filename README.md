# OpenPerf Project

OpenPerf is an open source benchmark for evaluating test the performance of the microarchitecture in processor core, developed and be maintained by [One Student One Chip Project](https://ysyx.oscc.cc/).

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

## Community

### One Student One Chip Project

"One Student One Chip" is a public welfare learning program to supply talents & trained students to chip industry, which means registering and studying "One Student One Chip" is free. In the mainline, even if he or she has zero experience or skills, every student could learn deeply about how computer system works and create their own processor cores from scratch.

Visit [the main page](https://ysyx.oscc.cc/) to know more information.

### Ranking (Coming Soon)

The One Student One Chip Project is planning to build a ranking system for students! You can run OpenPerf with your NEMU or NPC to find out your performance and compare with others.

## Contributing

### Roadmap

- [x] Transplant benchmark programs
- [ ] Test the sensitivity of various programs
- [ ] Collect performance data from various open source processor cores
- [ ] Get early access

## Acknowledgement

Thanks to the Open Source Community for developing related programs & tools included in OpenPerf. To know more copyright info you can check the Licence headers in programs' code. The modification and additional features & code written by us is under Mulan PSL v2 Licence.

```
Copyright (c) 2024 One Student One Chip Project OpenPerf is licensed under Mulan PSL v2. You can use this software according to the terms and conditions of the Mulan PSL v2.

You may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2

THIS SOFTWARE IS PROVIDED ON AN “AS IS” BASIS, WITHOUT warranties of any kind, either express or implied, including but not limited to non-infringement, merchantability or fit for a particular purpose. See the Mulan PSL v2 for more details.
```
