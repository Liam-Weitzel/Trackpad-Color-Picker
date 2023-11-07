# hyprmag

A wlroots-compatible Wayland screen magnifier with basic customization options.

![hyprmag screencast](https://user-images.githubusercontent.com/63104422/280996521-71936981-d8b4-45cf-9ad7-07dc16f9b24a.gif)

# Usage

Launch it. Move the mouse. That's it.

## Options

`-h | --help` prints a help message

`-r | --radius` sets the radius of the magnifying lens

`-s | --scale` sets the zoom factor

# Building

## Arch
`yay -S hyprmag-git`

## Manual
`make all`

the output binary is in `./build/hyprmag`

# Caveats

"Freezes" your displays while magnifying.
