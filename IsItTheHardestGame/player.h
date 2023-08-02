#pragma once
#include "objects.h"
#include "bullet.h"

class player : public object {
private:
	int bullet_count = 1;
	float hp = 100;

public:
	using object::object;
	bullet* shoot();
	void resetBulletCount();
	int getBulletCount();
	void thrust();
	float getPlayerHp() const;
	void setPlayerHp(float _hp);
	void reducePlayerHp(float damage);
};