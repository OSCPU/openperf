# Copyright (c) 2024 Yakkhini sign@yechanv.cc
# QEMULinuxDevFlake is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan
# PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#          http://license.coscl.org.cn/MulanPSL2
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
# KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PSL v2 for more details.
{
  description = "Flake which declare a reproducible environment to run RISC-V Linux on QEMU.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";
    unstable.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
    ...
  } @ inputs: let
    stdpkgs = nixpkgs.legacyPackages.x86_64-linux;
    unstablepkgs = inputs.unstable.legacyPackages.x86_64-linux;
    riscv-toolchain = import inputs.unstable {
      localSystem = "x86_64-linux";
      crossSystem = {
        config="riscv64-unknown-linux-gnu";
        gcc = {abi = "lp64";};
      };
    };
  in rec {
    formatter.x86_64-linux = stdpkgs.alejandra;
    devShells.x86_64-linux.default = stdpkgs.mkShell {
      name = "opmark-riscv-dev";

      packages = [
        stdpkgs.just
        packages.qemu-linux-riscv-dev
        stdpkgs.gcc
        stdpkgs.bear
        stdpkgs.clang-tools
        stdpkgs.libtool
        stdpkgs.spike
        stdpkgs.dtc
        stdpkgs.nil
        stdpkgs.qemu
        stdpkgs.gdb
        unstablepkgs.pkgsCross.riscv64.buildPackages.gdb
        riscv-toolchain.buildPackages.gcc
        stdpkgs.pkgsCross.riscv64.opensbi
        stdpkgs.automake
        stdpkgs.autoconf
        stdpkgs.texinfo
        stdpkgs.pkg-config
      ];

      RISCV="${unstablepkgs.pkgsCross.riscv64.buildPackages.gcc}/bin";

      shellHook = ''
        export OPENPERF_HOME=`pwd`
        export PATH="$OPENPERF_HOME/install/bin:$PATH"
      '';
    };

    packages.qemu-linux-riscv-dev = let
      closure = nixosConfigurations.minimal.config.system.build.toplevel;
    in
      stdpkgs.writeShellScriptBin "vm" ''
        qemu-system-riscv64 -M virt -m 4G -smp 4 \
          -kernel ${closure}/kernel \
          -initrd ${closure}/initrd\
          -append "$(cat ${closure}/kernel-params) init=${closure}/init" \
          -device virtio-rng-pci \
          -netdev user,id=net0 -device virtio-net-pci,netdev=net0 \
          -fsdev local,security_model=passthrough,id=nix-store,path=/nix/store,readonly=on \
          -device virtio-9p-pci,id=nix-store,fsdev=nix-store,mount_tag=nix-store \
          -nographic
      '';

    nixosConfigurations.minimal = nixpkgs.lib.nixosSystem {
      system = "x86_64-linux";
      specialArgs = inputs;
      modules = [
        ./configuration.nix
        "${nixpkgs}/nixos/modules/profiles/minimal.nix"
        {
          nixpkgs.crossSystem = {
            # target platform
            system = "riscv64-linux";
          };
        }
      ];
    };
  };
}
