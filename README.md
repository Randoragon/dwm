# dwm - suckless window manager

My build of dwm, the minimalist, fast and flexible window manager with focus on productivity.

## Main features

- Running custom scripts at startup
- New layouts
- Move and resize floating windows with keyboard shortcuts
- Jump and move windows to adjacent tags
- Real fullscreen toggle
- Move windows in stack or rotate the entire stack
- Bind functions to key press or release events
- Snap to closest corner on mouse resize
- Toggleable sticky windows
- swallow GUI child processes spawned from terminals
- Inner and outer gaps resizeable during runtime
- Zooming swaps windows instead of shifting the whole stack
- Unlimited scratch pads/windows (arbitrary command)
- Execute arbitrary commands by sending signals
- "throw" windows against screen borders

## Bar features

- transparency
- only occupied tags are visible

## Applied Patches

- [autostart](https://dwm.suckless.org/patches/autostart/)
- [bottomstack](https://dwm.suckless.org/patches/bottomstack/)
- [centeredmaster](https://dwm.suckless.org/patches/centeredmaster/)
- [emptyview](https://dwm.suckless.org/patches/emptyview/)
- [moveresize](https://dwm.suckless.org/patches/moveresize/)
- [fibonacci](https://dwm.suckless.org/patches/fibonacci/)
- [focus adjacent tag](https://dwm.suckless.org/patches/focusadjacenttag/)
- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/)
- [gridmode](https://dwm.suckless.org/patches/gridmode/)
- [rotate stack](https://dwm.suckless.org/patches/rotatestack/)
- [keypressrelease](https://dwm.suckless.org/patches/keypressrelease/)
- [movestack](https://dwm.suckless.org/patches/movestack/)
- [resizecorners](https://dwm.suckless.org/patches/resizecorners/)
- [sticky](https://dwm.suckless.org/patches/sticky/)
- [swallow](https://dwm.suckless.org/patches/swallow/)
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
- [zoomswap](https://dwm.suckless.org/patches/zoomswap/)
- [scratchpads](https://dwm.suckless.org/patches/scratchpads/)
- [fsignal](https://dwm.suckless.org/patches/fsignal/)
- [moveplace](https://dwm.suckless.org/patches/moveplace/) (modified)
- [alpha](https://dwm.suckless.org/patches/alpha/)
- [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)

## Installation

In order to build dwm you need the Xlib header files.

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


