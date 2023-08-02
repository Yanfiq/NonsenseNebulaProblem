#include "player.h"

bullet* player::shoot() {
	std::string bullet_id = "bullet_" + std::to_string(bullet_count);
	bullet* Bullet = new bullet(bullet_id, positionX, positionY, 20, 20, 0);
	Bullet->setVelocity(0.5, 0);
	Bullet->setDamageValue(20.0f);
	bullet_count++;
	return Bullet;
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