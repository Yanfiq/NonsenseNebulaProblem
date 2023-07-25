#include "object_manager.h"

std::unordered_map<std::string, object*> manageObject::objects_ptr;
std::unordered_map<std::string, object*> manageObject::bullets_object_ptr;
std::unordered_map<std::string, sf::RectangleShape*> manageObject::sprites_ptr;

void manageObject::createObject(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) {
	object* Object = new object(_object_id, _positionX, _positionY, _width, _height, _gravity);
	objects_ptr[_object_id] = Object;
}

void manageObject::createObject_bullet(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) {
	object* Object = new object(_object_id, _positionX, _positionY, _width, _height, _gravity);
	bullets_object_ptr[_object_id] = Object;
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

std::unordered_map<std::string, sf::RectangleShape*> manageObject::getSpritesMap() {
	return sprites_ptr;
}

bool manageObject::isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2) {
	return shape_1->getGlobalBounds().intersects(shape_2->getGlobalBounds());
}