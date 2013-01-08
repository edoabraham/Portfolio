//
// Orion
// Status Related Variables
// ------------------------------------
//
#include <math.h>
#include <iostream>

using namespace std;

#define MAX_STATS 180
#define DEX_LIMIT 200 // Limiting Scale Value on Max Range Attack function
#define BASE_WEIGHT 100
#define MOVE_SPEED_CAP 40
#define MOVE_SPEED_SCALE 10 // Dex at 100
#define ATTACK_SPEED_CAP 32
#define ATTACK_SPEED_SCALE 8 // Dex at 80
#define MAGIC_ATTACK_SCALE 500
#define HP_BASE_AMOUNT 100
#define HP_LEVEL_BONUS 5000
#define MP_BASE_AMOUNT 100
#define MP_LEVEL_BONUS 2000
#define MP_REGEN_BASE_AMOUNT 20
#define CAST_SCALE 180
#define CAST_STAT_MAX 100
#define SKILL_BASE_CAST_TIME 1.0 // Temporary value for future individual skill values (using same variable)
#define SKILL_REDUC_CAST_TIME 2.0 // Temporary value for future individual skill values (using same variable)
#define SKILL_REDUC_CD_TIME 3.5 // Temp

/* 
// Diminishing Returns Calculator
float diminishing_returns (float val, float scale) {
	if(val < 0)
		return -diminishing_returns(-val,scale);
	float mult = val / scale;
	float trinum = (sqrt(8.0 * mult + 1.0) - 1.0)/2;
	return trinum * scale;
}
*/
// Caps
// if(int atk_speed >= 1.40) int AttackSpeed = 1.40;
