#pragma once
#include "objects.h"
#include "bullet.h"
#include "soundManager.h"
#include "animation.h"
#include "bar.h"
#include "textureManager.h"
#define MAX_ENEMY_HEALTH 100

class enemy : public object {
protected:
	float hp = 100.0f;
	static int bullet_count;
	static std::unordered_map<int, enemy*> enemy_map;
	bar HPBar;

public:
	enemy(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY);

	void reduceHp(float damage);
	void shoot();
	float getHp();

	static std::unordered_map<int, enemy*>* getEnemyMap();
	static enemy* getObjectPtr(int id);
	static void deleteObject(int id);

	static void clearObject();
	static void renderAllObject(double dt, sf::RenderWindow& window, bool Update);
};