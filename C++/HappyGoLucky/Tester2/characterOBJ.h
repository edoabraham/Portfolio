// Q. How crazy are you Jesse?
// A. "Crazy Enough"

#ifndef _CHARACTEROBJ_H
#define _CHARACTEROBJ_H

#include "dependencies.h"
#define _SECURE_SCL 1

using namespace std;
// Global Constants
extern const int MAX_DB_LENGTH;

/***************************************************************************
	Rectangle
/***************************************************************************/
struct rect {
	int x, y;
	int w, h;
	rect() {}
	rect(int _x, int _y, int _w, int _h) {
		x = _x;	y = _y;	w = _w;	h = _h;
	}
	~rect() {}
	void init(int _x, int _y, int _w, int _h) {
		x = _x;	y = _y;	w = _w;	h = _h;
	}
};


/***************************************************************************
	Player Info
/***************************************************************************/
class PlayerInfo {
public:
	int id;			// For keeping track of multiple game saves
	string name;
	rect playerObject;
	int map;
	int level;
	int skill1, skill2;
	int katar, dagger, knife, bow;
	int screenSize;	// I'm sticking this here; the number of text files is overwhelming
	// Scoring
	int kills;
	void init(int _id, string _name, int _x, int _y, int _map, int _skill1, int _skill2, int _katar,
		int _dagger, int _knife, int _bow, int _kills, int _screen) {
			id = _id;	name = _name;	map = _map;	skill1 = _skill1;	skill2 = _skill2;
			katar = _katar;	dagger = _dagger;	knife = _knife;	bow = _bow;	kills = _kills;
			screenSize = _screen;
			playerObject.init(_x, _y, 0, 0);
	}
	PlayerInfo() {}
	~PlayerInfo() {}
};

struct PlayerControls {
	int Left,	Right,	Jump,	Duck,	Backslide,		
		Katar,	Dagger,	Bow,	Knife,	Grab,	Block,
		Skill1,	Skill2,
		Equipment,	Inventory, Skills,	Menu,
		Item1,	Item2,	Item3,	Item4,	Item5,	Item6;
	string fool;							// Delete
};

//void textReaderOBJ(string fileName);
//void textReaderItemDB(string fileName);
void textReaderCtrlDB(string fileName, PlayerControls &p);
void textReaderSaveList(string fileName, vector<PlayerInfo> &p);
void newSaveFile(string fileName);
void defaultControls (string file);
int charReturn (const string input);

#endif