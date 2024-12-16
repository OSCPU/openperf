{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs =
    { self, nixpkgs, ... }:
    let
      pkgs = import nixpkgs { system = "x86_64-linux"; };
      patchGccStdenv =
        pkgs: stdenv:
        pkgs.overrideCC stdenv (
          pkgs.wrapCC (
            stdenv.cc.cc.overrideAttrs (final: prev: { patches = prev.patches ++ [ ./fix-gcc-ice.patch ]; })
          )
        );
      crossSystem = {
        config = "riscv32-none-none-elf";
        gcc = {
          abi = "ilp32";
          arch = "rv32i";
        };
      };
      localSystem = "x86_64-linux";
      rv32CrossPkgs = import nixpkgs {
        inherit localSystem crossSystem;
      };
      rv32LLVMCrossPkgs = import nixpkgs {
        inherit localSystem;
        crossSystem = crossSystem // {
          useLLVM = true;
        };
      };
      bareClangStdenv =
        with rv32LLVMCrossPkgs;
        overrideCC clangStdenv buildPackages.llvmPackages.clangNoLibcNoRt;

      nemuDepsBuildBuild = with pkgs; [
        gnumake
        SDL2
        pkg-config
        bison
        flex
        ncurses
        readline
        libllvm
        gcc
        clang
        (python3.withPackages (
          ps: with ps; [
            tqdm
            pyyaml
          ]
        ))
      ];
    in
    {
      devShells.x86_64-linux = rec {
        nemu = rv32CrossPkgs.gccStdenvNoLibs.mkDerivation {
          name = "openperf";
          depsBuildBuild = nemuDepsBuildBuild;

          AM_HOME = "/home/xin/repo/openperf/abstract-machine";
          NEMU_HOME = "/home/xin/repo/openperf/openperf-nemu";
        };

        nemu-clang = bareClangStdenv.mkDerivation {
          name = "openperf";
          depsBuildBuild = nemuDepsBuildBuild;
          AM_HOME = "/home/xin/repo/openperf/abstract-machine";
          NEMU_HOME = "/home/xin/repo/openperf/openperf-nemu";
        };

        native =
          pkgs.mkShell.override
            {
              stdenv = patchGccStdenv pkgs pkgs.stdenv;
            }
            {
              name = "openperf";
              buildInputs = with pkgs; [
                gnumake
                SDL2
              ];
            };

        riscv32-nemu = nemu;
      };
      packages.x86_64-linux = {
        makefile2graph = pkgs.makefile2graph.overrideAttrs (
          final: prev: {
            version = "2023-08-31";
            src = pkgs.fetchFromGitHub {
              owner = "lindenb";
              repo = "makefile2graph";
              rev = "f388f3558a586f98cdac64db3db25ca4cb8eb710";
              hash = "sha256-8RGV7k+DMET0LaZeiAy4Xz/SEPHmMX1KMrY86zWAJ5I=";
            };
          }
        );
      };
    };
}
