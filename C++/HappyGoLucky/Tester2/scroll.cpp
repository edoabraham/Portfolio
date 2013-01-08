#include "scroll.h"

/******************************************************************
			Base Scroll Class Functions
******************************************************************/
Background::Background() {
	left_ = 0;
	right_ = 0;
}

void Background::init(int left, int right) {
	left_ = left;	right_ = right;
}

Background::~Background() {
	left_ = 0;
	right_ = 0;
}

ScrollMap::ScrollMap() {
	width_ = 0;
	listSize_ = 0;
}

void ScrollMap::add(string fileName, int width) {
	Background temp;
	temp.image_ = loadImage(fileName);
	int left = width_;
	width_ += width;
	temp.init(left, width_);
	mapList_.push_back(temp);
	listSize_++;
}

ScrollMap::~ScrollMap() {
	for(int i = int(mapList_.size() - 1); i >= 0; i--) {
		mapList_.pop_back();
	}
	width_ = 0;
	listSize_ = 0;
}

void ScrollMap::print(SDL_Surface *destination, int x, int width, int yOffSet) {
	bool mapsAdded = false;
	bool over = false;
	for(int i = 0; !(over) && i < listSize_; i++) {
		mapList_.at(i);
		if((x <= mapList_[i].left_ && mapList_[i].left_ <= (x + width)) || (x <= mapList_[i].right_ && mapList_[i].right_ <= (x + width)) ||
			(mapList_[i].left_ <= x && x <= mapList_[i].right_) || (mapList_[i].left_ <= (x + width) && (x + width) <= mapList_[i].right_)) {
			applySurface(mapList_[i].left_ - x, yOffSet, mapList_[i].image_, destination);
		} else if(mapsAdded) over = true;
	}
}

/******************************************************************
			Scrolling Functions
******************************************************************/

Scroll::Scroll() {
	leftMargin_ = 0;
	rightMargin_ = 0;
	topMargin_ = 0;
	botMargin_ = 0;
}

Scroll::Box::Box() {
	x1_ = 0;
	y1_ = 0;
	w_ = 0;
	h_ = 0;
}

Scroll::Box::~Box() {
	x1_ = 0;
	y1_ = 0;
	w_ = 0;
	h_ = 0;
}

int Scroll::Box::x2() const { return x1_ + w_; }

int Scroll::Box::y2() const { return y1_ + h_; }

Scroll::~Scroll() { 
	leftMargin_ = 0;
	rightMargin_ = 0;
	topMargin_ = 0;
	botMargin_ = 0;
}

void Scroll::player(int x, int y, int w, int h) {
	player_ = Box(x, y, w, h);
}

void Scroll::bound(int leftMargin, int rightMargin, int topMargin, int bottomMargin) {
	leftMargin_ = leftMargin;	rightMargin_ = rightMargin;	topMargin_ = topMargin;	botMargin_ = bottomMargin;
	if(window_.x2() != 0 || window_.y2() != 0) setBounds();
}

void Scroll::window(int x, int y, int w, int h) {
	window_ = Box(x, y, w, h);
	if(!(leftMargin_ == 0 && rightMargin_ == 0 && topMargin_ == 0 && botMargin_ == 0)) setBounds();
}

void Scroll::setBounds() {
	if(!(leftMargin_ + rightMargin_ > window_.w_) && !(topMargin_ + botMargin_ > window_.h_)) {
		bounds_ = Box(leftMargin_, topMargin_, window_.w_ - leftMargin_ - rightMargin_, window_.h_ - topMargin_ - botMargin_);
	}
	else bounds_ = window_;
}

void Scroll::print(ScrollMap mapScroll, SDL_Surface *destination, int &xScreen, int &yScreen, int &x, int xSpeed, int ySpeed) {
	player_.x1_ = xScreen;
	player_.y1_ = yScreen;
	window_.x1_ = x;

	if(player_.x1_ <= bounds_.x1_ && xSpeed < 0) window_.x1_ += xSpeed;
	if(player_.x1_ <= bounds_.x1_ && xSpeed > 0) player_.x1_ += xSpeed;

	if(player_.x2() >= bounds_.x2() && xSpeed > 0) window_.x1_ += xSpeed;
	if(player_.x2() >= bounds_.x2() && xSpeed < 0) player_.x1_ += xSpeed;

	if(player_.x1_ > bounds_.x1_ && player_.x2() < bounds_.x2()) player_.x1_ += xSpeed;

	if(player_.y1_ < bounds_.y1_);
	else player_.y1_ += ySpeed;
	if(player_.y2() > bounds_.y2());
	else player_.y1_ += ySpeed;

	xScreen = player_.x1_;
	yScreen = player_.y1_;
	x = window_.x1_;
	mapScroll.print(destination, window_.x1_, window_.w_);
}




















/******************************************************************
			Scroll With Parallax Built In
******************************************************************/


