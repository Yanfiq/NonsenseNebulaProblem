#include "object.h"

object::object(std::string _object_id, float _positionX, float _positionY, float _width, float _height) {
	positionX = _positionX; positionY = _positionY; width = _width; height = _height; object_id = _object_id;
	object_sprite.setSize(sf::Vector2f(width, height));
}
sf::RectangleShape object::draw_object() {
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
	positionX += velocityX * time;
	if (minY < velocityY < maxY)
	{
		positionY += velocityY * time;
		velocityY += gravity * time;
	}
}