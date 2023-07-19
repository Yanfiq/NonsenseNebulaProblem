#include "objects.h"

sf::RectangleShape object::getSprite() {
	return object_sprite;
}

void object::reduceHP(float damage) {
	HP -= damage;
}
float object::getPositionX() {
	return positionX;
}
float object::getPositionY() {
	return positionY;
}

void object::Update(float time) {
	positionX += velocityX;
	if (minY < velocityY < maxY)
	{
		positionY += velocityY * time;
		velocityY += gravity * time;
	}
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
}

void object::thrust() {
	velocityY = velocityY - 0.2;
}

std::string object::getId() {
	return object_id;
}