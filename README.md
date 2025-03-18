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

# Monitor Scaling

The internal scaling table in `src/trackpad-color-picker.hpp` is primarily used to determine when to exit the color picker on zoom out gestures:

```cpp
const std::vector<ScalePair> SCALE_MAP = {
    {0.5f, 2.0f},
    {0.6f, 1.66f},
    {0.7f, 1.41f},
    {0.9f, 1.1f},
    {1.1f, 1.8f},
    {1.2f, 1.6f},
    {1.3f, 1.55f},
    {1.5f, 1.32f},
    {1.7f, 1.2f},
    {2.1f, 1.44f},
    {2.8f, 1.0f}
};
```

If you find the color picker exiting too early or too late on pinch-out gestures, you may need to adjust these values for your monitor's scaling. Note that you can always exit the color picker by clicking to select a color or pressing escape, regardless of these values.

# Caveats

"Freezes" your displays while magnifying.

May segfault in certain edge cases (use the persistence script above to handle this)
