# Trackpad-Color-Picker

A wlroots-compatible Wayland screen magnifier and color picker daemon that activates on trackpad pinch gesture with basic customization options.

![preview](./preview.gif)

# References

![hypermag](https://github.com/SIMULATAN/hyprmag)

![hyperpicker](https://github.com/hyprwm/hyprpicker)

# Usage

Launch it. Trackpad pinch to zoom in/out. Move the mouse. Click. Paste. That's it.

## Options

`-h | --help` prints a help message
`-r | --radius` sets the radius of the magnifying lens
`-l | --lowercase-hex` Outputs the hexcode in lowercase
`-f | --format=fmt` Specifies the output format (cmyk, hex, rgb, hsl, hsv)

# Building

Building is done via CMake:

```sh
cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=/usr -S . -B ./build
cmake --build ./build --config Release --target Trackpad-Color-Picker -j`nproc 2>/dev/null || getconf _NPROCESSORS_CONF`
```

Install with:

```sh
cmake --install ./build
```

# Caveats

"Freezes" your displays while magnifying.
