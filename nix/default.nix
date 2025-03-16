{
  lib,
  stdenv,
  pkg-config,
  cmake,
  cairo,
  fribidi,
  libdatrie,
  libGL,
  libjpeg,
  libselinux,
  libsepol,
  libthai,
  libxkbcommon,
  libinput,
  pango,
  expect,
  pcre,
  pcre2,
  utillinux,
  wayland,
  wayland-protocols,
  wayland-scanner,
  libXdmcp,
  debug ? false,
  version ? "git",
}:
stdenv.mkDerivation {
  pname = "hyprmag" + lib.optionalString debug "-debug";
  inherit version;

  src = ../.;

  cmakeBuildType =
    if debug
    then "Debug"
    else "Release";

  nativeBuildInputs = [
    cmake
    pkg-config
  ];

  buildInputs = [
    cairo
    fribidi
    libdatrie
    libGL
    libjpeg
    libselinux
    libsepol
    libthai
    libinput
    expect
    pango
    pcre
    pcre2
    wayland
    wayland-protocols
    wayland-scanner
    libXdmcp
    libxkbcommon
    utillinux
  ];

  outputs = [
    "out"
    "man"
  ];

  meta = with lib; {
    homepage = "https://github.com/SIMULATAN/hyprmag";
    description = "A wlroots-compatible Wayland screen magnifier with basic customization options.";
    license = licenses.bsd3;
    platforms = platforms.linux;
    mainProgram = "hyprmag";
  };
}
