#include "controller.h"

CharacterControls::CharacterControls() {
	state_ = 0;
	faceDirection_ = false;
	xMoveSpeed_ = 0;
	yMoveSpeed_ = 0;
	isMoving_ = false;
}

CharacterControls::~CharacterControls() {
	state_ = 0;
	faceDirection_ = 0;
	xMoveSpeed_ = 0;
	yMoveSpeed_ = 0;
	isMoving_ = 0;
}

void CharacterControls::actionEvent(PlayerControls p, int xSpeed, int ySpeed, SDL_Event event) {
	if(event.type == SDL_KEYDOWN) {
		if(event.key.keysym.sym == p.Left) {
			xMoveSpeed_ -= xSpeed;		
			faceDirection_ = false;
			isMoving_ = true;
		} 
		if(event.key.keysym.sym == p.Right) {
			xMoveSpeed_ += xSpeed;
			faceDirection_ = true;
			isMoving_ = true;
		}
		if(event.key.keysym.sym == p.Jump) {
			yMoveSpeed_ -= ySpeed;
			isMoving_ = true;
		}
		if(event.key.keysym.sym == p.Duck) {
			yMoveSpeed_ += ySpeed;
			isMoving_ = true;
		}
		if (event.key.keysym.sym == p.Katar) {	// Attack1
			state_ = 3;
		}
		if (event.key.keysym.sym == p.Dagger) {	// Attack2
			state_ = 4;
		}
		if (event.key.keysym.sym == p.Bow) {		// Attack3
			state_ = 5;
		}
		if (event.key.keysym.sym == p.Knife) {	// Attack4
			state_ = 6;
		}
		if(event.key.keysym.sym == p.Backslide) {
			if(faceDirection_) {
				xMoveSpeed_ -= xSpeed;
			} else {
				xMoveSpeed_ += xSpeed;
			}
			state_ = 2;
		}
	} else if(event.type == SDL_KEYUP) {
		if(event.key.keysym.sym == p.Left) {
			xMoveSpeed_ += xSpeed;		
			state_ = 0;
			isMoving_ = false;
		}
		if(event.key.keysym.sym == p.Right) {
			xMoveSpeed_ -= xSpeed;
			state_ = 0;
			isMoving_ = false;
		}
		if(event.key.keysym.sym == p.Jump) {
			yMoveSpeed_ += ySpeed;
			state_ = 0;
			isMoving_ = false;
		}
		if(event.key.keysym.sym == p.Duck) {
			yMoveSpeed_ -= ySpeed;
			state_ = 0;
			isMoving_ = false;
		}
		if (event.key.keysym.sym == p.Katar) {	// Attack1
			if(isMoving_) state_ = 1;
			else state_ = 0;
		}
		if (event.key.keysym.sym == p.Dagger) {	// Attack2
			if(isMoving_) state_ = 1;
			else state_ = 0;
		}
		if (event.key.keysym.sym == p.Bow) {		// Attack3
			if(isMoving_) state_ = 1;
			else state_ = 0;
		}
		if (event.key.keysym.sym == p.Knife) {	// Attack4
			if(isMoving_) state_ = 1;
			else state_ = 0;
		}
		if(event.key.keysym.sym == p.Backslide) {
			if(faceDirection_) {
				xMoveSpeed_ += xSpeed;
			} else {
				xMoveSpeed_ -= xSpeed;
			}
			state_ = 0;
		}
	} else state_ = 0;
}

int CharacterControls::xMoveSpeed() const {
	return xMoveSpeed_;
}

int CharacterControls::yMoveSpeed() const {
	return yMoveSpeed_;
}

int CharacterControls::state() const {
	return state_;
}

bool CharacterControls::faceDirection() const{
	return faceDirection_;
}

