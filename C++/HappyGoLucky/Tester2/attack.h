#ifndef _H_ATTACK
#define _H_ATTACK

#include "dependencies.h"
#include "entity.h"

class Attack {
public:
	Attack();
	Attack(int modifier, int base);
	~Attack();

	int damage(Entity source, Entity direction);
private:
	int modifier_;
	int base_;
};

#endif