#include "objects.h"

object::object(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) {
	positionX = _positionX; positionY = _positionY; width = _width; height = _height; object_id = _object_id; gravity = _gravity;
	object_sprite.setSize(sf::Vector2f(width, height));
	object_sprite.setFillColor(sf::Color(0, 0, 0, 255));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
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

float object::getVelocityY() {
	return velocityY;
}

float object::getVelocityX() {
	return velocityX;
}

std::string object::getId() {
	return object_id;
}