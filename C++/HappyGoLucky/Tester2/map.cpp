#include "map.h"

// 
const double yDepthRate = 0.4;

void RectObj::init (unsigned int _x, unsigned int _y, unsigned _w, unsigned int _h) {
	x = _x;	y = _y;	w = _w;	h = _h;
}

void pushSides (RectObj p1, RectObj p2, int &velocityX, int &velocityY) {
	if((p1.x1() >= p2.x1()) && (velocityX != 0)) {
		velocityX = 0;
		// Rest of Code here
	} 
	if((p1.x <= p2.x) && (velocityX != 0)) {
		velocityX = 0;
		// Rest of Code here
	}
	if((p1.y1() >= p2.y1()) && (velocityY != 0)) {
		velocityY = 0;
	}
	if((p1.y <= p2.y) && (velocityY != 0)) {
		velocityY = 0;
	}
}

// Checks if an object is in map boundaries
void mapBounds (RectObj object, RectObj boundaries) {
	if(object.x < boundaries.x) object.x = boundaries.x;
	if(object.y < boundaries.y) object.y = boundaries.y;
	if(object.x + object.w > boundaries.x + boundaries.w) object.x = boundaries.x + boundaries.w - object.w;
	if(object.y + object.h > boundaries.y + boundaries.h) object.y = boundaries.y + boundaries.h - object.h;
}

void charCollide (int &x, int &y, int objSizeX, int objSizeY, int x1, int y1, int objSizeX1, int objSizeY1) {
	if (x < x1 + objSizeX1) x = x1 + objSizeX1;
	if (y < y1 + objSizeY1) y = y1 + objSizeY1;
	if (x + objSizeX > x1) x = x1 - objSizeX;
	if (y + objSizeY > y1) y = y1 - objSizeY;
}


Oscillation::Oscillation() {
	speed_ = 0.00;
	range_ = 0.00;
	iteration_ = 0;
}

Oscillation::~Oscillation() {

}

void Oscillation::set(double speed, double range) {
	speed_ = speed;	range_ = range;
}
int Oscillation::displacement(const int y) {
	int temp = int(range_ * sin(speed_ * iteration_)) + y;
	iteration_++;
	return temp;
}