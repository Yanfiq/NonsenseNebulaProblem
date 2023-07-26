#ifndef MANAGEOBJECT_H
#define MANAGEOBJECT_H

#include <unordered_map>
#include <string>
#include "player.h"
#include "bullet.h"
#include "inanimateObject.h"

class manageObject {
private:
	static std::unordered_map <std::string, player*> player_object_ptr;
	static std::unordered_map <std::string, bullet*> bullets_object_ptr;
	static std::unordered_map<std::string, inanimateObject*> another_object_ptr;
	static std::unordered_map <std::string, sf::RectangleShape*> sprites_ptr;

public:
	static void createObject(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);
	static void delete_object(std::string id);
	static std::unordered_map<std::string, sf::RectangleShape*> getSpritesMap();
	static bool isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2);
	static void show_object(std::string id);
	static void unshow_object(std::string id);
	static sf::RectangleShape* draw_sprite(std::string id);

	//template <typename T>
	//static T* get_objectptr(std::string id) {
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

	template <typename T>
	static T* get_objectptr(std::string id);
};

#endif