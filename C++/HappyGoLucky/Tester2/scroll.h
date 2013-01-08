#ifndef _H_SCROLL
#define _H_SCROLL
#define _SECURE_SCL 1

#include "SDLfunctions.h"

class Background {
public:

	Background();

	void init(int left, int right);

	~Background();

	SDL_Surface *image_;

	int left_, right_;

};


class ScrollMap {
public:
	ScrollMap();
	~ScrollMap();

	void add(string fileName, int width);

	void print(SDL_Surface *destination, int x, int width, int yOffSet = NULL);

protected:
	vector<Background> mapList_;

	int width_;
	int listSize_;

};


class Scroll {

public:

	Scroll();
	~Scroll();

	void print(ScrollMap mapScroll, SDL_Surface *destination, int &xScreen, int &yScreen, int &x, int xSpeed, int ySpeed);

	void player(int x, int y, int w, int h);

	void bound(int leftMargin, int rightMargin, int topMargin, int bottomMargin);

	void window(int x, int y, int w, int h);

private:

	class Box {
	public:

		Box();
		Box(int x, int y, int w, int h) {
			x1_ = x;	y1_ = y;	w_ = w;	h_ = h;
		}

		int x1_, y1_;

		int x2() const;
		int y2() const;

		void init (int x, int y, int w, int h) {
			x1_ = x;	y1_ = y;	w_ = w;	h_ = h;
		}

		int w_, h_;

		~Box();

	} temp;

	Box player_;
	Box bounds_;
	Box window_;

	int leftMargin_;
	int rightMargin_;
	int topMargin_;
	int botMargin_;

	void setBounds();

	Box *sizeCheck(Box *test, Box *against) {
		Box *temp = test;
		if((test->w_ > against->w_)) temp->w_ = against->w_;
		if((test->h_ > against->h_)) temp->h_ = against->h_;
		return temp;
	}
};

#endif