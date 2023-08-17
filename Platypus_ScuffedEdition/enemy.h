#pragma once
#include "objects.h"
#include "bullet.h"
#include "sound.h"
#include "textureManager.h"
#define MAX_ENEMY_HEALTH 100

class enemy : public object {
protected:
	float hp = 100.0f;
	static int bullet_count;
	static std::unordered_map<int, enemy*> enemy_map;

public:
	enemy(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY);

	void reduceHp(float damage);
	void shoot(int& sfxVol);
	float getHp();
	void drawHpBar(sf::RenderWindow& window, float position_x, float position_y, float width, float height);

	static std::unordered_map<int, enemy*>* getEnemyMap();
	static enemy* getObjectPtr(int id);
	static void deleteObject(int id);

	static void clearObject();
	static void updateNDrawAllObject(double dt, sf::RenderWindow& window);
};