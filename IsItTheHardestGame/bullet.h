#ifndef BULLET_H
#define BULLET_H

#include "objects.h"

class bullet : public object {
protected:
	float damage = 20.0f;
public:
	using object::object;
	float getDamageValue();
};

#endif