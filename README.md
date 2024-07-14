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

## How to compile & run programs in Spike

With `just` installed, run `just compile` then `just run` in the program source code directory.

Or you can run commands manually. `Justfile` is extremely easy to read and understand.

## Development Environment & Testing

```sh
cd am-kernel # This project would be a submodule in am-kernel when it's finish
git clone git@github.com:Yakkhini/OPMark.git
cd OPMark
# git switch [branch] # Maybe you want to contribute to another branch
cp -r src/common/stdio.c $AM_HOME/klib/src/stdio.c # We improve printf functions feature, like print float numbers
cd src/linpack # Run a sub program to ensure build system working
make ARCH=riscv32-nemu run
```

## Transplanted

* Memory Access: STREAM
* Floating-point Arithmetic: Linpack, Whetstone
* Utils: soft-fp(cyl), abstract-machine, openlibm
* Can build: Spike, RISC-V OpenOCD

## Roadmap

- [x] Run Configurable Linux on QEMU RISC-V Platform
- [x] Basic Benchmark Programs
- [x] Math Library
- [x] GEMM
- [x] Organize Build Scripts
- [x] More Complex Programs
- [ ] Embedded into am-kernel
- [ ] Handle with Licence
- [ ] Merge into single benchmark program
- [ ] Decide OpenPerf Project File Struct
