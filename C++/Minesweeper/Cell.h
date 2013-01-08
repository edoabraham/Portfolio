/// Cell.h - Cell Class Declaration
/// Written By Jesse Z. Zhong (Takuto)

#ifndef __CELL_H__
#define __CELL_H__

#include "PrecompiledHeader.h"

// Max Dimensions
const int MAXROW = 24;
const int MAXCOL = 30;
const int BOMB = -1;

// Dimensions of a Cell/Button
const int CELL_WIDTH = 32;
const int CELL_HEIGHT = 32;

// States
const int REVEALED = 0;
const int HIDDEN = 1;
const int MARKED = 2;

// Length of the SDL Surface Array
const int ARRAY_LENGTH = 14;

/***********************************************************************
	Main Cell Class
		The Cell Class allows for each cell in the game table
		to have a set of its own characteristics such as its
		stored value (bomb or no bomb, number of surrounding 
		bombs, etc) as well as the current image it can display
		at a given moment.

************************************************************************/

// Class that Stores the Property of Each Cell
class Cell {
public:
	// Constructor
	Cell();

	// Destructor
	~Cell() {}

	// Initialize with Provided Values
	void initValues(int _row, int _col);

	// Current Image Display ID
	int imageNumber;
	bool clickedBomb;

	// Reveals Image According to Value if Image ID is Still Zero
	void revealImage() {
		if(imageNumber == 0) {
			if(val == BOMB) imageNumber = 10;
			else setImageNumber();
		}
	}

	// Cell Position Determining Functions
	int X1();
	int Y1();
	int X2();
	int Y2();

	// ID of the Cell, Row Position, Column Position
	int val, col, row, reveal;

	// Assigns Correct Image ID When Mouse is Clicked
	void setImageNumber() {
		// Display Bomb and Initiates Game Over Sequence
		if(reveal == REVEALED) {
			if(val == BOMB) {
				if(clickedBomb) imageNumber = 11;
				else imageNumber = 10;
			} else {
				// If ID of the Cell is in Range, Change Number to Display Correct Image
				if(val > 0 && val < ARRAY_LENGTH) imageNumber = val;
				else imageNumber = 9;
			}
		}
		if(reveal == HIDDEN) {
			imageNumber = 0;
		}
		if(reveal == MARKED) {
			imageNumber = 12;
		}
	}

	void click(Cell p[MAXROW][MAXCOL], int numOfBombs, int rowSize, int colSize);

	// For Stopping Reveal Area Recursion
	int tag;

private:
	int MouseX_, MouseY_;
	int RightMouseToggle_;
};

#endif