#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "anotherObject.h"

class objectsContainer {
protected:
	static std::unordered_map <std::string, player*> player_object_ptr;
	static std::unordered_map <std::string, bullet*> bullet_object_ptr;
	static std::unordered_map <std::string, enemy*>  enemy_object_ptr;
	static std::unordered_map <std::string, anotherObject*> another_object_ptr;

	static std::unordered_map <std::string, sf::RectangleShape*> sprites_ptr;

public:
	static void createObject(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);
	static void delete_object(std::string id);
	static void assign_bullet(std::string id, bullet* bullet_ptr);
	static void show_object(std::string id);
	static void unshow_object(std::string id);
	static void clearObject();

	static std::unordered_map<std::string, sf::RectangleShape*>* getSpritesMap();
	static std::unordered_map <std::string, enemy*>* getEnemyMap();
	static std::unordered_map<std::string, bullet*>* getBulletMap();

	static bool isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2);

	static sf::RectangleShape* draw_sprite(std::string id);
	//static player* get_object_player(std::string id);
	//static bullet* get_object_bullet(std::string id);
	//static enemy* get_object_enemy(std::string id);
	static anotherObject* get_another_object(std::string id);

	static object* get_objectptr(std::string id);
	//template <typename T>
	//static object* get_objectptr(std::string id) {
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

	//template <typename T>
	//static T* get_objectptr(const std::string& id);
};