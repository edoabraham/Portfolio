/// Cell.cpp - Cell Class Method Implementation
/// Written By Jesse Z. Zhong (Takuto)

#include "PrecompiledHeader.h"
#include "Cell.h"

// Constructor
Cell::Cell() {
	imageNumber = 0;
	val = 0;
	col = 0;
	row = 0;
	reveal = HIDDEN;
	clickedBomb = 0;
	RightMouseToggle_ = 0;

	MouseX_ = 0;
	MouseY_ = 0;

	tag = 0;
}

// Initialize with Provided Values
void Cell::initValues(int _row, int _col) {
	col = _row; row = _col;
}

// Cell Position Determining Functions
int Cell::X1() { 
	return SCREEN_OFFSET_X + col * CELL_WIDTH; 
}
int Cell::Y1() { 
	return SCREEN_OFFSET_Y + row * CELL_HEIGHT; 
}
int Cell::X2() { 
	return SCREEN_OFFSET_X + (col + 1) * CELL_WIDTH; 
}
int Cell::Y2() { 
	return SCREEN_OFFSET_Y + (row + 1) * CELL_HEIGHT; 
}