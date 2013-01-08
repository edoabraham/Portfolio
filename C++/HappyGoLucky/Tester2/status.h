
// File Name: status.h

// Dependencies
#include "dependencies.h"

// Current Maximum Number of Elements
// Note: Make Sure to Check Size Against the Largest Index Value
const int NUM_OF_STATS = 25;

// Status Index Numbers
// Note: Make Sure to Increment NUM_OF_STATS when Adding New Stats
const int I_ELEMENT = 0;
const int I_ATTACK	= 1;
const int I_MAGIC_ATTACK	= 2;

const int I_HEALTH_POINTS	= 3;
const int I_MANA_POINTS		= 4;
const int I_STAMINA_POINTS	= 5;

const int I_HEALTH_RECOVERY = 6;
const int I_MANA_RECOVERY	= 7;
const int I_STAMINA_RECOVERY	= 8;

const int I_DEFENSE	= 9;
const int I_MAGIC_DEFENSE	= 10;

const int I_MOVEMENT_SPEED	= 11;
const int I_ATTACK_SPEED	= 12;
const int I_RANGE	= 13;

const int I_STRENGTH	= 14;
const int I_INTELLIGENCE	= 15;
const int I_DEXTERITY	= 16;
const int I_VITALITY	= 17;
const int I_STAMINA	= 18;
const int I_AGILITY	= 19;
const int I_LUCK	= 20;

const int I_CRITICAL_RATE	= 21;
const int I_CRITICAL_DAMAGE_INCREASE	= 22;
const int I_CRITICAL_RATE_RESIST	= 23;
const int I_CRITICAL_DAMAGE_RESIST	= 24;
// Last of the Element Index Values

// Class Name: Status
class Status {
public:
	Status();
	Status(vector<int> status);
	~Status();

	Status &operator+(const Status &operand);
	Status &operator==(const Status &operand);

	void add_element(int element);
	void add_atk(int attack);
	void add_matk(int magic);

	void add_hp(int health);
	void add_mp(int mana);
	void add_sp(int stamina);

	void add_hp_rec(int healthRecovery);
	void add_mp_rec(int manaRecovery);
	void add_sp_rec(int staminaRecovery);

	void add_def(int defense);
	void add_mdef(int mdefense);
	void add_mspd(int movement);
	void add_aspd(int speed);
	void add_range(int range);

	void add_str(int strength);
	void add_int(int intelligence);
	void add_dex(int dexterity);
	void add_vit(int vitality);
	void add_sta(int stamina);
	void add_agi(int agility);
	void add_luk(int luck);

	void add_crit_rate(int criticalRate);
	void add_crit_dmg_inc(int criticalDamageIncrease);
	void add_crit_rate_resist(int criticalResist);
	void add_crit_dmg_resist(int criticalDamageResist);

	// Output Formulas
	const int element() const;
	const int attack() const;
	const int magic_attack() const;

	const int health_points() const;
	const int health_recovery() const;
	const int mana_points() const;
	const int mana_recovery() const;
	const int stamina_points() const;
	const int stamina_recovery() const;

	const int defense() const;
	const int magic_defense() const;
	const int movement_speed() const;
	const int attack_speed() const;

	const int strength() const;
	const int intelligence() const;
	const int dexterity() const;
	const int vitality() const;
	const int agility() const;
	const int luck() const;

	const int critical() const;
	const int crit_resist() const;

private:
	void add_status(int index, int value);

	vector<int> status_;
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
};