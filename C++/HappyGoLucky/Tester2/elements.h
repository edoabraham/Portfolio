#ifndef _H_ELEMENTS
#define _H_ELEMENTS

#include "dependencies.h"

extern const unsigned int NUM_ELE;
extern const unsigned int LVL_ELE;

enum Element:unsigned int {
	NEUTRAL = 1,
	WATER = 2,
	FIRE = 4,
	WIND = 8,
	EARTH = 16,
	ELECTRIC = 32,
	POISON = 64,
	STEEL = 128,
	HOLY = 256,
	SHADOW = 512,
	GHOST = 1024
};

class Elemental {
public:
	Elemental();
	~Elemental();
	double damage_modifier(unsigned int atk_signature, unsigned int def_signature, unsigned int level);
private:
	double effectiveness(unsigned int ele, unsigned int def_signature, unsigned int level);
	void read_in(ifstream &file_stream);
	void store();
	void resize();
	vector<vector<double>> advantages_;
};

// Global Elements
static const Elemental Elements;





















#endif