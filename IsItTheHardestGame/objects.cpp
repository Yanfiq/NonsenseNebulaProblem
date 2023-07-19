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

void object::update(float time) {
	positionX += velocityX * time;
	positionY += velocityY * time;
	if (velocityY <= maxY)
	{
		velocityY += gravity * time;
	}
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
}

void object::thrust() {
	if (minY <= velocityY) {
		velocityY -= 0.2;
	}
}

void object::setVelocity(float vx, float vy) {
	velocityX = vx;
	velocityY = vy;

}

std::string object::getId() {
	return object_id;
}