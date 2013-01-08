#include "attack.h"

Attack::Attack() {
	modifier_ = 0;
	base_ = 0;
}

Attack::Attack(int modifier, int base) {
	modifier_ = modifier;
	base_ = base;
}

Attack::~Attack() {

}

// Damage Formula
int Attack::damage(Entity source, Entity direction) {
	return 5; // Placeholder
}