#include <SDL.h>
#include "util.h"

void DrawPixel(SDL_Surface *Surface, int x, int y,Uint8 R, Uint8 G,Uint8 B) {
  Uint32 color = SDL_MapRGB(Surface->format, R, G, B);
  Uint8*  bufp= (Uint8*)Surface->pixels + y*Surface->pitch + x*Surface->format->BytesPerPixel;
  switch (Surface->format->BytesPerPixel) {
  case 4:
    bufp[3] = color >> 24;
  case 3:
    bufp[2] = color >> 16;
  case 2:
    bufp[1] = color >> 8;
  case 1:
    bufp[0] = color;
  }
  return;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y) {
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to retrieve */
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  
  switch (bpp) {
  case 1:
    return *p;
    
  case 2:
    return *(Uint16 *)p;
    
  case 3:
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
    
  case 4:
    return *(Uint32 *)p;
    
  default:
    return 0;
  }
}
