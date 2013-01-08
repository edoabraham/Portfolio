#ifndef _H_GAME_DATA
#define _H_GAME_DATA
#define _SECURE_SCL 1

#include "graphics.h"
#include "scroll.h"
#include "characterOBJ.h"
#include "entity.h"
#include "dependencies.h"

extern const int MIN_CONST_LIST_SIZE;

class Game_Data {
public:
	Game_Data();
	~Game_Data();

	// Root File that Contains the File Names of Individual Data Files
	// Consolidates All Individual Files and Parses Them
	void parse_data(string fileName);

	void store_const(string fileName);
	vector<Entity> entity_list_;

private:
	void parse_file(string fileName);
	void parse_entities(const string line);
	void parse_items(const string line);
	void parse_graphics(const string line, int val);
	void parse_status(const string line, int val);
	void parse_animations(const string line, int val);
	bool comment(string line);
	string constant(const int val);
	string int_to_str(const int val);
	int str_to_int(const string line);
	string get_line(string &destination, istringstream &source, const int val, const int range);
	vector<string> const_str_;
	string default_;
	Entity temp_;
};

#endif