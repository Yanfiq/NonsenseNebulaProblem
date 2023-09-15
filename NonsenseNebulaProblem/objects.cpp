#include "objects.h"

object::object(float _positionX, float _positionY, float _velocityX, float _velocityY) {
	object_sprite.setPosition(sf::Vector2f(_positionX, _positionY));
	velocityX = _velocityX;
	velocityY = _velocityY;
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
	object_sprite.setPosition(sf::Vector2f(px, py));
}

sf::Vector2f object::getPosition() {
	return object_sprite.getPosition();
}

sf::Vector2f object::getVelocity() {
	return sf::Vector2f(velocityX, velocityY);
}

sf::Vector2f object::getSize() {
	return sf::Vector2f(object_sprite.getSize().x, object_sprite.getSize().y);
}

void object::update(float time) {
	object_sprite.move(sf::Vector2f(velocityX * time, velocityY * time));
}

bool object::isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2) {
	return shape_1->getGlobalBounds().intersects(shape_2->getGlobalBounds());
}