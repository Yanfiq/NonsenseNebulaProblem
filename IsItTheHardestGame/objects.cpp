#include "objects.h"

object::object(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) {
	positionX = _positionX; positionY = _positionY; width = _width; height = _height; object_id = _object_id; gravity = _gravity;
	object_sprite.setSize(sf::Vector2f(width, height));
	object_sprite.setFillColor(sf::Color(0, 0, 0, 255));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
}

sf::RectangleShape* object::getSprite() {
	sf::RectangleShape *sprite;
	sprite = &object_sprite;
	return sprite;
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
		velocityY -= 0.04f;
	}
}

void object::setVelocity(float vx, float vy) {
	velocityX = vx;
	velocityY = vy;
}

float object::getVelocityY(){
	return velocityY;
}

float object::getVelocityX() {
	return velocityX;
}

std::string object::getId() {
	return object_id;
}


//object manager
void manageObject::assign_objectptr(std::string id, object* Object) {
	objects_ptr[id] = Object;
}

void manageObject::delete_object(std::string id) {
	delete objects_ptr[id];
}

void manageObject::show_object(std::string id) {
	object* Object = objects_ptr[id];
	sprites_ptr[id] = Object->getSprite();
}

void manageObject::unshow_object(std::string id) {
	sprites_ptr.erase(id);
}

sf::RectangleShape* manageObject::draw_sprite(std::string id) {
	sf::RectangleShape* sprite = sprites_ptr[id];
	return sprite;
}

object* manageObject::get_objectptr(std::string id) {
	object* Object = objects_ptr[id];
	return Object;
}

void manageObject::assign_bulletptr(std::string id, object* Object) {
	bullets_object_ptr[id] = Object;
}

void manageObject::deassign_bulletptr(std::string id, object* Object) {
	bullets_object_ptr.erase(id);
}

bool manageObject::isintersect(std::string id_1, std::string id_2) {
	return sprites_ptr[id_1]->getGlobalBounds().intersects(sprites_ptr[id_2]->getGlobalBounds());
}

std::unordered_map<std::string, sf::RectangleShape*> manageObject::getSpritesMap() {
	return sprites_ptr;
}