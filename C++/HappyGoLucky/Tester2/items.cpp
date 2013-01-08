#include "items.h"

Item::Item() {
	str_ = 0;
	int_ = 0;
	dex_ = 0;
	vit_ = 0;
	sta_ = 0;
	luk_ = 0;
	agi_ = 0;
	hp_ = 0;
	mp_ = 0;
	sp_ = 0;
	hp_r = 0;
	mp_r = 0;
	sp_r = 0;
	atk_ = 0;
	matk_ = 0;
	mspd_ = 0;
	aspd_ = 0;
	def_ = 0;
	mdef_ = 0;
	crit_ = 0;
	rcrit_ = 0;
}

Item::~Item() {

}

bool & Item::operator==(const Item &operand) const {
	bool *result = false;
	Item temp = *this;
	if(temp.name() == operand.name() && temp.id() == operand.id() && 
		temp.strength() == operand.strength() && temp.intelligence() == operand.intelligence() &&
		temp.dexterity() == operand.dexterity() && temp.vitality() == operand.vitality() &&
		temp.stamina() == operand.stamina() && temp.luck() == operand.luck() &&
		temp.max_health() == operand.max_health() && temp.max_mana() == operand.max_mana() &&
		temp.max_stamina() == operand.max_stamina() && temp.rec_health() == operand.rec_health() &&
		temp.rec_mana() == operand.rec_mana() && temp.rec_stamina() == operand.rec_stamina() &&
		temp.attack() == operand.attack() && temp.magic() == operand.magic() &&
		temp.atk_spd() == operand.atk_spd() && temp.mov_spd() == operand.mov_spd() &&
		temp.defense() == operand.defense() && temp.mdefense() == operand.mdefense() &&
		temp.critical() == operand.critical() && temp.crit_res() == operand.crit_res()
		) *result = true;
	return *result;
}

const unsigned int Item::id() const {
	return id_;
}

const string Item::name() const {
	return name_;
}

const int Item::strength() const {
	return str_;
}

const int Item::intelligence() const {
	return int_;
}

const int Item::dexterity() const {
	return dex_;
}

const int Item::vitality() const {
	return vit_;
}

const int Item::stamina() const {
	return sta_;
}

const int Item::agility() const {
	return agi_;
}

const int Item::luck() const {
	return luk_;
}

const int Item::max_health() const {
	return hp_;
}

const int Item::max_mana() const {
	return mp_;
}

const int Item::max_stamina() const {
	return sp_;
}

const int Item::rec_health() const {
	return hp_r;
}

const int Item::rec_mana() const {
	return mp_r;
}

const int Item::rec_stamina() const {
	return sp_r;
}

const int Item::attack() const {
	return atk_;
}

const int Item::magic() const {
	return matk_;
}

const int Item::atk_spd() const {
	return aspd_;
}

const int Item::mov_spd() const {
	return mspd_;
}

const int Item::defense() const {
	return def_;
}

const int Item::mdefense() const {
	return mdef_;
}

const int Item::critical() const {
	return crit_;
}

const int Item::crit_res() const {
	return rcrit_;
}
