# Hermann grid

Check out https://chrplr.github.io/hermann_grid/

<christophe@pallier.org>

Implementation of the [Hermann grid illusion](https://en.wikipedia.org/wiki/Grid_illusion) in C using [Simple DirectMedia Layer (SDL)](http://libsdl.org).

![Grid stimulus](grid.png)


## Usage


## Linux executable


After running the compilation and installation as described below, if everything worked out well, an executable file is `grid` (or `grid.exe` under Windows) is available in `$HOME/bin`. 

If `$HOME/bin` is in the `PATH` environment variable, you just have type `grid` on a command line to start it, otherwise, type `~/bin/grid`.

While `grid` is running, the user can press the four arrow keys to modify the squares width and the gap. 

One can also press the 'S' key to save a screenshot of the content of the current window.

## Compilation


### Linux

Note: A Linux executable (`builds/linux/grid`), compiled under Ubuntu 20.04, is provided (It requires that SDL2 from libsdl is installed: Under Ubuntu: `sudo apt install libsdl2-2.0-0` ; under Fedora: `sudo dnf install SDL2`)


1. Install SDL2 development library. You can do from the source code, following the instructions at <https://wiki.libsdl.org/Installation>, or from your distribution package manager (Ubuntu: `sudo apt install libsdl2-dev`; Fedora:  `sudo dnf install SDL2 SDL2-devel`.


Note: Other SDL2 libraries are also worth installing: 

* For Ubuntu:

        sudo apt install libsdl2-gfx-1.0-0 libsdl2-image-2.0-0 \
                         libsdl2-mixer-2.0-0 libsdl2-net-2.0-0 \
                         libsdl2-ttf-2.0-0

* For Fedora: 

        sudo dnf install SDL2_image SDL2_image-devel SDL2_ttf SDL2_ttf-devel \
                         SDL2_mixer SDL2_mixer-devel SDL2_gfx SDL2_gfx-devel \
                         SDL2_net SDL2_net-devel



2. Compile 

        ./configure --prefix=$HOME && make && make install

### MacOSX

1. install [homebrew](https://brew.sh/)
2. install sdl2

        brew install sdl2
        
3. Compile

        ./configure prefix=$HOME && make && make install

### Windows

1. Install the mingw-w64 C compiler and the development version of SDL2, following the instructions at  <https://www.matsson.com/prog/sdl2-mingw-w64-tutorial.php>

2. Compile

        ./configure prefix=$HOME && make && make install


Actually, it does not work :(
Use: $ gcc grid.c -o grid -I/opt/local/i686-w64-mingw32/include/SDL2 -Dmain=SDL_main -L/opt/local/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows
    
## Development 

### TODO

* Add some help text at the bottom of the windows that explains what 
keys can be pressed (even better: "Press 'h' for help" and display the keybindings in the window.

* add command line usage and options (--help --version)

* Add cross compilation to target Windows.


