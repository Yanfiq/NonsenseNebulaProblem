#include "objectsContainer.h"

std::unordered_map<std::string, player*> objectsContainer::player_object_ptr;
std::unordered_map<std::string, bullet*> objectsContainer::bullets_object_ptr;
std::unordered_map<std::string, anotherObject*> objectsContainer::another_object_ptr;

std::unordered_map<std::string, sf::RectangleShape*> objectsContainer::sprites_ptr;
//template <>
// 
//bullet* objectsContainer::get_objectptr<bullet>(const std::string& id) {
//	// Implementation to retrieve Bullet objects from the unordered_map
//	return bullets_object_ptr[id];
//}
//
//template <>
//player* objectsContainer::get_objectptr<player>(const std::string& id) {
//	// Implementation to retrieve Player objects from the unordered_map
//	return player_object_ptr[id];
//}
//
//template <>
//anotherObject* objectsContainer::get_objectptr<anotherObject>(const std::string& id) {
//	// Implementation to retrieve InanimateObject objects from the unordered_map
//	return another_object_ptr[id];
//}

//template <typename T>
//T* get_objectptr(const std::string& id) {
//	if (id.substr(0, 6) == "bullet") {
//		return static_cast<T*>(bullets_object_ptr[id]);
//	}
//	else if (id.substr(0, 6) == "player") {
//		return static_cast<T*>(player_object_ptr[id]);
//	}
//	else {
//		return static_cast<T*>(another_object_ptr[id]);
//	}
//}

player* objectsContainer::get_object_player(std::string id) {
	return player_object_ptr[id];
}

bullet* objectsContainer::get_object_bullet(std::string id) {
	return bullets_object_ptr[id];
}

anotherObject* objectsContainer::get_another_object(std::string id) {
	return another_object_ptr[id];
}

void objectsContainer::createObject(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) {
	if (_object_id.substr(0, 6) == "bullet") {
		bullet* Object = new bullet(_object_id, _positionX, _positionY, _width, _height, _gravity);
		bullets_object_ptr[_object_id] = Object;
	}
	else if(_object_id.substr(0, 6) == "player") {
		player* Object = new player(_object_id, _positionX, _positionY, _width, _height, _gravity);
		player_object_ptr[_object_id] = Object;
	}
	else {
		anotherObject* Object = new anotherObject(_object_id, _positionX, _positionY, _width, _height, _gravity);
		another_object_ptr[_object_id] = Object;
	}
}

void objectsContainer::assign_object(std::string id, object* Object) {
	if (id.substr(0, 6) == "bullet") {
		bullet* Bullet = static_cast<bullet*>(Object);
		bullets_object_ptr[Bullet->getId()] = Bullet;
	}
	else if (id.substr(0, 6) == "player") {
		player* Player = static_cast<player*>(Object);
		player_object_ptr[Player->getId()] = Player;
	}
	else {
		anotherObject* anotherobject = static_cast<anotherObject*>(Object);
		another_object_ptr[anotherobject->getId()] = anotherobject;
	}
}

void objectsContainer::delete_object(std::string id) {
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

void objectsContainer::show_object(std::string id) {
	if (id.substr(0, 6) == "bullet") {
		bullet* Object = bullets_object_ptr[id];
		sprites_ptr[id] = Object->getSprite();
	}
	else if(id.substr(0, 6) == "player") {
		player* Object = player_object_ptr[id];
		sprites_ptr[id] = Object->getSprite();
	}
	else {
		anotherObject* Object = another_object_ptr[id];
		sprites_ptr[id] = Object->getSprite();
	}
}

void objectsContainer::unshow_object(std::string id) {
	sprites_ptr.erase(id);
}

sf::RectangleShape* objectsContainer::draw_sprite(std::string id) {
	sf::RectangleShape* sprite = sprites_ptr[id];
	return sprite;
}

std::unordered_map<std::string, sf::RectangleShape*> objectsContainer::getSpritesMap() {
	return sprites_ptr;
}

bool objectsContainer::isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2) {
	return shape_1->getGlobalBounds().intersects(shape_2->getGlobalBounds());
}