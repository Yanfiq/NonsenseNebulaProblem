#include "enemy.h"

std::unordered_map<std::string, enemy*> enemy::enemy_map;
std::unordered_map<std::string, sf::RectangleShape*>* sprites_map_ptr_3 = object::getSpritesMap();
int enemy::bullet_count = 0;

enemy::enemy(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) : object(_object_id, _positionX, _positionY, _width, _height, _gravity) {
	positionX = _positionX; positionY = _positionY; width = _width; height = _height; object_id = _object_id; gravity = _gravity;
	object_sprite.setSize(sf::Vector2f(width, height));
	object_sprite.setFillColor(sf::Color(0, 0, 0, 255));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
	enemy_map[_object_id] = this;
	(*sprites_map_ptr_3)[_object_id] = &object_sprite;
}

std::unordered_map<std::string, enemy*>* enemy::getEnemyMap() {
	return &enemy_map;
}

enemy* enemy::getObjectPtr(std::string id) {
	return enemy_map[id];
}

void enemy::deleteObject(std::string id) {
	sprites_map.erase(id);
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
	std::string bullet_id = "bullet_enemy_" + std::to_string(bullet_count++);
	bullet* Bullet = new bullet(bullet_id, positionX, positionY, 20, 20, 0);
	Bullet->setVelocity(-0.5, 0);
	Bullet->setDamageValue(20.0f);
	(*sprites_map_ptr_3)[bullet_id] = Bullet->getSprite();
}

void enemy::clearObject() {
	for (auto it = enemy_map.begin(); it != enemy_map.end();) {
		sprites_map.erase(it->first);
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