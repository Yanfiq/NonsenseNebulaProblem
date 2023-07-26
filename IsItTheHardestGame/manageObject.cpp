#include "manageObject.h"


//template <>
//bullet* manageObject::get_objectptr<bullet>(std::string id) {
//	// Implementation to retrieve Bullet objects from the unordered_map
//	return bullets_object_ptr[id];
//}
//
//template <>
//player* manageObject::get_objectptr<player>(std::string id) {
//	// Implementation to retrieve Player objects from the unordered_map
//	return player_object_ptr[id];
//}
//
//template <>
//inanimateObject* manageObject::get_objectptr<inanimateObject>(std::string id) {
//	// Implementation to retrieve InanimateObject objects from the unordered_map
//	return another_object_ptr[id];
//}

std::unordered_map<std::string, player*> manageObject::player_object_ptr;
std::unordered_map<std::string, bullet*> manageObject::bullets_object_ptr;
std::unordered_map<std::string, sf::RectangleShape*> manageObject::sprites_ptr;
std::unordered_map<std::string, inanimateObject*> another_object_ptr;

template <typename T>
T* get_objectptr(std::string id) {
	if (id.substr(0, 6) == "bullet") {
		return static_cast<T*>(bullets_object_ptr[id]);
	}
	else if (id.substr(0, 6) == "player") {
		return static_cast<T*>(player_object_ptr[id]);
	}
	else {
		return static_cast<T*>(another_object_ptr[id]);
	}
}

void manageObject::createObject(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) {
	if (_object_id.substr(0, 6) == "bullet") {
		bullet* Object = new bullet(_object_id, _positionX, _positionY, _width, _height, _gravity);
		bullets_object_ptr[_object_id] = Object;
	}
	else if(_object_id.substr(0, 6) == "player") {
		player* Object = new player(_object_id, _positionX, _positionY, _width, _height, _gravity);
		player_object_ptr[_object_id] = Object;
	}
	else {
		inanimateObject* Object = new inanimateObject(_object_id, _positionX, _positionY, _width, _height, _gravity);
		another_object_ptr[_object_id] = Object;
	}
}

void manageObject::delete_object(std::string id) {
	if (id.substr(0, 6) == "bullet") {
		delete bullets_object_ptr[id];
	}
	else if(id.substr(0, 6) == "player") {
		delete player_object_ptr[id];
	}
	else {
		delete another_object_ptr[id];
	}
}

void manageObject::show_object(std::string id) {
	if (id.substr(0, 6) == "bullet") {
		bullet* Object = bullets_object_ptr[id];
		sprites_ptr[id] = Object->getSprite();
	}
	else if(id.substr(0, 6) == "player") {
		player* Object = player_object_ptr[id];
		sprites_ptr[id] = Object->getSprite();
	}
	else {
		inanimateObject* Object = another_object_ptr[id];
		sprites_ptr[id] = Object->getSprite();
	}
}

void manageObject::unshow_object(std::string id) {
	sprites_ptr.erase(id);
}

sf::RectangleShape* manageObject::draw_sprite(std::string id) {
	sf::RectangleShape* sprite = sprites_ptr[id];
	return sprite;
}

std::unordered_map<std::string, sf::RectangleShape*> manageObject::getSpritesMap() {
	return sprites_ptr;
}

bool manageObject::isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2) {
	return shape_1->getGlobalBounds().intersects(shape_2->getGlobalBounds());
}