#include "bullet.h"

float bullet::getDamageValue() const {
	return this->damage;
}

void bullet::setDamageValue(float _damage) {
	this->damage = _damage;
}