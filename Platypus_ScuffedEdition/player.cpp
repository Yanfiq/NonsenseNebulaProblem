#include "player.h"

std::unordered_map<std::string, player*> player::player_map;
std::unordered_map<std::string, sf::RectangleShape*>* sprites_map_ptr = object::getSpritesMap();

player::player(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) : object(_object_id, _positionX, _positionY, _width, _height, _gravity) {
	positionX = _positionX; positionY = _positionY; width = _width; height = _height; object_id = _object_id; gravity = _gravity;
	object_sprite.setSize(sf::Vector2f(width, height));
	object_sprite.setFillColor(sf::Color(0, 0, 0, 255));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
	player_map[_object_id] = this;
	(*sprites_map_ptr)[_object_id] = &object_sprite;
}

player* player::getObjectPtr(std::string id) {
	return player_map[id];
}

void player::shoot() {
	std::string bullet_id = "bullet_" + std::to_string(bullet_count);
	bullet* Bullet = new bullet(bullet_id, positionX, positionY, 20, 20, 0);
	Bullet->setVelocity(0.5, 0);
	Bullet->setDamageValue(20.0f);
	bullet_count++;
	(*sprites_map_ptr)[bullet_id] = Bullet->getSprite();
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

		if (it.second->getPositionY() >= 720 || it.second->getPositionY() <= 0)
			it.second->setVelocity(it.second->getVelocityX(), it.second->getVelocityY() * -1);

		if (it.second->getPositionY() >= 720)
			it.second->setPosition(it.second->getPositionX(), 720);
		else if (it.second->getPositionY() <= 0)
			it.second->setPosition(it.second->getPositionX(), 0);

		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);
	}
}