#pragma once
#include "objects.h"

#ifndef ENEMY_H
#define ENEMY_H

class enemy : public object {
protected:
	float hp = 100.0f;

public:
	using object::object;
	void reduceHp(float damage);
	float getHp();
};

#endif // !ENEMY_H
