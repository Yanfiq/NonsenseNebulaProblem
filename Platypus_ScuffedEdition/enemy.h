#pragma once
#include "objects.h"
#include "bullet.h"
#include <unordered_map>

class enemy : public object {
protected:
	float hp = 100.0f;

	static int bullet_count;
	static std::unordered_map<std::string, enemy*> enemy_map;

public:
	enemy(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);

	void reduceHp(float damage);
	void shoot();
	float getHp();

	static std::unordered_map<std::string, enemy*>* getEnemyMap();
	static enemy* getObjectPtr(std::string id);
	static void deleteObject(std::string id);

	static void clearObject();
};