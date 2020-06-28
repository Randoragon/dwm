# dwm - suckless window manager

My build of dwm, the minimalist, fast and flexible window manager with focus on productivity.

## Features

- Running custom scripts at startup

## Applied Patches

- [autostart](https://dwm.suckless.org/patches/autostart/)

## Installation

In order to build dwm you need the Xlib header files.

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


