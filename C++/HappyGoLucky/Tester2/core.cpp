#include "core.h"

// Game Globals
SDL_Surface *screen = NULL;
SDL_Surface *fart = NULL;
bool quit = false;
SDL_Event event;

// Default Screen Size
const int SCREEN_WIDTH = 1280;				
const int SCREEN_HEIGHT = 800;

// Bits Per Pixel
// 32 Bit; Functions will Include Optimizer
const int SCREEN_BPP = 32;

// Temps
Game_Data The_Data;
CharacterObject Cel;
Scroll camera;
PlayerControls player1Controls;
vector<PlayerInfo> saveList;
Entity Marluxia;
ScrollMap map1;

void gameDataList () {

	// Marluxia
	Marluxia.entity_.load("MarluxiaProof.png");
	Marluxia.entity_.animations(8);
	Marluxia.entity_.offset(100, 90);

	// Standing
	Marluxia.entity_.add(0,0,0,100,100);
	Marluxia.entity_.add(0,100,0,100,100);
	Marluxia.entity_.add(0,200,0,100,100);
	Marluxia.entity_.add(0,300,0,100,100);
	// Movement
	Marluxia.entity_.add(1,0,0,100,100);
	Marluxia.entity_.add(1,100,0,100,100);
	Marluxia.entity_.add(1,200,0,110,100);
	Marluxia.entity_.add(1,300,0,100,100);
	// Floating
	Marluxia.entity_.add(2,400,0,100,100);
	Marluxia.entity_.add(2,500,0,100,100);
	Marluxia.entity_.add(2,600,0,100,100);
	Marluxia.entity_.add(2,700,0,100,100);
	Marluxia.entity_.add(2,800,0,100,100);
	// Attack1
	Marluxia.entity_.add(3,0,100,100,150,-7,50);
	Marluxia.entity_.add(3,100,100,100,150,-7,50);
	Marluxia.entity_.add(3,200,100,90,150,-7,50);
	Marluxia.entity_.add(3,290,100,90,150,-17,50);
	Marluxia.entity_.add(3,390,100,100,150,-7,50);
	Marluxia.entity_.add(3,600,100,200,150,-39,50);
	//Marluxia.add(3,500,100,100,150,-7,50);
	Marluxia.entity_.add(3,800,100,200,150,-39,50);
	// Attack2
	Marluxia.entity_.add(4,0,250,100,150,-7,60);
	Marluxia.entity_.add(4,100,250,100,150,-7,60);
	Marluxia.entity_.add(4,200,250,100,150,-7,60);
	Marluxia.entity_.add(4,300,250,100,150,-7,60);
	Marluxia.entity_.add(4,100,250,100,150,-7,60);
	Marluxia.entity_.add(4,200,250,100,150,-7,60);
	Marluxia.entity_.add(4,300,250,100,150,-7,60);
	Marluxia.entity_.add(4,0,250,100,150,-7,60);
	// Attack3
	Marluxia.entity_.add(5,0,400,100,100,-7,5);
	Marluxia.entity_.add(5,100,400,100,100,-7,5);
	Marluxia.entity_.add(5,200,400,100,100,-7,5);
	Marluxia.entity_.add(5,300,400,100,100,-7,5);
	Marluxia.entity_.add(5,400,400,100,100,18,5);
	Marluxia.entity_.add(5,500,400,100,100,18,5);
	Marluxia.entity_.add(5,600,400,100,100,18,5);
	Marluxia.entity_.add(5,700,400,100,100,18,5);
	Marluxia.entity_.add(5,800,400,100,100,18,5);
	// Attack4
	Marluxia.entity_.add(6,0,500,100,110,-7,15);
	Marluxia.entity_.add(6,100,500,100,110,-7,15);
	Marluxia.entity_.add(6,200,500,100,110,-7,15);
	Marluxia.entity_.add(6,300,500,100,110,-7,15);
	Marluxia.entity_.add(6,400,500,100,110,-7,15);
	Marluxia.entity_.add(6,500,500,100,110,-7,15);
	Marluxia.entity_.add(6,600,500,100,110,-7,15);
	Marluxia.entity_.add(6,700,500,100,110,-7,15);
	Marluxia.entity_.add(6,800,500,100,110,-7,15);
	Marluxia.entity_.add(6,900,500,100,110,-7,15);

	// Map
	map1.add("Test Background.png", 1920);
	map1.add("Test Background.png", 1920);
	map1.add("Test Background.png", 1920);
	The_Data.store_const("Data/const.txt");
	The_Data.parse_data("Data/Directories.txt");
}

Entity selected_character(int val, vector<Entity> entity_list) {
	if(!entity_list.empty() && unsigned(val) < entity_list.size() && val >= 0) return entity_list[val];
	else {
		cout << "Score!" << endl;
		return Marluxia;
	}
}

template <class T>
T isReal(T p) {
	T *i = &p;
	T temp = 0;
	if(i == NULL) return temp;
	else return p;
}

// Returns the Correct Screen Dimensions
unsigned int screenWidth(int settingNumber) {
	switch (settingNumber) {
	case 0:	return 600;	break;
	case 1:	return 800;	break;
	case 2:	return 1024;	break;
	case 3:	return 1280;	break;
	case 4:	return 1920;	break;
	default:
		return SCREEN_WIDTH;	break;
	}
}

unsigned int screenHeight(int settingNumber) {
	switch (settingNumber) {
	case 0:	return 400;	break;
	case 1:	return 600;	break;
	case 2:	return 768;	break;
	case 3:	return 800;	break;
	case 4:	return 1080;	break;
	default:
		return SCREEN_HEIGHT;	break;
	}
}

// Starts, Reads, and Stores Necessary Settings to Start Game
bool initGameData () {				// One word: Fuck!
	// Seed Random Values
	srand((unsigned) time (0));			

	// Parse Lists
	textReaderSaveList("Saves.txt", saveList);
	//textReaderItemDB("itemdb.txt");
	textReaderCtrlDB("controls.txt", player1Controls);
	return true;
}

// Initializes Specified Window
/******************************************************************************************************/
void intializeGame () {
	/******************************************************************************************************/
	// Reads and Stores Game Data
	initGameData();

	// Starts All SDL Processes
	SDL_Init(SDL_INIT_EVERYTHING);

	// Sets Game Icon
	//SDL_WM_SetIcon(IMG_Load("Graphics/Minesweeper_Icon.png"), NULL);

	// Sets Up the Screen Surface
	screen = SDL_SetVideoMode(screenWidth(isReal(saveList[0].screenSize)), screenHeight(isReal(saveList[0].screenSize)), SCREEN_BPP, SDL_SWSURFACE);

	// Sets the Window Name
	SDL_WM_SetCaption(GAME_NAME.c_str(), NULL);

	gameDataList();

	// Declares New Timer Class Named FPS
	// Used for Controlling the Frame Rate as well as other Time Functions of Game
	Timer fps;



	// Player States
	int xScreen = 300;
	int yScreen = 600;
	int x = 0;
	int xSpeed = 10;
	int ySpeed = 5;
	camera.player(xScreen, yScreen, 100, 150);
	camera.bound(500, 500, 0, 0);
	camera.window(x, 0, screenWidth(isReal(saveList[0].screenSize)), screenHeight(isReal(saveList[0].screenSize)));
	CharacterControls player1;
	Entity Main_Character = selected_character(0, The_Data.entity_list_);
	Oscillation osc;
	osc.set(0.04, 3.00);


	// Game Event Loop; Core to the Operation of the Game
	while(quit == false) {

		// Starts the Game's Timer
		fps.start();

		// Polls/Stands-by for Events that Come In
		while(SDL_PollEvent(&event)) {

			player1.actionEvent(player1Controls, xSpeed, ySpeed, event);


			if(event.type == SDL_QUIT) {		// If you closed my program T^T buh bye~

				quit = true;
				// Save here
			}

			/* Here for Individual Press and React */
		}

		/* Here for Hold and React */

		// Blitting List (In Order with Bottom First, Top Last)
		// Re-apply Background Surface
		camera.print(map1, screen, xScreen, yScreen, x, player1.xMoveSpeed(), player1.yMoveSpeed());
		Main_Character.entity_.playAnimation(screen, xScreen, yScreen/*osc.displacement(yScreen)*/, player1.state(), player1.faceDirection());

		// Flips "screen" Surface to the Screen
		SDL_Flip(screen);

		// Pauses For Set Time Between Frames to Maintain Smooth Consistent Animations
		if(fps.get_ticks() < SKIP_TICKS) {
			SDL_Delay(SKIP_TICKS - fps.get_ticks());
		}
		//cout << x << "    Speed : " << player1.xMoveSpeed() << "    Screen : " << xScreen << endl;
	}
}
















//void Sakura() {
//	sakura.load("Sakura Particles.png", 1, 10, 20, 26);
//	sakura.clipYes(0,5,7,4,7);
//	sakura.clipYes(1,17,4,4,7);
//	sakura.clipYes(2,27,4,4,7);
//	sakura.clipYes(3,41,2,5,7);
//	sakura.clipYes(4,3,20,8,3);
//	sakura.clipYes(5,16,18,7,5);
//	sakura.clipYes(6,28,17,8,4);
//	sakura.clipYes(7,43,17,6,5);
//
//	sakura1.stencil(sakura,1,30,30);
//}