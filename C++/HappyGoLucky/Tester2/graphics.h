#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include "SDLfunctions.h"
#define _SECURE_SCL 1

extern const int MAX_REPEAT;
			

/******************************************************************************************************
	- 2D Graphic Class - 
		Om Nom Nom Nom!

*******************************************************************************************************/
class Graphic {
public:
	Graphic();
	~Graphic() {}

	void animate(SDL_Surface *spriteSheet, SDL_Surface *destination, int x, int y);

	void add(int x, int y, int w, int h, int xOffSet = NULL, int yOffSet = NULL);

	void repeat(int maxRepeat);

	void offset(int width, int height);

	void togglePause();

	void pause(bool check);

	void reset();

	void continuous();

	bool isFinished() const;

	bool isContinuous() const;

private:
	class OffSet {
	public:
		OffSet() {}
		OffSet(int x, int y) {	x_ = x;	y_ = y;	}
		int x_, y_;
	};

	vector<OffSet> offSets_;

	vector<SDL_Rect> clips_;

	int height_, width_;

	int currentFrame_;

	int maxFrames_;

	int maxRepeat_;

	int repeatCounter_;

	bool pause_;

	bool finished_;

	bool continuous_;

	void frameRepeat();

};


/******************************************************************************************************
	- Character Object Class - 
		Yay Happiness!

*******************************************************************************************************/
class CharacterObject {
public:

	CharacterObject();
	~CharacterObject();
	
	// Plays the Animation at a Provided Coordinate
	void playAnimation(SDL_Surface *destination, int x, int y, int state, bool faceDirection);

	// Loads Sprites
	void load(string fileName);

	// Sets the Sprite Printing Offset
	void offset(int width, int height);

	// Sets the Number of Animations
	void animations(int number);

	// Pushes Back the Number of Animations
	void push_push();

	// Returns the Most Recent Index
	const int index();

	// Adds a New Frame
	void add(int animation, int x, int y, int w, int h, int xOffSet = NULL, int yOffSet = NULL);

	// Toggles an Animation's Continuity Flag
	void continuous(int animation);

	// Pauses Games
	void pause(bool check);

	SDL_Surface *print();

protected:

	// ~ Graphic/Animation List ~
	vector<Graphic> animationsR_;
	vector<Graphic> animationsL_;

	Graphic temp_;

	// ~ Sprite Offset ~
	int height_, width_;

	// ~ The Character's Animation State ~
	int state_;

	// ~ Number of Animations ~
	int animations_;

	// ~ Face Direction ~
	// 0 = Faces Left; 1 = Faces Right
	bool faceDirection_;

	// Pause
	bool pause_;

	// ~ First Entry Accessed ~
	bool check_;

	// Sprite Sheet Surfaces
	SDL_Surface* spriteSheetLeft_;
	SDL_Surface* spriteSheetRight_;
	
	bool proceed(Graphic p);
};




#endif