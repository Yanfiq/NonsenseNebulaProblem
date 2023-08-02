#include "enemy.h"

void enemy::reduceHp(float damage) {
	hp -= damage;
}

float enemy::getHp() {
	return hp;
}

bullet* enemy::shoot() {
	static int bullet_count;
	std::string bullet_id = "bullet_enemy_" + std::to_string(bullet_count);
	bullet* Bullet = new bullet(bullet_id, positionX, positionY, 20, 20, 0);
	Bullet->setVelocity(-0.5, 0);
	Bullet->setDamageValue(20.0f);
	bullet_count++;
	return Bullet;
}