{
  description = "Trackpad-Color-Picker - A wlroots-compatible Wayland screen magnifier and color picker daemon that activates on trackpad pinch gesture with basic customization options.";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = {
    self,
    nixpkgs,
    ...
  }: let
    inherit (nixpkgs) lib;
    genSystems = lib.genAttrs [
      # Add more systems if they are supported
      "aarch64-linux"
      "x86_64-linux"
    ];
    pkgsFor = nixpkgs.legacyPackages;
    mkDate = longDate: (lib.concatStringsSep "-" [
      (builtins.substring 0 4 longDate)
      (builtins.substring 4 2 longDate)
      (builtins.substring 6 2 longDate)
    ]);
  in {
    overlays.default = _: prev: rec {
      Trackpad-Color-Picker = prev.callPackage ./nix/default.nix {
        stdenv = prev.gcc12Stdenv;
        version = "0.pre" + "+date=" + (mkDate (self.lastModifiedDate or "19700101")) + "_" + (self.shortRev or "dirty");
        wayland-protocols = prev.wayland-protocols.overrideAttrs (self: super: {
          version = "1.34";
          src = prev.fetchurl {
            url = "https://gitlab.freedesktop.org/wayland/${self.pname}/-/releases/${self.version}/downloads/${self.pname}-${self.version}.tar.xz";
            hash = "sha256-xZsnys2F9guvTuX4DfXA0Vdg6taiQysAq34uBXTcr+s=";
          };
        });
        inherit (prev.xorg) libXdmcp;
      };
      Trackpad-Color-Picker-debug = Trackpad-Color-Picker.override {debug = true;};
    };

    packages = genSystems (system:
      (self.overlays.default null pkgsFor.${system})
      // {default = self.packages.${system}.Trackpad-Color-Picker;});

    formatter = genSystems (system: pkgsFor.${system}.alejandra);
  };
}
