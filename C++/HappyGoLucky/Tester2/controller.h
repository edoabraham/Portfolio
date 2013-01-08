#ifndef _H_CONTROLLER
#define _H_CONTROLLER

#define _SECURE_SCL 1

#include "dependencies.h"
#include "characterOBJ.h"

class CharacterControls {
public:
	CharacterControls();

	void actionEvent(PlayerControls p, int xSpeed, int ySpeed, SDL_Event event);

	int xMoveSpeed() const;

	int yMoveSpeed() const;

	int state() const;

	bool faceDirection() const;

	~CharacterControls();

protected:

	int xMoveSpeed_;

	int yMoveSpeed_;

	bool faceDirection_;
	
	int state_;

	bool isMoving_;
};










#endif