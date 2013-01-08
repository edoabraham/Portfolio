#ifndef _MAP_H
#define _MAP_H
#define _SECURE_SCL 1

#include "dependencies.h"

extern const double yDepthRate;

class RectObj {
public:
	RectObj() {}
	unsigned int x, y, w, h;
	unsigned int x1() { return x + w; }
	unsigned int y1() { return y + h; }

	void init (unsigned int _x, unsigned int _y, unsigned _w, unsigned int _h);
};

void pushSides (RectObj p1, RectObj p2, int &velocityX, int &velocityY);

// Checks if an object is in map boundaries
void mapBounds (RectObj object, RectObj boundaries);

void charCollide (int &x, int &y, int objSizeX, int objSizeY, int x1, int y1, int objSizeX1, int objSizeY1);

class Oscillation {
public:
	Oscillation();
	~Oscillation();

	void set(double speed, double range);
	int displacement(const int y);
private:
	double speed_;
	double range_;
	int iteration_;
};





#endif