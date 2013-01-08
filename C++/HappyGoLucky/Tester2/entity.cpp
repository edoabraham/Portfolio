#include "entity.h"

const unsigned int ELE_ARRAY = 12;
const unsigned int MAX_MELEE_RANGE = 100;
const unsigned int BASE_MP_RECOVERY = 6;
const unsigned int BASE_SP_RECOVERY = 5;

Entity::Entity() {
	level_ = 1;
	element_ = 1;
	atk_ = 1;
	matk_ = 1;
	hp_ = 1;
	mp_ = 1;
	def_ = 1;
	mdef_ = 1;
	mspd_ = 1;
	aspd_ = 1;
	range_ = 1;

	str_ = 1;
	int_ = 1;
	dex_ = 1;
	vit_ = 1;
	sta_ = 1;
	agi_ = 1;
	luk_ = 1;

	s_atk_ = 1;
	s_matk_ = 1;
	s_hp_ = 1;
	s_mp_ = 1;
	s_def_ = 1;
	s_mdef_ = 1;
	s_mspd_ = 1;
	s_aspd_ = 1;
	s_range_ = 1;

	crit_ = 1;
	rcrit_ = 1;

	playable_ = false;

}

Entity::~Entity() {
	affinities_.resize(ELE_ARRAY);
	resistances_.resize(ELE_ARRAY);
}

void Entity::char_info(string name, unsigned int level, int element, vector<int> affinity, vector<int> resistances, bool playable) {
	name_ = name;	level_ = level;		element_ = element;		playable_ = playable;

	if(!affinities_.empty() && !resistances_.empty() && !affinity.empty() && !resistances.empty()
		&& (affinities_.size() + resistances_.size() == ELE_ARRAY * 2)
		&& (affinity.size() + resistances.size()) == ELE_ARRAY * 2) {
			affinities_ = affinity;
			resistances_ = resistances;
	} else {
		affinities_.resize(ELE_ARRAY);
		resistances_.resize(ELE_ARRAY);

		if(!affinity.empty() && affinity.size() == ELE_ARRAY) resistances_ = resistances;
		else {
			for(unsigned int i = 0; i < affinities_.size(); i++)
				affinities_[i] = 0;
		}

		if(!resistances.empty() && resistances.size() == ELE_ARRAY) resistances_ = resistances;
		else {
			for(unsigned int i = 0; i < resistances_.size(); i++)
				resistances_[i] = 0;
		}
	}
}

void Entity::char_stats(int atk, int matk, int hp, int mp, int sp, int def, int mdef, int mspd, int aspd, int range) {
	atk_ = atk;	matk_ = matk;	hp_ = hp;	mp_ = mp;	sp_ = sp;	def_ = def;	mdef_ = mdef;
	mspd_ = mspd;	aspd_ = aspd;	range_ = range;
}

void Entity::char_scale(int atk, int matk, int hp, int mp, int sp, int def, int mdef, int mspd, int aspd, int range) {
	s_atk_ = atk;	s_matk_ = matk;		s_hp_ = hp;		s_mp_ = mp;		s_sp_ = sp;		s_def_ = def;	
	s_mdef_ = mdef;	s_mspd_ = mspd;		s_aspd_ = aspd;					s_range_ = range;
}

void Entity::raw_stats(int strength, int intelligence, int dexterity, int vitality, int stamina, int agility, int luck) {
	str_ = strength;	int_ = intelligence;	dex_ = dexterity;
	vit_ = vitality;	sta_ = stamina;			agi_ = agility;		luk_ = luck;
}

void Entity::add_name(string name) {
	name_ = name;
}

void Entity::add_level(unsigned int level) {
	level_ = level;
}

void Entity::add_element(int element) {
	element_ = element;
}

void Entity::add_atk(int attack) {
	atk_ = attack;
}
void Entity::add_matk(int magic) {
	matk_ = magic;
}

void Entity::add_hp(int health) {
	hp_ = health;
}

void Entity::add_mp(int mana) {
	mp_ = mana;
}

void Entity::add_sp(int stamina) {
	sp_ = stamina;
}

void Entity::add_def(int defense) {
	def_ = defense;
}

void Entity::add_mdef(int resistance) {
	mdef_ = resistance;
}

void Entity::add_mspd(int movement) {
	mspd_ = movement;
}

void Entity::add_aspd(int speed) {
	aspd_ = speed;
}

void Entity::add_range(int range) {
	range_ = range;
}

void Entity::add_s_atk(int attack) {
	s_atk_ = attack;
}
void Entity::add_s_matk(int magic) {
	s_matk_ = magic;
}

void Entity::add_s_hp(int health) {
	s_hp_ = health;
}

void Entity::add_s_mp(int mana) {
	s_mp_ = mana;
}

void Entity::add_s_sp(int stamina) {
	s_sp_ = stamina;
}

void Entity::add_s_def(int defense) {
	s_def_ = defense;
}

void Entity::add_s_mdef(int resistance) {
	s_mdef_ = resistance;
}

void Entity::add_s_mspd(int movement) {
	s_mspd_ = movement;
}

void Entity::add_s_aspd(int speed) {
	s_aspd_ = speed;
}

void Entity::add_s_range(int range) {
	s_range_ = range;
}

void Entity::add_str(int strength) {
	str_ = strength;
}

void Entity::add_int(int intelligence) {
	int_ = intelligence;
}

void Entity::add_dex(int dexterity) {
	dex_ = dexterity;
}

void Entity::add_vit(int vitality) {
	vit_ = vitality;
}

void Entity::add_sta(int stamina) {
	sta_ = stamina;
}

void Entity::add_agi(int agility) {
	agi_ = agility;
}

void Entity::add_luk(int luck) {
	luk_ = luck;
}


const string Entity::name() const {
	return name_;
}

const int Entity::element() const {
	return element_;
}

const int Entity::atk() const {
	return atk_;
}

const int Entity::matk() const {
	return matk_;
}

const int Entity::hp() const {
	return hp_;
}

const int Entity::mp() const {
	return mp_;
}

const int Entity::sp() const {
	return sp_;
}

const int Entity::def() const {
	return def_;
}

const int Entity::mdef() const {
	return mdef_;
}

const int Entity::mspd() const {
	return mspd_;;
}

const int Entity::aspd() const {
	return aspd_;
}

const int Entity::range() const {
	return range_;
}

const int Entity::atk_s() const {
	return s_atk_;
}

const int Entity::matk_s() const {
	return s_matk_;
}

const int Entity::hp_s() const {
	return s_hp_;
}

const int Entity::mp_s() const {
	return s_mp_;
}

const int Entity::def_s() const {
	return s_def_;
}

const int Entity::mdef_s() const {
	return s_mdef_;
}

const int Entity::mspd_s() const {
	return s_mspd_;
}

const int Entity::aspd_s() const {
	return s_aspd_;
}

const int Entity::range_s() const {
	return s_range_;
}

const int Entity::strength() const {
	return str_;
}

const int Entity::intelligence() const {
	return int_;
}

const int Entity::dexterity() const {
	return dex_;
}

const int Entity::vitality() const {
	return vit_;
}

const int Entity::agility() const {
	return agi_;
}

const int Entity::luck() const {
	return luk_;
}






// Use These

const int Entity::attack() const {
	int atk_sum = atk_ + (s_atk_ * (level_ - 1));
	// Melee Calculation
	if(range_ <= MAX_MELEE_RANGE) {
		atk_sum += (int) (str_ + (((double) str_ / 10) + ((double) dex_ / 5)));
	} else {
		// Range Calculation
		atk_sum += (int) (dex_ + (((double) dex_ / 12) + ((double) str_ / 4)));
	}
	return atk_sum;
}

const int Entity::magic() const {
	// Magic Calculation
	return (int) (matk_ + (s_matk_ * (level_ - 1)) + int_ * 3 + (((double) int_ / 18) + ((double)dex_ / 15)));
}

const int Entity::health() const {
	return (int) (hp_ + (s_hp_ * (level_ - 1)) + 20 * (vit_ + (((double) vit_ / 10) + ((double) vit_ / 15) + ((double) sta_ / 25))));
}

const int Entity::mana() const {
	return mp_ + (s_mp_ * (level_ - 1)) + int_ * 30;
}

const int Entity::mana_recovery() const {
	return BASE_MP_RECOVERY + int_ / 6;
}

const int Entity::stamina() const {
	return sta_ * 2 + (s_sp_ * (level_ - 1));
}

const int Entity::stamina_recovery() const {
	return BASE_SP_RECOVERY + sta_ + (sta_ / 8);
}

const int Entity::defense() const {
	return (int) (def_ * (s_def_ * level_) + (vit_ * 1.3));
}

const int Entity::mdefense() const {
	return (int) (mdef_ * (s_def_ * level_) + ((vit_ * 0.8) + (int_ * 1.2)));
}

const int Entity::move_speed() const {
	return mspd_ + (s_mspd_ * level_) + agi_;
}

const int Entity::attack_speed() const {
	return aspd_ + (s_aspd_ * level_) + (agi_ / 4);
}