# Hermann grid

Check out https://chrplr.github.io/hermann_grid/

<christophe@pallier.org>

Implementation of the [Hermann grid illusion](https://en.wikipedia.org/wiki/Grid_illusion) in C using [Simple DirectMedia Layer (SDL)](http://libsdl.org).

![Grid stimulus](grid.png)


## Usage

A Linux executable (`builds/linux/grid`), compiled under Ubuntu 20.04, is provided. 

It assumes that SDL2 from libsdl is installed. Under Ubuntu:

    sudo apt install libsdl2-2.0-0 
    
Note: other sdl2 libraries are also worth installing:

    sudo apt install libsdl2-gfx-1.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-net-2.0-0 libsdl2-ttf-2.0-0


When the program is running, use the four arrow keys to modify the squares' width and the gap between them, and the 's' key to save screenshots. 


## Compilation

1. Install SDL2 source from libsdl.org (see https://wiki.libsdl.org/Installation).
 Under Ubuntu::
 
        sudo apt install libsdl2-dev

2. Compile 

        ./configure
        make


## Development 

### TODO

* Add some help text at the bottom of the windows that explains what 
keys can be pressed (even better: "Press 'h' for help" and display the keybindings in the windows.

* Add cross compilation to target Windows.


