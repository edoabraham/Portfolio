#ifndef _H_PROFESSION
#define _H_PROFESSION
// File Name: profession.h

// Includes
#include "dependencies.h"

// Enumerate
enum unsigned int profession {
	KNIGHT = 1,
	MAGICIAN,
	SCOUT,
	ARCHER,
	MERCHANT,
	ACOLYTE
};

// Temporary Hard Code
enum unsigned int prof_mastery {
	// KNIGHT
	RUNE_KNIGHT = 1,
	PALADIN,
	DRAGOON,
	BERSERKER,

	// MAGICIAN
	WIZARD = 10,
	SCHOLAR,
	ASURA,
	SOUL,

	// SCOUT
	ASSASSIN = 20,
	SNIPER,
	NINJA,
	STALKER,

	// ARCHER
	RANGER = 30,
	MINSTREL,
	GUNSLINGER,
	ACROBAT,

	// MERCHANT
	ALCHEMIST = 40,
	BIOCHEMIST,
	BLACKSMITH,
	ENGINEER,

	// ACOLYTE
	PRIEST = 50,
	HIGH_PRIEST,
	EXORCIST,
	MONK,
	CHAMPION,
	KUNG_FU
};

// Class Name: Profession
class Profession {
public:
	Profession();
	~Profession();
	void InitializeData();
	vector<int> ModifierArray(unsigned int&) const;
	vector<int> LearnableSkills(unsigned int&) const;
private:
	vector<int<int>> modfierList_;
	vector<int<int>> skillLearnableList_;
	
};



#endif