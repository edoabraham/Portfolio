#include "GUI.h"

GUI_Elements::Box::Box() {
	x_ = 0;
	y_ = 0;
	w_ = 0;
	h_ = 0;
}

GUI_Elements::Box::Box(int x, int y, int w, int h) {
	x_ = x;		y_ = y;		w_ = w;		h_ = h;
}

GUI_Elements::Box::~Box() {

}

GUI_Elements::GUI_Elements() {
	xOffset_ = 0;
	yOffset_ = 0;
	height_ = 0;
	width_ = 0;
}

const int GUI_Elements::Box::x() const {
	return x_;
}

const int GUI_Elements::Box::y() const {
	return y_;
}

const int GUI_Elements::Box::x1() const {
	return x_ + w_;
}

const int GUI_Elements::Box::y1() const {
	return y_ + h_;
}

const bool GUI_Elements::is_clicked(SDL_Event event, const Box zone) const {
	int x(0), y(0);
	x = event.button.x;
	y = event.button.y;
	if((x >= zone.x()) && (x <= zone.x1()) && (y >= zone.y()) && y <= zone.y1()) return true;
	else return false;
}
