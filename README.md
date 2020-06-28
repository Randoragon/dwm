# dwm - suckless window manager

My build of dwm, the minimalist, fast and flexible window manager with focus on productivity.

## Features

- Running custom scripts at startup
- New layouts
- Move and resize floating windows with keyboard shortcuts
- Jump and move windows to adjacent tags

## Applied Patches

- [autostart](https://dwm.suckless.org/patches/autostart/)
- [bottomstack](https://dwm.suckless.org/patches/bottomstack/)
- [centeredmaster](https://dwm.suckless.org/patches/centeredmaster/)
- [emptyview](https://dwm.suckless.org/patches/emptyview/)
- [moveresize](https://dwm.suckless.org/patches/moveresize/)
- [fibonacci](https://dwm.suckless.org/patches/fibonacci/)
- [float border color](https://dwm.suckless.org/patches/float_border_color)
- [focus adjacent tag](https://dwm.suckless.org/patches/focusadjacenttag/)

## Installation

In order to build dwm you need the Xlib header files.

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


