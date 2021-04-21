/* Display the grid illusion (https://en.wikipedia.org/wiki/Grid_illusion) */

/* Copyright © Christophe Pallier

Time-stamp: <2021-04-21 09:38:41 christophe@pallier.org> 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
The Software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the Software.
*/


#include <iostream>
#include <string>

#include <SDL.h>


using namespace std;

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 1024;


const int n_cells = 10;
int cell_width = 50;
int gap = 10;


void render_grid(int n_cells, int cell_width, int gap) {

  int array_width = n_cells * cell_width + (n_cells - 1) * gap;
  int x_offset = (SCREEN_WIDTH - array_width ) / 2;
  int y_offset = (SCREEN_HEIGHT - array_width ) / 2;

  SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
  SDL_RenderClear(sdlRenderer);
  SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);

  SDL_Rect r;
  r.w = cell_width;
  r.h = cell_width;

  for (int col = 0; col < n_cells; col++)
    for (int row = 0; row < n_cells; row ++) {
      r.x = col * (cell_width + gap) + x_offset;
      r.y = row * (cell_width + gap) + y_offset;
      SDL_RenderFillRect(sdlRenderer, &r);
    }
}


int is_relevant_event(void *nada, SDL_Event* event)
{
  if (event->type == SDL_QUIT || event->type == SDL_KEYDOWN)
    return 1;
  return 0;
}


int main() {

    SDL_Init(SDL_INIT_VIDEO);

    sdlWindow = SDL_CreateWindow("Herman Grid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetEventFilter(is_relevant_event, NULL);

    render_grid(n_cells, cell_width, gap);
    SDL_RenderPresent(sdlRenderer);

    bool quit = false;

    while (!quit) {

          SDL_Event event;

          while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
              quit = true;
              break;
            }
            case SDL_KEYDOWN:
              switch (event.key.keysym.sym) {
              case SDLK_ESCAPE: {
                    quit = true;
                    break;
                  };
              case SDLK_RIGHT: {
                    gap++;
                    break;
                  };
              case SDLK_LEFT: {
                    if (gap > 1) gap--;
                    break;
              }
              case SDLK_UP: {
                cell_width++;
                break;
              }
              case SDLK_DOWN: {
                if (cell_width > 1) cell_width--;
                break;
              }
              }
            }
            render_grid(n_cells, cell_width, gap);
            SDL_RenderPresent(sdlRenderer);
            cout << "size: " << cell_width << " -- gap: " << gap << " -- ratio: " << ((float)cell_width / (float)gap) << endl ;
          }
          SDL_Delay(10);
         }


    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);

    SDL_Quit();

    return 0;
}
