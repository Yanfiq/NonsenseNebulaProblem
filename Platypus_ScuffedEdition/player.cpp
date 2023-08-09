#include "player.h"

std::unordered_map<int, player*> player::player_map;
int player::bullet_count = 1;


player::player(float _positionX, float _positionY, float _velocityX, float _velocityY, float _width, float _height, float _gravity) : object(_positionX, _positionY, _velocityX, _velocityY, _width, _height, _gravity) {
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
	static int num = 1;
	player_map[player_obj + num++] = this;
	if (num == 3)
		num = 1;
}

player* player::getObjectPtr(int id) {
	if (player_map.find(id) != player_map.end())
		return player_map[id];
	else
		return NULL;
}

void player::shoot() {
	bullet* Bullet = new bullet(bullet_count++, positionX, positionY, 0.5, 0, 20, 20, 0);
	Bullet->setDamageValue(20.0f);
}

void player::resetBulletCount() {
	bullet_count = 1;
}

int player::getBulletCount() {
	return bullet_count;
}

void player::thrust() {
	setVelocity(getVelocityX(), getVelocityY() - 0.03f);
}

float player::getPlayerHp() const {
	return this->hp;
}

void player::setPlayerHp(float _hp) {
	this->hp = _hp;
}

void player::reducePlayerHp(float damage) {
	this->hp -= damage;
}

std::unordered_map<int, player*>* player::getPlayerMap() {
	return &player_map;
}

void player::deleteObject(int id) {
	delete player_map[id];
	player_map.erase(id);
}

void player::clearObject() {
	for (auto it = player_map.begin(); it != player_map.end();) {
		delete it->second;
		it = player_map.erase(it);
	}
}

void player::updateNDrawAllObject(double dt, sf::RenderWindow& window) {
	for (const auto& it : player_map) {
		it.second->update(dt);

		if (it.second->getPositionY() >= 720) {
			it.second->setPosition(it.second->getPositionX(), 720);
			it.second->setVelocity(it.second->getVelocityX(), it.second->getVelocityY() * -1 + 0.05);
		}
		else if (it.second->getPositionY() <= 0) {
			it.second->setPosition(it.second->getPositionX(), 0);
			it.second->setVelocity(it.second->getVelocityX(), it.second->getVelocityY() * -1 - 0.05);
		}

		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);
	}
}