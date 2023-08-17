#include "bullet.h"

std::unordered_map<int, bullet*> bullet::bullet_map;

bullet::bullet(int _object_id, sf::Texture* texture, float _positionX, float _positionY, float _velocityX, float _velocityY) : object(_positionX, _positionY, _velocityX, _velocityY) {
	object_sprite.setTexture(texture);
	object_sprite.setSize(sf::Vector2f(texture->getSize()));
	object_sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
	
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
	for (auto it = bullet_map.begin(); it != bullet_map.end();) {
		it->second->update(dt);
		sf::RectangleShape* sprite = it->second->getSprite();
		window.draw(*sprite);

		if (it->second->getPositionX() < 0 || it->second->getPositionX() > window.getSize().x){
			delete it->second;
			it = bullet_map.erase(it);
		}
		else {
			it++;
		}
	}
}