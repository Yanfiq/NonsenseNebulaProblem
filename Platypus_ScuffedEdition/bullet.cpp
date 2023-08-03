#include "bullet.h"

std::unordered_map<std::string, bullet*> bullet::bullet_map;
//std::unordered_map<std::string, sf::RectangleShape*> object::sprites_map;
std::unordered_map<std::string, sf::RectangleShape*>* sprites_map_ptr_2 = object::getSpritesMap();

bullet::bullet(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) : object(_object_id, _positionX, _positionY, _width, _height, _gravity) {
	positionX = _positionX; positionY = _positionY; width = _width; height = _height; object_id = _object_id; gravity = _gravity;
	object_sprite.setSize(sf::Vector2f(width, height));
	object_sprite.setFillColor(sf::Color(0, 0, 0, 255));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
	bullet_map[_object_id] = this;
	(*sprites_map_ptr_2)[_object_id] = &object_sprite;
}

bullet* bullet::getObjectPtr(std::string id) {
	return bullet_map[id];
}

float bullet::getDamageValue() const {
	return this->damage;
}

void bullet::setDamageValue(float _damage) {
	this->damage = _damage;
}

std::unordered_map<std::string, bullet*>* bullet::getBulletMap() {
	return &bullet_map;
}

void bullet::deleteObject(std::string id) {
	sprites_map.erase(id);
	delete bullet_map[id];
}

void bullet::clearObject() {
	for (auto it = bullet_map.begin(); it != bullet_map.end();) {
		//deleteObject(it->first);
		sprites_map.erase(it->first);
		delete it->second;
		it++;
	}
}