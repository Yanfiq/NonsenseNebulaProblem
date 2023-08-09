#include "bullet.h"

std::unordered_map<int, bullet*> bullet::bullet_map;

bullet::bullet(int _object_id, float _positionX, float _positionY, float _velocityX, float _velocityY, float _width, float _height, float _gravity) : object(_positionX, _positionY, _velocityX, _velocityY, _width, _height, _gravity) {
	positionX = _positionX;
	positionY = _positionY;
	velocityX = _velocityX;
	velocityY = _velocityY;
	width = _width;
	height = _height;
	gravity = _gravity;
	object_sprite.setSize(sf::Vector2f(width, height));
	object_sprite.setFillColor(sf::Color::Black);
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
	if (velocityX > 0.0f) {
		bullet_map[playerBullet_obj + _object_id] = this;
	}
	else if (velocityX < 0.0f) {
		bullet_map[enemyBullet_obj + _object_id] = this;
	}
}

bullet* bullet::getObjectPtr(int id) {
	return bullet_map[id];
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