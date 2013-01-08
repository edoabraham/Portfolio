// Stat
#include <iostream>
#include "Stats2.h"
#include <stdio.h>
#include <math.h>

using namespace std;
int Str, Int, Dex, Vit, Base_Level, StrDex, DexInt, IntVit;

unsigned int RawMaxAtk () {
	 return int(Str + floor(Str/5.0) + floor(Dex/10.0)); }
unsigned int RawMinAtk () {
	double raw_min_atk = (floor(Str/2.0) + Dex);
	if(raw_min_atk <= RawMaxAtk()) { return int(raw_min_atk); } else {
		return RawMaxAtk(); } }

unsigned int Weight_Limit () {
	return Str * 10 + Base_Level * 15 + BASE_WEIGHT; }
unsigned int RawRangeMaxAtk () {
	return Dex + int(floor(Str/8.0)); }
unsigned int RawRangeMinAtk () {
	double range_min_dmg = ((sqrt(8.0 * Dex / DEX_LIMIT + 1.0) - 1.0)/2.0) * DEX_LIMIT;
	return int(floor(range_min_dmg / DEX_LIMIT * Dex)); }

double MovementSpeedModifier () {
	double init_move_speed = ((sqrt(8.0 * Dex / MOVE_SPEED_SCALE + 1.0) - 1.0)/2.0) * MOVE_SPEED_SCALE;
	if (init_move_speed <= MOVE_SPEED_CAP) {
		return (100 + init_move_speed) / 100; } else {
		return (100 + MOVE_SPEED_CAP) / 100; } }

double AttackSpeedModifier () {
	if (Dex <= Str) StrDex = Dex; else StrDex = Str;
	double init_attack_speed = ((sqrt(8.0 * StrDex / ATTACK_SPEED_SCALE + 1.0) - 1.0)/2.0) * ATTACK_SPEED_SCALE;
	if (init_attack_speed <= ATTACK_SPEED_CAP) {
		return (100 + init_attack_speed) / 100; } else {
		return (100 + ATTACK_SPEED_CAP) / 100; } }

unsigned int MaxMagicAttack () {
	return int(floor(((sqrt(8.0 * Int / MAGIC_ATTACK_SCALE + 1.0) - 1.0) / 2.0) * MAGIC_ATTACK_SCALE)); }
unsigned int MinMagicAttack () { return Int + int(floor(Int / 5.0)); }

double cast_timer_val (int input, int scaler) { return ((sqrt(8.0 * input / scaler + 1.0)/2.0) * scaler); }
double CastingTimeMod () { 
	if ((Dex-10) <= Int) DexInt = Dex - 10; else DexInt = Int;
	if (DexInt > 100) DexInt = CAST_STAT_MAX;
	return 1.0 - ((100 - cast_timer_val(CAST_STAT_MAX,CAST_SCALE)) + cast_timer_val(DexInt,CAST_SCALE))/100; }
double CoolDownRedMod () {
	if ((Int-20) <= Dex) DexInt = Int - 20; else DexInt = Dex;
	if (DexInt > 100) DexInt = CAST_STAT_MAX;
	return 1.0 - ((100 - cast_timer_val(CAST_STAT_MAX,CAST_SCALE)) + cast_timer_val(DexInt,CAST_SCALE))/100; }

double CastingTime () { return SKILL_BASE_CAST_TIME + SKILL_REDUC_CAST_TIME * CastingTimeMod(); }
double CoolDownTime () { return SKILL_BASE_CAST_TIME + SKILL_REDUC_CD_TIME * CoolDownRedMod(); }

unsigned int MaxMP () { return int(MP_BASE_AMOUNT + MP_LEVEL_BONUS * (Base_Level/180) + Int * 30 + floor(Int/5.0) * 15 + floor(Vit/5.0) * 120); }
unsigned int MPRegenAmount () { return MP_REGEN_BASE_AMOUNT + Int * 6; } // Runs and Refresh every 4.0 seconds
unsigned int MPRandRegenAmount () {int(floor(Int/6.0) * 30);} // Runs and Refresh every rand(2.0,10.0) seconds

unsigned int MaxHP () { return int(HP_BASE_AMOUNT + HP_LEVEL_BONUS * (Base_Level/180) + Vit * 70 + floor(Vit/7.0) * 160); }
unsigned int HPRegenAmount () { return int(Vit * 5 + floor(Vit/5.0) * 2);} // Runs and Refreshes every 5.0 seconds

unsigned int physicalDefense () { return int(Vit + floor(Vit/8.0)); }
unsigned int PhysicalDefense () { return int(floor(Vit/25.0)); }

unsigned int magicDefense () { return int(Int + floor(Int/6.0) + floor(Vit/4.0)); }
unsigned int MagicDefense () { return int(floor(Int/25.0)); } 
