#ifndef _MAIN_FUNCTIONS_H
#define _MAIN_FUNCTIONS_H


#include "timer.h"

#include <iostream>


using namespace std;

/**********************************************************
	All Constant Globals Involved in Graphics Header
		Some are Subject to Change
***********************************************************/

// Title
const string TITLE = "MineSweeper of Doom";

// Bomb Search/Detection Area for Empty Cells
const int SEARCH_WIDTH = 3;
const int SEARCH_HEIGHT = 3;



// Screen SDL Global Surfaces
SDL_Surface *screen = NULL;
SDL_Surface *screen2 = NULL;
SDL_Surface *background = NULL;

// Number of Bits-Per-Pixel
const int SCREEN_BPP = 32;

// Margins Spacing of the Game
const int SCREEN_OFFSET_X = 48;
const int SCREEN_OFFSET_Y = 48;



// Constant Frames Per Second
const int FRAMES_PER_SECOND = 20;

// Calculates Frame Speed in Real Time
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;



// SDL Surface Array (Stores all the Cell Images)
SDL_Surface *cellPics[ARRAY_LENGTH] = { NULL };

// Passed Bomb Map
int bombMapPassed[MAXROW][MAXCOL] = { 0 };

// SDL Event Handler
SDL_Event event;

// Boolean to check if App/Game is still Running
bool quit = false;





/**********************************************************
	Forward Declarations and Prototypes
		Includes Functions and Classes
***********************************************************/

// Game Over Sequence
void endGameSquence(bool);

// swapping index i and j of an array
// i and j must be both within bounds for numbers.
void swap(int numbers[], int i, int j);

// given an array, the size of the array, and numOfChoices
// randomly shuffles the first numOfChoices element in the array to 
// randomly choose the first numOfChoices out of [0, size-1] choices
// the chosen elements' indexes will be stored in numbers array
// at indexes from [0, numOfChoices-1]
void chooseRandomly(int numbers[], int size, int numOfChoices);

// Given a bombMap of size rowSize * colSize, we will place numberOfBombs bombs
// randomly through out the bombMap.
// The bombMap you passed to us must be already initialized to all zeros.
void placeBombs(Cell p[MAXROW][MAXCOL], int rowSize, int colSize, int numberOfBombs);

// Given a bombMap with size rowSize & colSize, display the map
// for locations with a bomb, we are displaying a *
void displayBombMap(Cell p[MAXROW][MAXCOL], int rowSize, int colSize);

// Counts the Number of Bombs in the Surrounding Cells and Stores the Number
// In the Current Cell
void findSurroundingBombs(Cell p[MAXROW][MAXCOL], int rowSize, int colSize);

// Runs the System and Functionality of Game
void gameSystem(int numOfBombs, int bombMap[][MAXCOL], int condition[][MAXCOL], int rowSize, int colSize);

// Clicks a Given Cell
bool clickCell(int numOfBombs, int row, int col, int bombMap[][MAXCOL], int condition[][MAXCOL], int rowSize, int colSize);

// Marks a Given Cell
void markCell(Cell &p);

// Displays Help/Hints
void help(int bombMap[][MAXCOL], int rowSize, int colSize);

// Reveals Given Selections
bool revealArea(int numOfBombs, int row, int col, int bombMap[][MAXCOL], int condition[][MAXCOL], int rowSize, int colSize);

// Runs Game Win Sequence
bool winGame(int numOfBombs, Cell p[MAXROW][MAXCOL], int rowSize, int colSize);

// Runs Game Over Sequence and Game Terminates
bool gameOver(Cell p[MAXROW][MAXCOL], int rowSize, int colSize);

// Reveals the Whole Map when Game Ends
void endGameSquence(Cell p[MAXROW][MAXCOL], bool test);

// Prints Player Map
void displayGameMap(Cell p[MAXROW][MAXCOL], int rowSize, int colSize);

// Random Seed
int randomSeed();

// Determine the Width of the Screen Depending on the Row Size of the Table
unsigned int screenWidth(int val);

// Determine the Height of the Screen Depending on the Column Size of the Table
unsigned int screenHeight(int val);

// 
void printCellsToScreen(Cell p[MAXROW][MAXCOL], int width, int height);

// Display Cell Surface Depending on the Image State of the Cell
SDL_Surface *showSurface(int val);

// Checks if a Cell is Clicked on and Activates Functions
void isClicked (Cell p[MAXROW][MAXCOL], int numOfBombs, int rowSize, int colSize);

// Start Graphics Processes
void initGraphics(Cell p[MAXROW][MAXCOL]);


/*********************************************************************************
	Functions
		Graphical and System Functions

**********************************************************************************/

//* 
void swap(int numbers[], int i, int j) {
	int temp = numbers[i];
	numbers[i] = numbers[j];
	numbers[j] = temp;
}

//*
void chooseRandomly(int numbers[], int size, int numOfChoices) {
	int index;
	// first initialize the whole array to contain indices
	for (int i = 0; i < size; i++) {
		numbers[i] = i;
	}
	// to randomly choose the first numOfChoices, we don't need
	// to shuffle the whole array, just shuffle the first numOfChoices
	// element to get our choices
	for (int i = 0; i < numOfChoices; i++) {
		index = rand() % (size - i) + i;
		swap(numbers, i, index);
	}
}

//* Places the Bombs in Pseudo-Random Locations
void placeBombs(Cell p[MAXROW][MAXCOL], int rowSize, int colSize, int numberOfBombs) {
	int bombLocations[MAXROW * MAXCOL];
	int rowIndex;
	int colIndex;
	assert(rowSize >= 1 && rowSize <= MAXROW);
	assert(colSize >= 1 && colSize <= MAXCOL);
	assert(numberOfBombs >= 0 && numberOfBombs <= (rowSize * colSize));
	// randomly chose numberOfBombs locations for the bombs
	chooseRandomly(bombLocations, rowSize * colSize, numberOfBombs);
	// place the bombs in the map
	for (int i = 0; i < numberOfBombs; i++) {
		rowIndex = bombLocations[i] / colSize;
		colIndex = bombLocations[i] % colSize;
		p[rowIndex][colIndex].val = BOMB;
	}
}

//*
void displayBombMap(Cell p[MAXROW][MAXCOL], int rowSize, int colSize) {
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			if (p[i][j].val == BOMB) {
				cout << "* ";
			}
			else {
				cout << p[i][j].val << " ";
			}
		}
		cout << endl;
	}
}



/**********************************************************
	Functions and Classes Written for MineSweeper
		by Takuto (Jesse)
***********************************************************/

/* Set & Free All Images */
void setAllSurfaces() {

	// Store Individual Images into Image Array
	cellPics[0] = loadImage("Graphics/button.png");
	cellPics[1] = loadImage("Graphics/1.png");
	cellPics[2] = loadImage("Graphics/2.png");
	cellPics[3] = loadImage("Graphics/3.png");
	cellPics[4] = loadImage("Graphics/4.png");
	cellPics[5] = loadImage("Graphics/5.png");
	cellPics[6] = loadImage("Graphics/6.png");
	cellPics[7] = loadImage("Graphics/7.png");
	cellPics[8] = loadImage("Graphics/8.png");
	cellPics[9] = loadImage("Graphics/cleared.png");
	cellPics[10] = loadImage("Graphics/bomb.png");
	cellPics[11] = loadImage("Graphics/bomb-hit.png");
	cellPics[12] = loadImage("Graphics/flag.png");
	// Insert More When Necessary
}

/* Free All SDL Surfaces */
bool freeAllSurfaces() {

	// Frees Screen Surfaces
	SDL_FreeSurface(background);
	SDL_FreeSurface(screen);

	// Frees All Image Array Surfaces
	for(int i = 0; i < ARRAY_LENGTH; i++) {
		SDL_FreeSurface(cellPics[i]);
	}
	return true;
}

//* Detect if There are Any Bombs in the Surrounding Area of a Given Cell
void findSurroundingBombs(Cell p[MAXROW][MAXCOL], int rowSize, int colSize) {

	// Iterates Through Array with Nested Loop
	for(int i = 0; i < rowSize; i++) {
		for(int j = 0; j < colSize; j++) {

			// If Cell Contains a Bomb, Skip It; Otherwise Find Number of Bombs Surrounding Cell
			if(!(p[i][j].val == BOMB)) {

				// Counts the Number of Bombs
				int tallyBombs(0);

				// Iterates Through Surrounding Cells to Check for Bombs
				for(int k = (i - SEARCH_WIDTH / 2); k <= (i + SEARCH_WIDTH / 2); k++) {
					for(int l = (j - SEARCH_HEIGHT / 2); l <= (j + SEARCH_HEIGHT / 2); l++) {

						// If a Bomb is Found in Any Surrounding Cell, Tally Goes Up
						if(p[k][l].val == BOMB) tallyBombs++;
					}
				}

				// Tallied Bomb Number is Stored into Cell
				p[i][j].val = tallyBombs;
			}
		}
	}
}

//* Reveal a Left Clicked Cell
bool clickCell(int numOfBombs, int row, int col, Cell p[MAXROW][MAXCOL], int rowSize, int colSize) {
	// Only Run Code When Input is Within the Constraints of the Table
	if((row >= 0) && (row < rowSize) && (col >= 0) && (col < colSize)) {

		if(p[row][col].reveal ==  MARKED) {
			return true;
		} else
		// If a Bomb is Clicked On, Game Over
		if(p[row][col].val == BOMB) {
			p[row][col].clickedBomb = true;
			return gameOver(p, rowSize, colSize);
		}

		// If There's No Bomb Activated, Check If it Is Already Revealed; If so, Do Nothing
		else if(p[row][col].reveal == REVEALED) {

			// Return True to Continue the Game
			return true;

		} else {
			// If False, Reveal/Expose the Selected Cell
			p[row][col].reveal = REVEALED;

			// Check if Winning Conditions are Met
			return winGame(numOfBombs, p, rowSize, colSize);
		}

	} else {
		// Return True to Continue Game
		return true;
	}
}

//* Mark a Right Clicked Cell
void markCell(Cell &p) {

	// Checks if Cell Has Been Exposed Yet; If not...
	if(!(p.reveal == REVEALED)) {
		// Change to MARKED State if Not Already Marked, Else Un-Mark
		if(p.reveal == HIDDEN) {
			p.reveal = MARKED;
		} else if(p.reveal == MARKED) {
			p.reveal = HIDDEN;
		}
	}
}

//* Display Help/Hints
void help(Cell p[MAXROW][MAXCOL], int rowSize, int colSize) {

	cout << "Hints: " << endl;

	// Counts Bombs Row By Row and cout's Results
	for(int i = 0; i < rowSize; i++) {
		int rowBombs = 0;
		for(int j = 0; j < colSize; j++) {
			if(p[i][j].val == BOMB) rowBombs++;
		}
		string happyS;
		if(rowBombs == 1) happyS = "s";
		else happyS = " ";
		cout << endl << "Row " << i << " : " << rowBombs << " bomb" << happyS;
	}

	// Counts Bombs Column by Column and cout's Results
	for(int j = 0; j < colSize; j++) {
		int colBombs = 0;
		for(int i = 0; i < rowSize; i++) {
			if(p[i][j].val == BOMB) colBombs++;
		}
		string happyS;
		if(colBombs == 1) happyS = "s";
		else happyS = " ";
		cout << endl << "Column " << j << " : " << colBombs << " bomb" << happyS;
	}
	cout << endl << endl;
}

//* Runs Win Game Sequence
bool winGame(int numOfBombs, Cell p[MAXROW][MAXCOL], int rowSize, int colSize) {
	int tally = 0;
	for(int i = 0; i < rowSize; i++) {
		for(int j = 0; j < colSize; j++) {
			if(p[i][j].reveal == REVEALED) tally++;
		}
	}
	if(tally == ((rowSize * colSize) - numOfBombs)) {
		cout << endl << "You have won!!" << endl;
		return false;
	} else {
		return true;
	}
}

//* Runs Game Over Sequence
bool gameOver(Cell p[MAXROW][MAXCOL], int rowSize, int colSize) {
	for(int i = 0; i < rowSize; i++) {
		for(int j = 0; j < colSize; j++) {
			p[i][j].reveal = REVEALED;
		}
	}
	cout << endl << "You have lost..." << endl;
	return false;
}

//* Displays Layout of the Bomb Map in Console [Cheating] Haha
void displayGameMap(Cell p[MAXROW][MAXCOL], int rowSize, int colSize) {
	cout << endl;
	cout << "You're CHEATING!!! HAHA!!\n";
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
//			if(p[i][j].reveal == HIDDEN) cout << "# ";
//			else if(p[i][j].reveal == MARKED) cout << "? ";
//			else {
				if (p[i][j].val == BOMB) {
					cout << "* ";
				} else {
					cout << p[i][j].val << " ";
				}
			}
//		}
		cout << endl;
	}
}

//* Reveals an Area that Doesn't Contain Bombs When a Cell is Left Clicked
//* Combines the Functionality of the "clickCell()" Function
bool revealArea(int numOfBombs, int row, int col, Cell p[MAXROW][MAXCOL], int rowSize, int colSize) {
	if((row >= 0) && (row < rowSize) && (col >= 0) && (col < colSize) &&
		(p[row][col].reveal == HIDDEN) && (p[row][col].val == 0)) {
		p[row][col].reveal = REVEALED;
		revealArea(numOfBombs, row + 1, col, p, rowSize, colSize);
		revealArea(numOfBombs, row - 1, col, p, rowSize, colSize); 
		revealArea(numOfBombs, row, col + 1, p, rowSize, colSize);
		revealArea(numOfBombs, row, col - 1, p, rowSize, colSize);
		revealArea(numOfBombs, row + 1, col + 1, p, rowSize, colSize);
		revealArea(numOfBombs, row - 1, col - 1, p, rowSize, colSize); 
		revealArea(numOfBombs, row - 1, col + 1, p, rowSize, colSize);
		revealArea(numOfBombs, row + 1, col - 1, p, rowSize, colSize);
	} else clickCell(numOfBombs, row, col, p, rowSize, colSize);
	return true;
}

//* Prompts the "Game ID" to Seed for a Random Game Table
int numOfBombs(int rowSize, int colSize) {
	// Prompt Game ID
	int numberOfBombs(1);
	cout << "> Enter Number of Bombs between 1 and " << (rowSize * colSize - 1) << " : ";
	cin >> numberOfBombs;
	cout << endl;
	if(numberOfBombs < 1) return 1;
	else if(numberOfBombs > (rowSize * colSize - 1)) return (rowSize * colSize - 1);
	else return numberOfBombs;
}

//* Prompts User for the 
int colSizePrompt() {
	int columnSize(1);
	cout << "> Choose a Column Height \n> between 2 and " << MAXCOL << " : ";
	cin >> columnSize;	// Replace
	cout << endl;
	if(columnSize >= MAXCOL) return MAXCOL;
	else if(columnSize <= 2) return 2;
	else return columnSize;
}

int rowSizePrompt() {
	int rowwSize(1);
	cout << "> Choose a Row Width \n> between 2 and " << MAXROW << " : ";
	cin >> rowwSize;				// Replace
	cout << endl;
	if(rowwSize >= MAXROW) return MAXROW;
	else if(rowwSize <= 2) return 2;
	else return rowwSize;
}

int randomSeed() {
	int seed(0);
	cout << "> Please Enter a Game ID or \n> Enter 0 for a Random Game : ";
	cin >> seed;	// Replace
	cout << endl;
	if(seed < 0) return 0;
	if(seed == 0) return (unsigned) time(0);
	else return seed;
}


void isClicked (Cell p[MAXROW][MAXCOL], int numOfBombs, int rowSize, int colSize) {

	for(int i = 0; i < rowSize; i++) {
		for(int j = 0; j < colSize; j++) {
			p[i][j].click(p, numOfBombs, rowSize, colSize);
		}
	}
}

void Cell::click(Cell p[MAXROW][MAXCOL], int numOfBombs, int rowSize, int colSize) {
	MouseX_ = event.button.x;
	MouseY_ = event.button.y;

	// Tests if Any Mouse Buttons Were Pressed
	if(event.type == SDL_MOUSEBUTTONDOWN) {

		// Checks if Left Mouse Button is Pressed
		if(event.button.button == SDL_BUTTON_LEFT) {
			if((MouseX_ > X1()) && (MouseX_ < X2()) && (MouseY_ > y1()) && (MouseY_ < Y2())) {
				revealArea(numOfBombs, row, col, p, rowSize, colSize);

			}
		}

		if(event.button.button == SDL_BUTTON_RIGHT) {

			// Checks if Mouse is in the Boundaries of this Cell When Button is Pressed
			if((MouseX_ > X1()) && (MouseX_ < X2()) && (MouseY_ > y1()) && (MouseY_ < Y2()) && (RightMouseToggle_ == 0)) {
				markCell(p[row][col]);
			}
		}
	}
}

void keyboardEvent (Cell p[MAXROW][MAXCOL], int rowSize, int colSize) {
	if(event.type == SDL_KEYDOWN) {
		if(event.key.keysym.sym == SDLK_h) {
			help(p, rowSize, colSize);
		}
		if(event.key.keysym.sym == SDLK_c) {
			displayGameMap(p, rowSize, colSize);
		}
	}
}

/* *************************************************************** *\

	Starts and Maintains the GUI of the Game
		Also Handles All the Important Game Events

\* *************************************************************** */

void gameInitialization () {

	cout << "//***********************************************************************\\" << endl
		 << "                         Welcome to Minesweeper!!" << endl
		 << "\\***********************************************************************//" << endl << endl;

	srand(randomSeed());
	int gameWidth = rowSizePrompt();
	int gameHeight = colSizePrompt();
	int gameBombs = numOfBombs(gameWidth, gameHeight);

	Cell gameCells[MAXROW][MAXCOL];

	// put some random bombs into the map
	placeBombs(gameCells, gameWidth, gameHeight, gameBombs);

	findSurroundingBombs(gameCells, gameWidth, gameHeight);

	// Initializes Cell Values
	initGraphics(gameCells);
	
	// Initializes SDL Processes
	SDL_Init(SDL_INIT_EVERYTHING);

	// Sets Game Icon
	SDL_WM_SetIcon(IMG_Load("Graphics/Minesweeper_Icon.png"), NULL);

	// Sets up Dimensions and Properties of the Screen's Surface
	screen = SDL_SetVideoMode(screenHeight(gameHeight), screenWidth(gameWidth), SCREEN_BPP, SDL_SWSURFACE);

	// Gives Title to the App's Window
	SDL_WM_SetCaption(TITLE.c_str(), NULL);

	// Loads Background Image into Background SDL Surface
	background = loadImage("Graphics/Background.png");

	// Prints First Frame of Background to Freshly Initialized Screen
	applySurface(0, 0, background, screen, NULL);

	// Loads All Images into Image Array
	setAllSurfaces();

	// Declares New Timer Class Named FPS
	// Used for Controlling the Frame Rate as well as other Time Functions of Game
	Timer fps;

	// Game Event Loop; Core to the Operation of the Game
	while(quit == false) {

		// Starts the Game's Timer
		fps.start();

		// Polls/Stands-by for Events that Come In
		while(SDL_PollEvent(&event)) {

			// Checks if App has been Exited
			if(event.type == SDL_QUIT) {
				// If "TRUE", then Free All Surfaces from Memory
				quit = true;
			}

			isClicked(gameCells, gameBombs, gameWidth, gameHeight);

			keyboardEvent(gameCells, gameWidth, gameHeight);
		}
		// Blitting List (In Order with Bottom First, Top Last)
		// Re-apply Background Surface
		applySurface(0, 0, background, screen, NULL);
		printCellsToScreen(gameCells, gameWidth, gameHeight);

		// Flips "screen" Surface to the Screen
		SDL_Flip(screen);

		// Pauses For Set Time Between Frames to Maintain Smooth Consistent Animations
		if(fps.get_ticks() < SKIP_TICKS) {
			SDL_Delay(SKIP_TICKS - fps.get_ticks());
		}
		
	}
}

//* Sets Screen Width Depending on Width of Game
unsigned int screenWidth(int val) {

	return SCREEN_OFFSET_X * 2 + CELL_WIDTH * val;
}

//* Sets Screen Height Depending on Height of Game
unsigned int screenHeight(int val) {

	return SCREEN_OFFSET_Y * 2 + CELL_HEIGHT * val;
}

//* Prints all of the Cells in Array to Screen
void printCellsToScreen(Cell p[MAXROW][MAXCOL], int width, int height) {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			p[i][j].setImageNumber();
			applySurface(SCREEN_OFFSET_X + j * CELL_WIDTH, SCREEN_OFFSET_Y + i * CELL_HEIGHT, showSurface(p[i][j].imageNumber), screen, NULL);
		}
	}
}

//* Displays Cell Image Depending on the Cell's Status
SDL_Surface *showSurface(int val) {
if(val < ARRAY_LENGTH && val >= 0) return cellPics[val];
else return NULL;
}

//* Game Over Sequence
void endGameSquence(Cell p[MAXROW][MAXCOL], bool test) {
	for(int i = 0; i < MAXROW; i++) {
		for(int j = 0; j < MAXCOL; j++) {
			p[i][j].revealImage();
		}
	}
}

//* Initializes Cell Values
void initGraphics(Cell p[MAXROW][MAXCOL]) {
	for(int i = 0; i < MAXROW; i++) {
		for(int j = 0; j < MAXCOL; j++) {
			p[i][j].initValues(j, i);
		}
	}
}


/*
	Start Game Text Box Prompter
		First Window

*/

void gamePrompter () {
	// Initializes SDL Processes
	SDL_Init(SDL_INIT_EVERYTHING);

	// Sets Game Icon
	SDL_WM_SetIcon(IMG_Load("Graphics/Minesweeper_Icon.png"), NULL);

	// Sets Up Video for Prompter Window
	screen2 = SDL_SetVideoMode(400, 200, SCREEN_BPP, SDL_SWSURFACE);

	// Initializes SDL Processes
	SDL_Init(SDL_INIT_EVERYTHING);

	// Gives Title to the App's Window
	SDL_WM_SetCaption(TITLE.c_str(), NULL);

	// Loads Background Image into Background SDL Surface
	background = loadImage("Graphics/Background.png");

	// Prints First Frame of Background to Freshly Initialized Screen
	applySurface(0, 0, background, screen, NULL);

}














#endif