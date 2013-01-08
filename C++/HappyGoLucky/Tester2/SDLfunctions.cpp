#include "SDLfunctions.h"

// Image Flip Flags
const int FLIP_VERTICAL = 1;
const int FLIP_HORIZONTAL = 2;

// Loads and image, optimizes it, and returns it to function
/**************************************************************/
SDL_Surface* loadImage(string fileName) {
	/**************************************************************/
	// Declare empty SDL surfaces here
	SDL_Surface* image = NULL;
	SDL_Surface* optimizedImage = NULL;

	// Adds Directory to the File Name Location
	string location = GRAPHICS_DIR;
	location += fileName;

	// Support for all 3 file types.. I hope
	image = IMG_Load(location.c_str());	
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

// Loads and image, optimizes it, and returns it to function
/**************************************************************/
SDL_Surface* loadImage2(string fileName) {
	/**************************************************************/
	// Declare empty SDL surfaces here
	SDL_Surface* image = NULL;
	SDL_Surface* optimizedImage = NULL;

	// Adds Directory to the File Name Location
	string location = GRAPHICS_DIR;
	location += fileName;

	// Support for all 3 file types.. I hope
	image = IMG_Load(location.c_str());	
	if (image != NULL) {
		optimizedImage = SDL_DisplayFormatAlpha(image);
		SDL_FreeSurface(image);
	} 
	cout << SDL_GetError() << endl;
	if (optimizedImage == NULL) { cout << "CAZZO" << endl; }

	return optimizedImage;
}

// Applies a Surface to a given Destination, offsetting when specified
/******************************************************************************************************/
	void applySurface(int offsetX, int offsetY, SDL_Surface* image, SDL_Surface* destination, SDL_Rect* clip) {
/******************************************************************************************************/
	SDL_Rect offset; // Class/Struct SDL_Rect?
	offset.x = offsetX;
	offset.y = offsetY;
	SDL_BlitSurface(image, clip, destination, &offset);
}

// Acts as a SDL_Rect "Constructor"
// I wrote this to save time...
SDL_Rect SDLRectCon (int x, int y, int w, int h) {
	SDL_Rect temp;
	temp.x = x; temp.y = y;	temp.w = w; temp.h = h;
	return temp;
}

/*
	Built to Order Clippers
		Beware: They do consume extra memory when used. Clean up after.
*/
// Clipped Image V1
/******************************************************************************************************/
void clipImage (string picFile, int x, int y, int w, int h, SDL_Surface* image) {
/******************************************************************************************************/
	SDL_Surface *Picture = NULL;
	SDL_Rect clipper;
	Picture = loadImage(picFile.c_str());
	clipper = SDLRectCon(x, y, w, h);
	applySurface(0, 0, Picture, image, &clipper);
	SDL_FreeSurface(Picture);
}


// Surface Flip Functions
// Courtesy of Lazyfoo (These are not my functions, but I do understand them)
// Since SDL does not come with any form of rotating or flipping of images & surfaces
// personal implementation is required.
Uint32 get_pixel32( SDL_Surface *surface, int x, int y ) {
	//Convert the pixels to 32bit
	Uint32 *pixels = (Uint32 *)surface->pixels;

	//Get the requested pixel
	return pixels[ ( y * surface->w ) + x ];
}
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel ) {
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)surface->pixels;

	//Set the pixel
	pixels[ ( y * surface->w ) + x ] = pixel;
}
SDL_Surface *flip_surface( SDL_Surface *surface, int flags ) {
	SDL_Surface *flipped = NULL;

	if( surface->flags & SDL_SRCCOLORKEY ) {
		flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
	} else {
		flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
	}

	if( SDL_MUSTLOCK( surface ) ) {
		SDL_LockSurface( surface );
	}

	for( int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx-- ) {
		for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- ) {
			Uint32 pixel = get_pixel32( surface, x, y );
			if( ( flags & FLIP_VERTICAL ) && ( flags & FLIP_HORIZONTAL ) ) {
				put_pixel32( flipped, rx, ry, pixel );
			} else if ( flags & FLIP_HORIZONTAL ) {
				put_pixel32( flipped, rx, y, pixel );
			} else if( flags & FLIP_VERTICAL ) {
				put_pixel32( flipped, x, ry, pixel );
			}
		}
	}

	if( SDL_MUSTLOCK( surface ) ) {
		SDL_UnlockSurface( surface );
	}

	if( surface->flags & SDL_SRCCOLORKEY ) {
		SDL_SetColorKey( flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
	}

	return flipped;
}
