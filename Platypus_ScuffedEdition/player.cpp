#include "player.h"

std::unordered_map<int, player*> player::player_map;

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
	player_map[player_obj + 1] = this;
}

player* player::getObjectPtr(int id) {
	return player_map[id];
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