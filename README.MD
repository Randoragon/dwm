# dwm - suckless window manager

My build of dwm – the minimalist, fast and flexible window manager with focus on
productivity. Patched 6.4 version.

## Applied Patches

I try not to modify code in dwm.c outside of what the patches do. This is to
keep the patching process "from scratch" relatively straight-forward, and thus
retain the ability to upgrade to newer versions of dwm.

- [autostart](https://dwm.suckless.org/patches/autostart/)
- [moveresize](https://dwm.suckless.org/patches/moveresize/)
- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/)
- [movestack](https://dwm.suckless.org/patches/movestack/)
    - This patch defines its function in a separate file and `#include`s it in
    `config.def.h`. Since this is not the conventional way, I manually move the
    function to `dwm.c` and add a function signature.
- [sticky](https://dwm.suckless.org/patches/sticky/)
- [zoomswap](https://dwm.suckless.org/patches/zoomswap/)
- [scratchpads](https://dwm.suckless.org/patches/scratchpads/)
    - This requires a small modification from the "*save floats*" patch, to make
      scratchpads save their positions on hide and restore them on unhide.
- [movethrow](https://dwm.suckless.org/patches/movethrow/)
    - This patch is slightly broken due to my mistake (I contributed it). A few
      constants are not named correctly in `config.def.h`. All of the
      functionality is working. I should fix this soon...
- [save floats](http://dwm.suckless.org/patches/save_floats/)
- [attachabove](https://dwm.suckless.org/patches/attachabove/)
- [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)

## Installation

In order to build dwm you need the Xlib header files.

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

## Forked from

<https://dwm.suckless.org>
