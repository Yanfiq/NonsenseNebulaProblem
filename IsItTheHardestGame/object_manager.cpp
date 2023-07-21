#include "object_manager.h"

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

bool manageObject::isintersect(std::string id_1, std::string id_2) {
	return sprites_ptr[id_1]->getGlobalBounds().intersects(sprites_ptr[id_2]->getGlobalBounds());
}

std::unordered_map<std::string, sf::RectangleShape*> manageObject::getSpritesMap() {
	return sprites_ptr;
}