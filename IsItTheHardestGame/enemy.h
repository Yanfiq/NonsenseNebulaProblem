#pragma once
#include "objects.h"
#include "bullet.h"

class enemy : public object {
protected:
	float hp = 100.0f;

public:
	using object::object;
	void reduceHp(float damage);
	bullet* shoot();
	float getHp();
};