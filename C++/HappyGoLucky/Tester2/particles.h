#ifndef _H_PARTICLES
#define _H_PARTICLES
#define _SECURE_SCL 1
#include "SDLfunctions.h"

const int MAX_PARTICLES = 100;		// Hard Check

/************************************************************************/
/*                         QUARANTINED                                  */
/************************************************************************/

// Particle Engine
/*
	Similar, compact, specialized class to characterOBJ

*/
class controlPattern {
public:
	controlPattern() {
		rangeGravity = 0;
		rangeVelocity = 0;
		rangeDeviation = 0;
		actualVelocity = rand() % (maxVelocity - rangeVelocity) + rangeVelocity;
		actualGravity = rand() % (maxGravity - rangeGravity) + rangeGravity;
		actualDeviation = rand() % (maxDeviation - rangeDeviation) + rangeDeviation;
	}
	controlPattern(int gravity, int velocity, int deviation) {
		maxGravity = gravity;		maxVelocity = velocity;
		maxDeviation = deviation;
	}
	void specific(int gravityR, int velocityR, int deviationR, int width = 0) {
		rangeGravity = gravityR;
		rangeVelocity = velocityR;
		rangeDeviation = deviationR;
		actualVelocity = rand() % (maxVelocity - rangeVelocity) + rangeVelocity;
		actualGravity = rand() % (maxGravity - rangeGravity) + rangeGravity;
		actualDeviation = rand() % (maxDeviation - rangeDeviation) + rangeDeviation;
	}
	void pattern (int type, int &x, int &y) {
		switch(type) {
		case 0:		// Pseudo Gravity
			x -= actualGravity;
			y = y;
			break;
		case 1:		// Feather/Leaf Falling
			break;
		case 2:		// Whipping Feather/Leaf Fall
			break;
		case 3:		// Tornado Spin
			break;
		case 4:		// Waving Ribbon
			break;
		default:	// Nothing Happens
			x = x;
			y = y;
			break;
		}
	}
private:
	int rangeGravity;
	int rangeVelocity;
	int rangeDeviation;
	int maxGravity;
	int maxVelocity;
	int maxDeviation;
	int actualGravity;
	int actualVelocity;
	int actualDeviation;
};



class circle {				// Built out of Necessity
public:
	circle() {}
	~circle() {}
	vector<vector<bool>> circlePoints;
	void fillin (int daRadius) {
		radius = daRadius;
		chordDis = radius;
		int diameter = radius * 2 + 1;
		circlePoints.resize(diameter);
		vector<bool> row;
		for(int i = 0; i < diameter; i++) {
			circlePoints[i].resize(diameter);
		}
		for (int i = 0; i <= radius; i++) {
			if(i == radius) {
				for(int j = 0; j < diameter; j++) {
					circlePoints[radius][j] = 1;
				}
			} else {
				for(int j = 0; j < diameter; j++) {
					boundSetter();
					if(j <= xPoint2 && j >= xPoint1) {
						circlePoints[i][j] = true;
						circlePoints[radius * 2 - i][j] = true;
					} else {
						circlePoints[i][j] = false;
						circlePoints[radius * 2 - i][j] = false;
					}
				}
			}
			chordDis--;
		}
	}
	void checkBounds (int x, int y) {
		if(circlePoints[x][y]) {
			// Insert Something
		}
	}
	void printShit () {
		for(int i = 0; i < (radius * 2 + 1); i++) {
			for(int j = 0; j < (radius * 2 + 1); j++) {
				cout << circlePoints[i][j] << " ";
			}
			cout << endl;
		}
	}
private:
	int radius, chordDis, halfChord;
	int xPoint1, xPoint2;
	void boundSetter () {
		halfChord = int(sqrt(double(pow((double)radius, 2) - pow((double)chordDis, 2))));
		xPoint1 = radius - halfChord;
		xPoint2 = radius + halfChord;
	}
};

class particle {
public:
	particle() {
		w = 1;
		h = 1;
		gravity = 3;
		frameLifeDeviation = 5;
		endFrame = 10;
	}
	void load(char* fileName, int Gravity, int LifeDeviation, int end, int theOffSet) {
		spriteSheet = loadImage(fileName);
		gravity = Gravity;
		frameLifeDeviation = LifeDeviation;
		endFrame = end;
		offSet = theOffSet;
	}
	void bounds(int W, int H) {
		w = W;	h = H;
	}
	void birth(int X, int Y) {
		x = X + (rand() % w);
		y = Y + (rand() % h);

		fallSpeed = rand() % (gravity + 3);
		if(frameLifeDeviation > endFrame - 1) { frameLifeDeviation = endFrame - 1; }
		if(frameLifeDeviation < 0) { frameLifeDeviation = 0; }
		currentFrame = 0; //rand() % (frameLifeDeviation + 1);

		if(int(clip1.size()) != int(clip2.size())) { cout << "Clip error!/n"; }
		clipSize = int(clip1.size());
		
		type = rand() % (clipSize + 1);
		for(int i = 0; i < clipSize; i++) {
			if(type == i) {
				type1 = clip1[i];
				type2 = clip2[i];
			}
		}
	}
	void clipYes(int element, int xClip, int yClip, int wClip, int hClip) {
		
			clip1.push_back(rect);
			clip2.push_back(rect);
		
		clip1[element] = SDLRectCon(xClip,yClip,wClip,hClip);
		clip2[element] = SDLRectCon(xClip,(yClip + offSet),wClip,hClip);
	}
	void display() {
		applySurface(x, y, spriteSheet, screen, &type1);
		if (currentFrame % 2 == 0) {		// On every even numbered frame
			applySurface(x, y, spriteSheet, screen, &type2);
		}
		currentFrame++;
		y += fallSpeed;
		// Curve here

		// Pause
		if(pauseGame) {
			currentFrame--;
			y -= fallSpeed;
		}
	}
	bool dead(bool force = 0) {
		if(force) {
			return true;
		}
		if(currentFrame > endFrame - frameLifeDeviation) {
			return true;
		}
		return false;
	}
	~particle() {}
	int x, y;
	int currentFrame;
private:
	int w, h;
	int gravity;
	int endFrame;
	int frameLifeDeviation;
	int type;
	SDL_Rect type1, type2;
	vector<SDL_Rect> clip1;
	vector<SDL_Rect> clip2;
	int clipSize;
	int offSet;
	int fallSpeed;
	SDL_Rect rect;
	SDL_Surface *spriteSheet;
};


class particleOBJ {
public:
	particleOBJ() {
		x = 0;
		y = 0;
		xVelocity = 4;
		yVelocity = 0;
		particles.resize(MAX_PARTICLES);
		for(int i = 0; i < MAX_PARTICLES; i++) {
			particles[i].birth(x,y);
		}
	}
	~particleOBJ() {
		for(int i = 0; i < MAX_PARTICLES; i++) {
			particles.erase(particles.begin() + i);
			particles.insert(particles.begin() + i, mainType);
		}
	}
	void move() {
		x += xVelocity;

		if(x + width > SCREEN_WIDTH) {
			x -= xVelocity;
			xVelocity = -xVelocity;
		}

		if(x < 0) {
			x -= xVelocity;
			xVelocity = -xVelocity;
		}

		y += yVelocity;

		if(y + height > SCREEN_HEIGHT) {
			y -= yVelocity;
			yVelocity = -yVelocity;
		}

		if(y < 0) {
			y -= yVelocity;
			yVelocity = -yVelocity;
		}

		// Pause
		if(pauseGame) {
			x -= xVelocity;
			y -= yVelocity;
		}
	}
	void stencil(particle type, int shapeFlag, int xSize, int ySize = 0) {

		switch(shapeFlag) {
		case 0:	// Rectangle
			{
				particleArea.resize(xSize);
				for(int i = 0; i < xSize; i++) {
					particleArea[i].resize(ySize);
				}
				for(int i = 0; i < xSize; i++) {
					for(int j = 0; j < ySize; j++) {
						particleArea[i][j] = true;
					}
				}
				width = xSize;
				height = ySize;
			}
			break;
		case 1:	// Circle
			{
				circle ball;
				ball.fillin(xSize/2);
				particleArea = ball.circlePoints;
				width = int(particleArea.size());
				height = int(particleArea.size());
			}
			break;
		default:
			break;
		}
		mainType = type;
		for(int i = 0; i < MAX_PARTICLES; i++) {
			particles[i] = mainType;
			particles[i].bounds(width,height);
			particles[i].birth(x,y);
		}
		
		mainType.bounds(width, height);
	}
	void display() {
		for(int i = 0; i < MAX_PARTICLES; i++) {
			if(particles[i].dead() == true) {
//				particles.erase(particles.begin() + i);
//				particles.insert(particles.begin() + i, mainType);
				particles[i].bounds(width,height);
				particles[i].birth(x,y);
			}
		}
		
		for(int i = 0; i < MAX_PARTICLES; i++) {
			if(particles[i].currentFrame == 0) {
				if(particles[i].x < width && particles[i].y < height) {
					if(particleArea[particles[i].x][particles[i].y]) {
					} else {
		//				particles.erase(particles.begin() + i);
		//				particles.insert(particles.begin() + i, mainType);
						particles[i].bounds(width,height);
						particles[i].birth(x,y);
					}
				} else {
					particles[i].bounds(width,height);
					particles[i].birth(x,y);
				}
			}
		}
		for(int i = 0; i < MAX_PARTICLES; i++) {
				particles[i].display();
		}
	}
private:
	int x, y;
	int width, height;
	int xVelocity, yVelocity;
	vector<vector<bool>> particleArea;
	particle mainType;
	vector<particle> particles;
	particle sizeParticle;
};

class menuScreen {

};





#endif