#include "objects.h"

object::object(float _positionX, float _positionY, float _velocityX, float _velocityY, float _gravity) {
	positionX = _positionX; 
	positionY = _positionY; 
	velocityX = _velocityX;
	velocityY = _velocityY;
	gravity = _gravity;
}

sf::RectangleShape* object::getSprite() {
	sf::RectangleShape* sprite;
	sprite = &object_sprite;
	return sprite;
}

void object::setVelocity(float vx, float vy) {
	velocityX = vx;
	velocityY = vy;
}

void object::setPosition(float px, float py) {
	positionX = px;
	positionY = py;
}

float object::getPositionX() {
	return positionX;
}
float object::getPositionY() {
	return positionY;
}

float object::getVelocityX() {
	return velocityX;
}

float object::getVelocityY() {
	return velocityY;
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

bool object::isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2) {
	return shape_1->getGlobalBounds().intersects(shape_2->getGlobalBounds());
}