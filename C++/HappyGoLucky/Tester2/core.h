#ifndef _H_CORE
#define _H_CORE
#define _SECURE_SCL 1
#include "game_data.h"
#include "map.h"
#include "controller.h"
#include "timer.h"
#include "entity.h"

// Globals
extern SDL_Surface *screen;
extern SDL_Surface *fart;
extern bool quit;
extern SDL_Event event;

// Temp Globals
extern Game_Data The_Data;
extern Entity Marluxia;
extern CharacterObject Cel;
extern ScrollMap map1;
extern Scroll camera;
extern PlayerControls player1Controls;
extern vector<PlayerInfo> saveList;

// Const
extern const int SCREEN_WIDTH;				
extern const int SCREEN_HEIGHT;
extern const int SCREEN_BPP;	

void gameDataList ();

/******************************************************************************************************
	Controls
		Controls, or the Core, more or less controls the game.

*******************************************************************************************************/

Entity selected_character(int val, vector<Entity> entity_list);

template <class T>
T isReal(T p);

// Returns the Correct Screen Dimensions
unsigned int screenWidth(int settingNumber);
unsigned int screenHeight(int settingNumber);

// Starts, Reads, and Stores Necessary Settings to Start Game
bool initGameData ();

// Initializes Specified Window
/******************************************************************************************************/
void intializeGame ();








#endif