#pragma once
#include "objects.h"
#include "bullet.h"

class player : public object {
private:
	int bullet_count = 1;

public:
	using object::object;
	bullet* shoot();
	void resetBulletCount();
	int getBulletCount();
	void thrust();
};