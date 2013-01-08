#ifndef _H_GUI
#define _H_GUI

#include "dependencies.h"
#include "graphics.h"



class GUI_Elements {
public:
	GUI_Elements();
	~GUI_Elements();
	void display();
	void set_sprite();
	void add();
private:
	Graphic visual_;
	int xOffset_;
	int yOffset_;
	int height_, width_;

	class Box {
	public:
		Box();
		Box(int x, int y, int w, int h);
		~Box();
		const int x() const;
		const int y() const;
		const int x1() const;
		const int y1() const;

	private:
		int x_;
		int y_;
		int w_;
		int h_;
	};

	const bool is_clicked(SDL_Event event, const Box zone) const;

};

class User_Interface {
public:
	User_Interface();
	~User_Interface();
	void display();

private:
	

};
































#endif