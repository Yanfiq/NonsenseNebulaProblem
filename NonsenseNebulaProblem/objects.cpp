#include "objects.h"

object::object(float _positionX, float _positionY, float _velocityX, float _velocityY) {
	object_sprite.setPosition(sf::Vector2f(_positionX, _positionY));
	velocityX = _velocityX;
	velocityY = _velocityY;
	before_state = sf::FloatRect(0, 0, 0, 0);
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

int object::getObjectType(int id) {
	if (player_obj < id && id < playerBullet_obj) {
		return 1; //player
	}
	if (playerBullet_obj < id && id < enemy_obj) {
		return 2; //player's bullet
	}
	if (enemy_obj < id && id < enemyBullet_obj) {
		return 3; //enemy
	}
	if (enemyBullet_obj < id) {
		return 4; //enemy's bullet
	}
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