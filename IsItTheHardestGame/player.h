#ifndef PLAYER_H
#define PLAYER_H

#include "objects.h"

class player : public object {
private:
	int bullet_count = 1;

public:
	using object::object;
	object* shoot();
	void resetBulletCount();
	int getBulletCount();
	void thrust();
};

#endif