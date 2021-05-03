# Hermann grid

<christophe@pallier.org>

Implementation of the [Hermann grid illusion](https://en.wikipedia.org/wiki/Grid_illusion) in C using [Simple DirectMedia Layer (SDL)](http://libsdl.org).

![Grid stimulus](grid.png)


## Usage

A linux executable is provided. Under Linux, just run:

    ./grid

Then use the four arrow keys to modify the squares' width and the gap between them. 


## Compilation

1. Install SDL2 from libsdl.org (see https://wiki.libsdl.org/Installation).
 Under Ubuntu::
 
        sudo apt install libsdl2-dev
     

2. Compile 

        ./configure
        make
    


