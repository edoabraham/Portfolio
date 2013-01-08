/// SDLFunctions.cpp - Implementations of SDL Functions
/// Written by Jesse (Takuto)

#include "PrecompiledHeader.h"
#include "SDLFunctions.h"

/**********************************************************
	General SDL Functions
		Customized by Takuto (Jesse)
***********************************************************/

// Loads and image, optimizes it, and returns it to function
/**************************************************************/
SDL_Surface* loadImage(char* fileName) {
/**************************************************************/
	// Declare empty SDL surfaces here
	SDL_Surface* image = NULL;
	SDL_Surface* optimizedImage = NULL;

	// Support for all 3 file types.. I hope
	image = IMG_Load(fileName);	
	if (image != NULL) {
		optimizedImage = SDL_DisplayFormat(image);
		SDL_FreeSurface(image);
	} 
	cout << SDL_GetError() << endl;
	if( optimizedImage != NULL ) {
		SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0x3D, 0xA2, 0xF7 ) );		
		// Not that it's necessary, but good thing there are calculators for Hex when you want them~
	}
	if (optimizedImage == NULL) { cout << "CAZZO" << endl; }
	return optimizedImage;
}

// Applies a Surface to a given Destination, offsetting when specified
/******************************************************************************************************/
void applySurface(int offsetX, int offsetY, SDL_Surface* image, SDL_Surface* destination, SDL_Rect* clip = NULL) {
/******************************************************************************************************/
	SDL_Rect offset; // Class/Struct SDL_Rect?
	offset.x = offsetX;
	offset.y = offsetY;
	SDL_BlitSurface(image, clip, destination, &offset);
}

/* Acts as a SDL_Rect "Constructor"; I wrote this to save time...     */
SDL_Rect SDLRectCon (int x, int y, int w, int h) {
	SDL_Rect temp;
	temp.x = x; temp.y = y;	temp.w = w; temp.h = h;
	return temp;
}
/* End SDL General Function List */