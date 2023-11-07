{
  lib,
  stdenv,
  pkg-config,
  cmake,
  ninja,
  cairo,
  fribidi,
  libdatrie,
  libjpeg,
  libselinux,
  libsepol,
  libthai,
  libxkbcommon,
  pango,
  pcre,
  utillinux,
  wayland,
  wayland-protocols,
  wayland-scanner,
  wlroots,
  libXdmcp,
  debug ? false,
  version ? "git",
}:
stdenv.mkDerivation {
  pname = "hyprmag" + lib.optionalString debug "-debug";
  inherit version;
  src = ../.;

  cmakeFlags = lib.optional debug "-DCMAKE_BUILD_TYPE=Debug";

  nativeBuildInputs = [
    cmake
    ninja
    pkg-config
  ];

  buildInputs = [
    cairo
    fribidi
    libdatrie
    libjpeg
    libselinux
    libsepol
    libthai
    pango
    pcre
    wayland
    wayland-protocols
    wayland-scanner
    wlroots
    libXdmcp
    libxkbcommon
    utillinux
  ];

  configurePhase = ''
    runHook preConfigure

    make protocols

    runHook postConfigure
  '';

  buildPhase = ''
    runHook preBuild

    make release

    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall

    mkdir -p $out/{bin,share/licenses}

    install -Dm755 build/hyprmag -t $out/bin
    install -Dm644 LICENSE -t $out/share/licenses/hyprmag

    runHook postInstall
  '';

  meta = with lib; {
    homepage = "https://github.com/SIMULATAN/hyprmag";
    description = "A wlroots-compatible Wayland screen magnifier with basic customization options.";
    license = licenses.bsd3;
    platforms = platforms.linux;
  };
}
