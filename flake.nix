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
  in rec {
    formatter.x86_64-linux = stdpkgs.alejandra;
    devShells.x86_64-linux.default = stdpkgs.mkShell {
      name = "qemu-linux-riscv-dev";

      packages = [
        packages.qemu-linux-riscv-dev
        stdpkgs.nil
        stdpkgs.qemu
        unstablepkgs.pkgsCross.riscv64.buildPackages.gcc
        stdpkgs.pkgsCross.riscv64.opensbi
      ];
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
