#ifndef _H_SDLFUNCTIONS
#define _H_SDLFUNCTIONS
#include "dependencies.h"
#define _SECURE_SCL 1

extern const int FLIP_VERTICAL;
extern const int FLIP_HORIZONTAL;

SDL_Surface* loadImage(string fileName);
SDL_Surface* loadImage2(string fileName);
void applySurface(int offsetX, int offsetY, SDL_Surface* image, SDL_Surface* destination, SDL_Rect* clip = NULL);
SDL_Rect SDLRectCon (int x, int y, int w, int h);
void clipImage (string picFile, int x, int y, int w, int h, SDL_Surface* image);
Uint32 get_pixel32( SDL_Surface *surface, int x, int y );
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );
SDL_Surface *flip_surface( SDL_Surface *surface, int flags );

#endif