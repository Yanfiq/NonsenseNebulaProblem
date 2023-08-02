#pragma once
#include "objects.h"

class enemy : public object {
protected:
	float hp = 100.0f;

public:
	using object::object;
	void reduceHp(float damage);
	float getHp();
};