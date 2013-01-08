#ifndef _H_ITEMS
#define _H_ITEMS
#include "dependencies.h"

class Item {
public:
	Item();

	~Item();
	bool & operator==(const Item &operand) const;
	const unsigned int id() const;
	const string name() const;
	const int strength() const;
	const int intelligence() const;
	const int dexterity() const;
	const int vitality() const;
	const int stamina() const;
	const int agility() const;
	const int luck() const;
	const int max_health() const;
	const int max_mana() const;
	const int max_stamina() const;
	const int rec_health() const;
	const int rec_mana() const;
	const int rec_stamina() const;
	const int attack() const;
	const int magic() const;
	const int atk_spd() const;
	const int mov_spd() const;
	const int defense() const;
	const int mdefense() const;
	const int critical() const;
	const int crit_res() const;
private:
	unsigned int id_;
	string name_;
	int str_;
	int int_;
	int dex_;
	int vit_;
	int sta_;
	int luk_;
	int agi_;
	int hp_;
	int mp_;
	int sp_;
	int hp_r;
	int mp_r;
	int sp_r;
	int atk_;
	int matk_;
	int mspd_;
	int aspd_;
	int def_;
	int mdef_;
	int crit_;
	int rcrit_;

	

};

class Items {
public:
	Items();
	~Items();
	Item info(unsigned int id);
private:

};






























#endif