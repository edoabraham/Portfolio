/// SDLFunctions.h - Forward Declarations of SDL Functions
/// Written by Jesse Z. Zhong (Takuto)

#ifndef __SDL_FUNCTIONS_H__
#define __SDL_FUNCTIONS_H__

#include "PrecompiledHeader.h"

using namespace std;

// Loads and image, optimizes it, and returns it to function
SDL_Surface* loadImage(char* fileName);

// Applies a Surface to a given Destination, offsetting when specified
void applySurface(int offsetX, int offsetY, SDL_Surface* image, SDL_Surface* destination, SDL_Rect* clip = NULL);


#endif