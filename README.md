# dwm - suckless window manager

My build of dwm, the minimalist, fast and flexible window manager with focus on productivity.

The majority of added code comes from applying various patches from the [suckless website](https://dwm.suckless.org),
but there are also many small changes and tweaks I've done manually, so this build is quite unique to my taste.

Also check out [my dwmblocks build](https://github.com/randoragon/dwmblocks) for examples on how to
utilize some bar patches' features.

## Main features

- Running custom scripts at startup
- New layouts: bstack, centeredmaster, floatingcenteredmaster, fibonacci dwindle, grid
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
- window rules: canfocus, floatrules
- dwmblocks integration - see [statuscmd patch](https://dwm.suckless.org/patches/statuscmd/) and read the section below patches,
  I've actually rewritten much of dwm's status bar functionality to be more flexible for my needs.

## Bar features

- draw rectangles and customize colors
- transparency
- custom foreground and background colors
- customizable bar text horizontal padding
- custom bar height
- window name is centered between tags and status text

## Applied Patches

Often times the patches were tinkered with after having been applied,
so a lot of the code is slightly different from its original source.

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
- [moveplace](https://dwm.suckless.org/patches/moveplace/)
- [alpha](https://dwm.suckless.org/patches/alpha/)
- [colorbar](https://dwm.suckless.org/patches/colorbar/)
- [bar height](https://dwm.suckless.org/patches/bar_height/)
- [canfocusrule](https://dwm.suckless.org/patches/canfocusrule/)
- [floatrules](https://dwm.suckless.org/patches/floatrules/)
- [status2d](https://dwm.suckless.org/patches/status2d/)
- [statuscmd-signal](https://dwm.suckless.org/patches/statuscmd/)

## Status Bar Rewrite

Apparently [XStoreName cannot handle all character encodings well](https://linux.die.net/man/3/xstorename) (see second last paragraph in Description), which
actually caused me many instant crashes that were pretty hard to trace when I was trying to get the bar to display
icons from FontAwesome or Unicode characters. Since that's an inherent weakness of the WM\_NAME property, I thought
of an alternative solution:

- dwm spawns a fork of itself with shared memory which reads from a named pipe
- dwmblocks writes the status strings to the named pipe and sends a fake SIGUSR1 to dwm
using [fsignal](https://dwm.suckless.org/patches/fsignal/)
- dwm copies data from shared memory to the status bar everytime it receives the SIGUSR1 signal

Maybe someday I will make this into a patch, because it works rather well, is fully asynchronous and very stable
(you can turn dwmblocks on and off repeatedly without the bar breaking).

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
