#include "enemy.h"

std::unordered_map<int, enemy*> enemy::enemy_map;
int enemy::bullet_count = 1;

enemy::enemy(int _object_id, float _positionX, float _positionY, float _velocityX, float _velocityY, float _width, float _height, float _gravity) : object(_positionX, _positionY, _velocityX, _velocityY, _width, _height, _gravity) {
	positionX = _positionX; 
	positionY = _positionY; 
	velocityX = _velocityX;
	velocityY = _velocityY;
	width = _width; 
	height = _height;
	gravity = _gravity;
	object_sprite.setSize(sf::Vector2f(width, height));
	object_sprite.setFillColor(sf::Color(0, 0, 0, 255));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
	enemy_map[enemy_obj + _object_id] = this;
}

std::unordered_map<int, enemy*>* enemy::getEnemyMap() {
	return &enemy_map;
}

enemy* enemy::getObjectPtr(int id) {
	return enemy_map[id];
}

void enemy::deleteObject(int id) {
	delete enemy_map[id];
	enemy_map.erase(id);
}

void enemy::reduceHp(float damage) {
	hp -= damage;
}

float enemy::getHp() {
	return hp;
}

void enemy::shoot() {
	bullet* Bullet = new bullet(bullet_count++, positionX, positionY, -0.5f, 0.0f, 20, 20, 0);
	Bullet->setDamageValue(20.0f);
	if (bullet_count == 99)
		bullet_count = 0;
}

void enemy::clearObject() {
	for (auto it = enemy_map.begin(); it != enemy_map.end();) {
		delete it->second;
		it = enemy_map.erase(it);
	}
}

void enemy::updateNDrawAllObject(double dt, sf::RenderWindow& window) {
	for (const auto& it : enemy_map) {
		it.second->update(dt);

		if (it.second->getPositionY() >= 720 || it.second->getPositionY() <= 0) {
			it.second->setVelocity(it.second->getVelocityX(), it.second->getVelocityY() * -1);
			if (it.second->getPositionY() >= 720)
				it.second->setPosition(it.second->getPositionX(), 720);
			else if (it.second->getPositionY() <= 0)
				it.second->setPosition(it.second->getPositionX(), 0);
		}
		if (it.second->getPositionX() >= 1280 || it.second->getPositionX() <= 400) {
			it.second->setVelocity(it.second->getVelocityX() * -1, it.second->getVelocityY());
			if (it.second->getPositionX() <= 400)
				it.second->setPosition(400, it.second->getPositionY());
			else if (it.second->getPositionX() >= 1280)
				it.second->setPosition(1280, it.second->getPositionY());
		}
		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);
	}
}