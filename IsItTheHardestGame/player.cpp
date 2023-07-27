#include "player.h"

int player::bullet_count;

object* player::shoot() {
	std::string bullet_id = "bullet_" + std::to_string(bullet_count);
	object* Object = new object(bullet_id, getPositionX(), getPositionY(), 20, 20, 0);
	Object->setVelocity(0.5, 0);
	bullet_count++;
	return Object;
}

void player::resetBulletCount() {
	bullet_count = 1;
}

int player::getBulletCount() {
	return bullet_count;
}

void player::thrust() {
	setVelocity(getVelocityX(), getVelocityY() - 0.06f);
}