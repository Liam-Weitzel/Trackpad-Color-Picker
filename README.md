# Trackpad-Color-Picker

A wlroots-compatible Wayland screen magnifier and color picker daemon that activates on trackpad pinch gesture with basic customization options.

![preview](./preview.gif)

# References

⚠️ Development Status: Experimental

This project emerged from a weekend of enthusiastic hacking - it's a beautiful mess of forked code and hacky solutions. While functional, it's very much a playground project and not production-ready. Use at your own discretion and with a sense of adventure.

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

# Making it persistent

Due to some edge cases causing segfaults, it's recommended to run this with a persistence script:

```bash
#!/bin/bash
# always-launch.sh

if [ $# -ne 2 ]; then
    echo "Usage: $0 <command> <process_name>"
    exit 1
fi

COMMAND="$1"
PROCESS="$2"

while true; do
    if ! pgrep -x "$PROCESS" > /dev/null; then
        echo "Starting $PROCESS..."
        $COMMAND &
    fi
    sleep 1
done
```

Optional: Configure your window manager to intercept trackpad gestures to prevent default behaviour in apps like Firefox. For example in Sway:

```bash
exec sh ~/.bash_scripts/always-launch.sh ~/Trackpad-Color-Picker/build/Trackpad-Color-Picker Trackpad-Color-
bindgesture pinch:inward exec
bindgesture pinch:outward exec
```

# Caveats

"Freezes" your displays while magnifying.

May segfault in certain edge cases (use the persistence script above to handle this)
