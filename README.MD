# dwm - suckless window manager

My build of dwm, the minimalist, fast and flexible window manager with focus on
productivity.

## Main features

- Running custom scripts at startup
- Move and resize floating windows with keyboard shortcuts
- Jump and move windows to adjacent tags
- Real fullscreen toggle
- Move windows in stack or rotate the entire stack
- Bind functions to key press or release events
- Snap to closest corner on mouse resize
- Toggleable sticky windows
- swallow GUI child processes spawned from terminals
- Inner and outer gaps resizeable during runtime (compatible with all layouts)
- Zooming swaps windows instead of shifting the whole stack
- Unlimited scratch pads/windows (arbitrary command)
- Execute arbitrary commands by sending signals
- "throw" windows against screen borders
- floating window rules
- removed dmenu binding (use an external program like xbindkeys instead)
- floating windows save their positions (includes scratchpads!)

## Bar features

- draw rectangles and customize colors
- transparency
- custom foreground and background colors
- customizable bar text horizontal padding
- custom bar height
- dwmblocks won't consume CPU power when bar is toggled off
- toggle dwmblocks without toggling the entire bar

## Applied Patches

Often times the patches were tinkered with after having been applied,
so a lot of the code is slightly different from its original source.

- [autostart](https://dwm.suckless.org/patches/autostart/)
- [moveresize](https://dwm.suckless.org/patches/moveresize/)
- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/)
- [push](https://dwm.suckless.org/patches/push/)
- [sticky](https://dwm.suckless.org/patches/sticky/)
- [zoomswap](https://dwm.suckless.org/patches/zoomswap/)
- [scratchpads](https://dwm.suckless.org/patches/scratchpads/)
- [movethrow](https://dwm.suckless.org/patches/movethrow/)
- [save floats](http://dwm.suckless.org/patches/save_floats/)
- [attachabove](https://dwm.suckless.org/patches/attachabove/)

## Installation

In order to build dwm you need the Xlib header files.

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

## References

- dwm is actively developed by the suckless community
    - [suckless.org](https://suckless.org)
- some snippets of code (mostly vanitygaps for some layouts) are reimplemented copies originating from Luke Smith's dwm repo
    - [github.com/lukesmithxyz/dwm](https://github.com/lukesmithxyz/dwm)
