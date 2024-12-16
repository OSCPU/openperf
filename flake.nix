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
        };

        nemu-clang = bareClangStdenv.mkDerivation {
          name = "openperf";
          depsBuildBuild = nemuDepsBuildBuild;
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
    };
}
