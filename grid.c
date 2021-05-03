/* Display the grid illusion (https://en.wikipedia.org/wiki/Grid_illusion) */

/* Copyright © Christophe Pallier

   Time-stamp: <2021-05-03 20:09:12 christophe@pallier.org> 

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
   The Software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the Software.
*/

#define _GNU_SOURCE		// asprintf

#include <stdio.h>
#include <stdlib.h>		// exit
#include <SDL.h>


SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 1024;

int running = 0;

const int n_cells = 10;
int cell_width = 50;
int gap = 10;


void
render_grid (int n_cells, int cell_width, int gap, SDL_Renderer * renderer)
{

     int array_width = n_cells * cell_width + (n_cells - 1) * gap;
     int x_offset = (WINDOW_WIDTH - array_width) / 2;
     int y_offset = (WINDOW_HEIGHT - array_width) / 2;

     //  white background
     SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
     SDL_RenderClear (renderer);

     // The squares will be drawn in black
     SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);

     SDL_Rect r;
     r.w = cell_width;
     r.h = cell_width;

     for (int col = 0; col < n_cells; col++)
          for (int row = 0; row < n_cells; row++)
          {
               r.x = col * (cell_width + gap) + x_offset;
               r.y = row * (cell_width + gap) + y_offset;
               SDL_RenderFillRect (renderer, &r);
          }
}


void process_keys ();
void init ();
void clean ();

inline void
display ()
{
     SDL_RenderPresent (sdlRenderer);
};

inline void
wait (int delay_in_ms)
{
     SDL_Delay (delay_in_ms);
};

int
main ()
{
     init ();

     printf ("Usage: Use the four arrows keys to modify parameters, 's' to save a screen shot.\n\n");

     running = 1;

     while (running)
     {
          render_grid (n_cells, cell_width, gap, sdlRenderer);
          display ();
          wait (10);
          process_keys ();
     }

     clean ();

     return EXIT_SUCCESS;
}


int
is_relevant_event (void *nada, SDL_Event * event)
/* we want to filter out any event which is not  Close window or keypress */
{
     if (event->type == SDL_QUIT || event->type == SDL_KEYDOWN)
          return 1;
     return 0;
}


void
init ()
{

     if (SDL_Init (SDL_INIT_VIDEO) != 0)
     {
          printf ("SDL initialization failed: %s", SDL_GetError ());
          exit (EXIT_FAILURE);
     }

     sdlWindow =
          SDL_CreateWindow ("Herman Grid", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

     if (sdlWindow == NULL)
     {
          printf ("SDL_CreateWindow failed: %s", SDL_GetError ());
          exit (EXIT_FAILURE);
     }

     sdlRenderer =
          SDL_CreateRenderer (sdlWindow, -1,
                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

     if (sdlRenderer == NULL)
     {
          printf ("SDL_CreateRenderer failed: %s\n", SDL_GetError ());
          exit (EXIT_FAILURE);
     }

     SDL_SetEventFilter (is_relevant_event, NULL);
}


void
clean ()
{
     SDL_DestroyRenderer (sdlRenderer);
     SDL_DestroyWindow (sdlWindow);
     SDL_Quit ();
}


int
save_grid (const char *file_name)
{
     SDL_Surface *image;

     if ((image =
          SDL_CreateRGBSurface (0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0,
                                0)) == NULL)
     {
          printf ("SDL_CreateRGBSurface() failed: %s", SDL_GetError ());
          return (EXIT_FAILURE);
     };

     SDL_Renderer *rend;

     if ((rend = SDL_CreateSoftwareRenderer (image)) == NULL)
     {
          printf ("SDL_CreateRGBSurface() failed: %s", SDL_GetError ());
          return (EXIT_FAILURE);
     };

     render_grid (n_cells, cell_width, gap, rend);

     if (SDL_SaveBMP (image, file_name) != 0)
     {
          printf ("SDL_CreateRGBSurface() failed: %s", SDL_GetError ());
          return (EXIT_FAILURE);
     };

     SDL_DestroyRenderer(rend);
     SDL_FreeSurface(image);

     return EXIT_SUCCESS;
}


void
process_keys ()
{
     SDL_Event event;

     while (SDL_PollEvent (&event))
     {
          switch (event.type)
          {
          case SDL_QUIT:
               running = 0;
               break;
          case SDL_KEYDOWN:
               switch (event.key.keysym.sym)
               {
               case SDLK_ESCAPE:
                    running = 0;
                    break;
               case SDLK_RIGHT:
                    gap++;
                    break;
               case SDLK_LEFT:
                    if (gap > 1)
                         gap--;
                    break;
               case SDLK_UP:
                    cell_width++;
                    break;
               case SDLK_DOWN:
                    if (cell_width > 1)
                         cell_width--;
                    break;
               case SDLK_s:
               {			// screenshot
                    char *filename = NULL;
                    if (asprintf
                        (&filename, "grid-width_%d-gap_%d.bmp", cell_width,
                         gap) != -1)
                    {
                         if (save_grid (filename) == EXIT_SUCCESS)
                         {
                              printf ("Screenshot taken in %s\n", filename);
                         }
                         free (filename);
                    }
                    else
                    {
                         perror ("Cannot create filename for screen shot");
                    }
               }
               break;
               }
          }
          /* cout << "size: " << cell_width << " -- gap: " << gap << " -- ratio: " << ((float)cell_width / (float)gap) << endl ; */
          printf ("side: %d -- gap: %d -- ratio: %.2f\n",
                  cell_width, gap, (float) cell_width / (gap));
     }
}
