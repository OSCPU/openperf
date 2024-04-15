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
    pkgs.url = "pkgs";
  };

  outputs = {
    self,
    pkgs,
  }: let
    stdpkgs = pkgs.legacyPackages.x86_64-linux;
  in {
    formatter.x86_64-linux = stdpkgs.alejandra;
    devShells.x86_64-linux.default = stdpkgs.mkShell {
      name = "qemu-linux-riscv-dev";

      packages = [stdpkgs.qemu];
    };
  };
}
