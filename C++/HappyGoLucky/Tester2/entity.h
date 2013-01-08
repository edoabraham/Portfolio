#ifndef _H_ENTITY
#define _H_ENTITY

#include "graphics.h"

extern const unsigned int ELE_ARRAY;
extern const unsigned int MAX_MELEE_RANGE;
extern const unsigned int BASE_MP_RECOVERY;
extern const unsigned int BASE_SP_RECOVERY;

class Entity {
public:
	Entity();
	~Entity();

	void char_info(string name, unsigned int level, int element, vector<int> affinity, vector<int> resistances, bool playable);
	void char_stats(int atk, int matk, int hp, int mp, int sp, int def, int mdef, int mspd, int aspd, int range);
	void char_scale(int atk, int matk, int hp, int mp, int sp, int def, int mdef, int mspd, int aspd, int range);
	void raw_stats(int strength, int intelligence, int dexterity, int vitality, int stamina, int agility, int luck);

	CharacterObject entity_;

	void add_name(string name);
	void add_level(unsigned int level);
	void add_element(int element);
	void add_atk(int attack);
	void add_matk(int magic);
	void add_hp(int health);
	void add_mp(int mana);
	void add_sp(int stamina);
	void add_def(int defense);
	void add_mdef(int resistance);
	void add_mspd(int movement);
	void add_aspd(int speed);
	void add_range(int range);

	void add_s_atk(int attack);
	void add_s_matk(int magic);
	void add_s_hp(int health);
	void add_s_mp(int mana);
	void add_s_sp(int stamina);
	void add_s_def(int defense);
	void add_s_mdef(int resistance);
	void add_s_mspd(int movement);
	void add_s_aspd(int speed);
	void add_s_range(int range);

	void add_str(int strength);
	void add_int(int intelligence);
	void add_dex(int dexterity);
	void add_vit(int vitality);
	void add_sta(int stamina);
	void add_agi(int agility);
	void add_luk(int luck);


	const string name() const;
	const int element() const;
	const int atk() const;
	const int matk() const;
	const int hp() const;
	const int mp() const;
	const int sp() const;
	const int def() const;
	const int mdef() const;
	const int mspd() const;
	const int aspd() const;
	const int range() const;

	const int atk_s() const;
	const int matk_s() const;
	const int hp_s() const;
	const int mp_s() const;
	const int sp_s() const;
	const int def_s() const;
	const int mdef_s() const;
	const int mspd_s() const;
	const int aspd_s() const;
	const int range_s() const;

	// Output Formulas
	const int attack() const;
	const int magic() const;
	const int health() const;
	const int mana() const;
	const int mana_recovery() const;
	const int stamina() const;
	const int stamina_recovery() const;
	const int defense() const;
	const int mdefense() const;
	const int move_speed() const;
	const int attack_speed() const;
	const int critical() const;
	const int crit_resist() const;

	const int strength() const;
	const int intelligence() const;
	const int dexterity() const;
	const int vitality() const;
	const int agility() const;
	const int luck() const;

protected:
	string name_;
	unsigned int level_;
	int element_;
	int atk_;
	int matk_;
	int hp_;
	int mp_;
	int sp_;
	int def_;
	int mdef_;
	int mspd_;
	int aspd_;
	int range_;

	int str_;
	int int_;
	int dex_;
	int vit_;
	int sta_;
	int agi_;
	int luk_;

	// Scales
	int s_atk_;
	int s_matk_;
	int s_hp_;
	int s_mp_;
	int s_sp_;
	int s_def_;
	int s_mdef_;
	int s_mspd_;
	int s_aspd_;
	int s_range_;

	int crit_;
	int rcrit_;

	vector<int> affinities_;
	vector<int> resistances_;

	bool playable_;
};




#endif