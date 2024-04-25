{
  pkgs,
  lib,
  ...
}: {
  boot.kernelPackages = pkgs.linuxPackages_6_6;
  boot.loader.systemd-boot.enable = true;
  boot.kernelParams = ["console=ttyS0" "earlycon"];
  boot.initrd.availableKernelModules = ["pci_host_generic" "virtio_pci" "9p" "9pnet_virtio"];

  services.getty.autologinUser = "root";

  fileSystems = {
    "/" = {
      device = "none";
      fsType = "tmpfs";
      options = ["defaults" "mode=755"];
    };

    "/nix/store" = {
      device = "nix-store";
      fsType = "9p";
      options = ["ro" "trans=virtio" "version=9p2000.L" "msize=1M"];
    };
  };

  environment.systemPackages = with pkgs; [
    neofetch
  ];

  system.stateVersion = "23.11";
}
