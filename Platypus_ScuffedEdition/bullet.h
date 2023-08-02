#pragma once
#include "objects.h"

class bullet : public object {
protected:
	float damage = 20.0f;
public:
	using object::object;
	float getDamageValue() const;
	void setDamageValue(float _damage);
};