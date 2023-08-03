#include "objects.h"

std::unordered_map<std::string, sf::RectangleShape*> object::sprites_map;

object::object(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) {
	positionX = _positionX; positionY = _positionY; width = _width; height = _height; object_id = _object_id; gravity = _gravity;
	object_sprite.setSize(sf::Vector2f(width, height));
	object_sprite.setFillColor(sf::Color(0, 0, 0, 255));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
}

std::unordered_map<std::string, sf::RectangleShape*>* object::getSpritesMap() {
	return &sprites_map;
}

sf::RectangleShape* object::getSprite() {
	sf::RectangleShape* sprite;
	sprite = &object_sprite;
	return sprite;
}

float object::getPositionX() {
	return positionX;
}
float object::getPositionY() {
	return positionY;
}

void object::update(double time) {
	positionX += velocityX * time;
	positionY += velocityY * time;
	if (velocityY <= maxY)
	{
		velocityY += gravity * time;
	}
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
}

void object::setVelocity(float vx, float vy) {
	velocityX = vx;
	velocityY = vy;
}

void object::setPosition(float px, float py) {
	positionX = px;
	positionY = py;
}

float object::getVelocityY() {
	return velocityY;
}

float object::getVelocityX() {
	return velocityX;
}

std::string object::getId() {
	return object_id;
}

bool object::isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2) {
	return shape_1->getGlobalBounds().intersects(shape_2->getGlobalBounds());
}

void object::hideObject(std::string id) {
	sprites_map.erase(id);
}

void object::unhideObject(std::string id, sf::RectangleShape* sprite) {
	sprites_map[id] = sprite;
}