#ifndef PLAYER_H
#define PLAYER_H

#include "objects.h"

class player : public object {
private:
	static int bullet_count;

public:
	using object::object;
	object* shoot();
	void resetBulletCount();
	int getBulletCount();
	void thrust();
};

#endif