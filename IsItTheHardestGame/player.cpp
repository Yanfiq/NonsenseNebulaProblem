#include "player.h"

//void player::shoot() {
//	std::string bullet_id = "bullet_" + std::to_string(bullet_count);
//	manageObject::createObject(bullet_id, getPositionX(), getPositionY(), 20, 20, 0);
//	manageObject::get_objectptr<bullet>(bullet_id)->setVelocity(0.5, 0);
//	manageObject::show_object(bullet_id);
//}

void player::resetBulletCount() {
	bullet_count = 1;
}

int player::getBulletCount() {
	return bullet_count;
}

void player::thrust() {
	setVelocity(getVelocityX(), getVelocityY() - 0.06f);
}