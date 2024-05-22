# OPMark (Prototype of OpenPerf Project)

This Flake give a Qemu RISC-V Linux / Spike bare metal runtime to run benchmark, aim to make test environment reproducible and result fair enough.

## Candidate Benchmark Programs

[stress-ng - GPL 2.0 Licence](https://github.com/ColinIanKing/stress-ng)

[Anybench - MIT Licence](https://github.com/EntityFX/anybench)

### Memory access patterns

#### Stream access

[STREAM - Custom Licence, but Open Source friendly](https://github.com/jeffhammond/STREAM)

[RRZE-HPC/TheBandwidthBenchmark - MIT Licence](https://github.com/RRZE-HPC/TheBandwidthBenchmark?tab=readme-ov-file)

#### Other patterns

[emilk/ram_bench - No Licence](https://github.com/emilk/ram_bench)

### Integer Arithmetic

[shaswata56/BenchUtil - WTFPL license](https://github.com/shaswata56/BenchUtil?tab=readme-ov-file)

### Floating-point Arithmetic

[shaswata56/BenchUtil - WTFPL license](https://github.com/shaswata56/BenchUtil?tab=readme-ov-file)

### Branch Prediction

Verilator Model

## Run Built-in QEMU VM

A Nix Flake is provided for convenience, but not necessary dependency in the final project.

With Nix installed, run `nix develop` to get the reproducible development environment.

Run `vm` to launch QEMU.

## Transplanted

* Memory Access: STREAM
* Floating-point Arithmetic: Linpack, Whetstone
* Utils: soft-fp(cyl), abstract-machine, openlibm
* Can build: Spike, RISC-V OpenOCD

## Roadmap

- [x] Run Configurable Linux on QEMU RISC-V Platform
- [x] Basic Benchmark Programs
- [x] Math Library
- [ ] GEMM
- [ ] Organize Build Scripts
- [ ] More Complex Programs
- [ ] Decide OpenPerf Project File Struct