#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "cgraph.h"
#include "util.h"

bool startgraphics() {
  printf("Hello, World.\n");
  
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    return false;
  }

  atexit(SDL_Quit);
  
  const SDL_VideoInfo* vinfo = SDL_GetVideoInfo();
  
  SDL_Surface* screen = NULL;
  int w = vinfo->current_w;
  int h = vinfo->current_h;
  if((screen = SDL_SetVideoMode(w, h, vinfo->vfmt->BitsPerPixel,
				SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }
  
  w /= 8;
  h /= 4;
  
  int colors[] = {0,0xff};
  bool** cells = calloc(h+2, sizeof(bool*));
  for (int y=0; y<h+2; y++) {
    cells[y] = calloc(w+2, sizeof(bool));
    if (y != 0 && y != h+1) {
      for (int x=1; x<w+1; x++) {
	cells[y][x] = random() & 1;
      }
    }
  }
  while (true) {
    bool** ncells = calloc(h+2, sizeof(bool*));
    for (int y=0; y<h+2; y++) {
      ncells[y] = calloc(w+2, sizeof(bool));
      if (y == 0 || y == h+1) continue;
      for (int x=1; x<w+1; x++) {
	DrawPixel(screen, (x-1)*2  , (y-1)*2  , colors[cells[y][x]], colors[cells[y][x]], colors[cells[y][x]]);
	DrawPixel(screen, (x-1)*2+1, (y-1)*2  , colors[cells[y][x]], colors[cells[y][x]], colors[cells[y][x]]);
	DrawPixel(screen, (x-1)*2  , (y-1)*2+1, colors[cells[y][x]], colors[cells[y][x]], colors[cells[y][x]]);
	DrawPixel(screen, (x-1)*2+1, (y-1)*2+1, colors[cells[y][x]], colors[cells[y][x]], colors[cells[y][x]]);
	
	int neighbors = cells[y+1][x] + cells[y-1][x] + cells[y][x+1] + cells[y][x-1] + cells[y+1][x+1] + cells[y+1][x-1] + cells[y-1][x+1] + cells[y-1][x-1];
	ncells[y][x] = (neighbors == 3) || (cells[y][x] && neighbors == 2);
      }
    }
    free(cells);
    cells = ncells;
    SDL_Flip(screen);
    
    SDL_Event event;
    if (SDL_PollEvent( &event )) {
      if (event.type == SDL_KEYDOWN) break;
    }
  }
  return true;
}
