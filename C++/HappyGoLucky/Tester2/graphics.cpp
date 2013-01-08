#include "graphics.h"
	
//	By Jesse (Takuto)
//    Gameplay: Graphics -> Sound -> Controls -> Fluency -> Content
// This is where all the my SDL functions go!

const int MAX_REPEAT = 5;

Graphic::Graphic() {
	maxFrames_ = 0;
	maxRepeat_ = MAX_REPEAT;
	repeatCounter_ = 0;
	pause_ = false;
	continuous_ = false;
	finished_ = false;
	currentFrame_ = 0;
	height_ = 0;
	width_ = 0;
}

void Graphic::add(int x, int y, int w, int h, int xOffSet, int yOffSet) {
	OffSet temp1 = OffSet(xOffSet, yOffSet);
	SDL_Rect temp2 = SDLRectCon(x, y, w, h);
	offSets_.push_back(temp1);
	clips_.push_back(temp2);
	maxFrames_++;
}

void Graphic::frameRepeat() {
	if(repeatCounter_ < maxRepeat_) {
		finished_ = false;
		repeatCounter_++;
	} else {
		repeatCounter_ = 0;
		if(!pause_) {
			currentFrame_++;
		}
		if(currentFrame_ >= maxFrames_) {
			finished_ = true;
			if(continuous_){
				currentFrame_ = 0;
				repeatCounter_ = 0;
			} else {
				currentFrame_--;
				repeatCounter_--;
			}
		}
	}
}


void Graphic::repeat(int maxRepeat) {
	maxRepeat_ = maxRepeat;
}

void Graphic::offset(int width, int height) {
	width_ = width;	height_ = height_;
}

void Graphic::togglePause() {
	pause_ = !pause_;
}

void Graphic::pause(bool check) {
	pause_ = check;
}

void Graphic::animate(SDL_Surface *spriteSheet, SDL_Surface *destination, int x, int y) {
	frameRepeat();
	offSets_.at(currentFrame_);
	clips_.at(currentFrame_);
	applySurface(x + width_ + offSets_[currentFrame_].x_, y - height_ - offSets_[currentFrame_].y_, spriteSheet, destination, &clips_[currentFrame_]);
}

void Graphic::reset() {
	repeatCounter_ = 0;
	currentFrame_ = 0;
}

void Graphic::continuous() {
	continuous_ = !continuous_;
}

bool Graphic::isFinished() const {
	return finished_;
}

bool Graphic::isContinuous() const {
	return continuous_;
}

/************************************************************************/
/*			Character Object (characterObject) Class Methods			*/
/************************************************************************/

// Constructor
CharacterObject::CharacterObject() {
	animationsL_.push_back(temp_);
	animationsR_.push_back(temp_);
	animationsL_[0].continuous();
	animationsR_[0].continuous();
	animations_ = 1;
	check_ = false;
}

//* Loads Sprite Sheet for Object
void CharacterObject::load(string fileName) {
	spriteSheetLeft_ = loadImage(fileName);
	spriteSheetRight_ = flip_surface(spriteSheetLeft_, 2);
	cout << fileName << " loaded." << endl;
}

// Sets the Sprite Printing Offset
void CharacterObject::offset(int width, int height) {
	width_ = width;	height_ = height;
}

// Sets the Number of Animations/Graphics to be Stored
void CharacterObject::animations(int number) {
	if(number < 1) animations_ = 1;
	animations_ = number;
	animationsR_.resize(animations_);
	animationsL_.resize(animations_);
}

void CharacterObject::push_push() {
	if(!check_) check_ = true;
	else animations_++;
	cout << animations_ << endl;
	animationsR_.resize(animations_);
	animationsL_.resize(animations_);
}

const int CharacterObject::index() {
	if(!animationsL_.empty() && !animationsR_.empty()) return animations_ - 1;
	else return -1;
}

// Adds a New Frame
void CharacterObject::add(int animation, int x, int y, int w, int h, int xOffSet, int yOffSet) {
	if(0 <= animation && animation < animations_) {
		animationsL_.at(animation);
		animationsR_.at(animation);
		cout << animation << " " << x << " " << y << " " << w << " " << h << endl;
		animationsL_[animation].add(x, y, w, h, xOffSet, yOffSet);
		animationsR_[animation].add((spriteSheetLeft_->w - (w + x)), y, w, h, (width_ - (w + xOffSet)), yOffSet);
	}
}

// Destructor
CharacterObject::~CharacterObject() {
	//SDL_FreeSurface(spriteSheetLeft_); // Strangely already de-allocates itself
	//SDL_FreeSurface(spriteSheetRight_);
	for(int i = (animationsL_.size() - 1); i >= 0; i--) {
		animationsL_.pop_back();
	}
	for(int i = (animationsR_.size() - 1); i >= 0; i--) {
		animationsR_.pop_back();
	}
}

bool CharacterObject::proceed(Graphic p) {
	if(p.isContinuous()) return true;
	else if(p.isFinished()) return true;
	else return false;
}

// Plays Given Animation
/******************************************************************************************************/
void CharacterObject::playAnimation (SDL_Surface *destination, int x, int y, int state, bool faceDirection) {
/******************************************************************************************************/
	if(spriteSheetLeft_ != NULL && spriteSheetRight_ != NULL) {
		if(0 <= state && state < animations_) {
			if((faceDirection_ == false && proceed(animationsL_[state_])) || (faceDirection_ == true && proceed(animationsR_[state_]))) {
				if(state_ != state) {
					animationsL_[state_].reset();
					animationsR_[state_].reset();
				}
				if(state < 0 && state >= animations_) state_ = 0;
				else state_ = state;
				faceDirection_ = faceDirection;
			}
			if (faceDirection_ == false) {
				animationsL_.at(state_);
				animationsL_[state_].pause(pause_);
				return animationsL_[state_].animate(spriteSheetLeft_, destination, x, y);
			} else if (faceDirection_ == true) {
				animationsR_[state_].pause(pause_);
				animationsR_.at(state_);
				return animationsR_[state_].animate(spriteSheetRight_, destination, x, y);
			}
		}
	}
}

// Toggles an Animation's Continuity Flag
void CharacterObject::continuous(int animation) {
	if(0 < animation && animation < animations_) {
		animationsL_[animation].continuous();
		animationsR_[animation].continuous();
	}
}

// Forces Pause
void CharacterObject::pause(bool check) {
	pause_ = check;
}

SDL_Surface *CharacterObject::print() {
	return spriteSheetRight_;
}