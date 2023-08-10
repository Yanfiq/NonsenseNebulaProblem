#include "bullet.h"

std::unordered_map<int, bullet*> bullet::bullet_map;

bullet::bullet(int _object_id, std::string textureDir, float _positionX, float _positionY, float _velocityX, float _velocityY, float _gravity) : object(textureDir, _positionX, _positionY, _velocityX, _velocityY, _gravity) {
	if (velocityX > 0.0f) {
		bullet_map[playerBullet_obj + _object_id] = this;
	}
	else if (velocityX < 0.0f) {
		bullet_map[enemyBullet_obj + _object_id] = this;
	}
}

bullet* bullet::getObjectPtr(int id) {
	if (bullet_map.find(id) != bullet_map.end())
		return bullet_map[id];
	else
		return NULL;
}

float bullet::getDamageValue() const {
	return this->damage;
}

void bullet::setDamageValue(float _damage) {
	this->damage = _damage;
}

std::unordered_map<int, bullet*>* bullet::getBulletMap() {
	return &bullet_map;
}

void bullet::deleteObject(int id) {
	delete bullet_map[id];
	bullet_map.erase(id);
}

void bullet::clearObject() {
	for (auto it = bullet_map.begin(); it != bullet_map.end();) {
		delete it->second;
		it = bullet_map.erase(it);
	}
}

void bullet::updateNDrawAllObject(double dt, sf::RenderWindow& window) {
	for (const auto& it : bullet_map) {
		it.second->update(dt);
		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);
	}
}