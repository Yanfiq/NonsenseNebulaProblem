#include "objectsContainer.h"

std::unordered_map<std::string, player*> objectsContainer::player_object_ptr;
std::unordered_map<std::string, bullet*> objectsContainer::bullet_object_ptr;
std::unordered_map<std::string, enemy*>  objectsContainer::enemy_object_ptr;
std::unordered_map<std::string, anotherObject*> objectsContainer::another_object_ptr;

std::unordered_map<std::string, sf::RectangleShape*> objectsContainer::sprites_ptr;

player* objectsContainer::get_object_player(std::string id) {
	return player_object_ptr[id];
}

bullet* objectsContainer::get_object_bullet(std::string id) {
	return bullet_object_ptr[id];
}

enemy* objectsContainer::get_object_enemy(std::string id) {
	return enemy_object_ptr[id];
}

anotherObject* objectsContainer::get_another_object(std::string id) {
	return another_object_ptr[id];
}

void objectsContainer::createObject(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity) {
	if (_object_id.substr(0, 6) == "bullet") {
		bullet* Object = new bullet(_object_id, _positionX, _positionY, _width, _height, _gravity);
		bullet_object_ptr[_object_id] = Object;
	}
	else if(_object_id.substr(0, 6) == "player") {
		player* Object = new player(_object_id, _positionX, _positionY, _width, _height, _gravity);
		player_object_ptr[_object_id] = Object;
	}
	else if (_object_id.substr(0, 5) == "enemy") {
		enemy* Object = new enemy(_object_id, _positionX, _positionY, _width, _height, _gravity);
		enemy_object_ptr[_object_id] = Object;
	}
	else {
		anotherObject* Object = new anotherObject(_object_id, _positionX, _positionY, _width, _height, _gravity);
		another_object_ptr[_object_id] = Object;
	}
}

void objectsContainer::assign_bullet(std::string id, bullet* bullet_ptr) {
	bullet* Bullet = bullet_ptr;
	bullet_object_ptr[Bullet->getId()] = Bullet;
}

void objectsContainer::show_object(std::string id) {
	if (id.substr(0, 6) == "bullet") {
		bullet* Object = bullet_object_ptr[id];
		sprites_ptr[id] = Object->getSprite();
	}
	else if(id.substr(0, 6) == "player") {
		player* Object = player_object_ptr[id];
		sprites_ptr[id] = Object->getSprite();
	}
	else if (id.substr(0, 5) == "enemy") {
		enemy* Object = enemy_object_ptr[id];
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

void objectsContainer::delete_object(std::string id) {
	if (id.substr(0, 6) == "bullet") {
		delete bullet_object_ptr[id];
	}
	else if (id.substr(0, 6) == "player") {
		delete player_object_ptr[id];
	}
	else if (id.substr(0, 5) == "enemy") {
		delete enemy_object_ptr[id];
	}
	else {
		delete another_object_ptr[id];
	}
	std::cout << id << " deleted\n";
}

void objectsContainer::clearObject() {
	while (!bullet_object_ptr.empty()) {
		auto object = bullet_object_ptr.begin();
		sprites_ptr.erase(object->first);
		delete bullet_object_ptr[object->first];
		object = bullet_object_ptr.erase(object);
	}
}

sf::RectangleShape* objectsContainer::draw_sprite(std::string id) {
	sf::RectangleShape* sprite = sprites_ptr[id];
	return sprite;
}

std::unordered_map<std::string, sf::RectangleShape*>* objectsContainer::getSpritesMap() {
	return &sprites_ptr;
}

std::unordered_map <std::string, enemy*>* objectsContainer::getEnemyMap() {
	return &enemy_object_ptr;
}

std::unordered_map <std::string, bullet*>* objectsContainer::getBulletMap() {
	return &bullet_object_ptr;
}

bool objectsContainer::isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2) {
	return shape_1->getGlobalBounds().intersects(shape_2->getGlobalBounds());
}

//commented code
//template <>
// 
//bullet* objectsContainer::get_objectptr<bullet>(const std::string& id) {
//	// Implementation to retrieve Bullet objects from the unordered_map
//	return bullet_object_ptr[id];
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
//		return static_cast<T*>(bullet_object_ptr[id]);
//	}
//	else if (id.substr(0, 6) == "player") {
//		return static_cast<T*>(player_object_ptr[id]);
//	}
//	else {
//		return static_cast<T*>(another_object_ptr[id]);
//	}
//}