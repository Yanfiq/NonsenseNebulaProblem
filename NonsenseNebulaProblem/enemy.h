#pragma once
#include "objects.h"
#include "bullet.h"
#include "bar.h"
#include "RNG.h"
#include "textureManager.h"
#include "soundManager.h"
#include "animationManager.h"
#include "QuadtreeNode.h"

#include <iostream>
#include <cmath>
#define MAX_ENEMY_HEALTH 100

class enemy : public object {
protected:
	float hp = 100.0f;
	sf::Vector2f rangeVelocity;
	static int bullet_count;
	static std::unordered_map<int, enemy*> enemy_map;
	static sf::Clock randomize;
	sf::Clock attackTimer;
	sf::Time attackCooldown = sf::milliseconds(500);
	bool allowedFire = false;
	bar HPBar;

public:
	enemy(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY);

	void update(float time) override;
	void reduceHp(float damage);
	void shoot();
	float getHp();
	float getMaxHp();
	sf::Vector2f* getBaseV();

	static std::unordered_map<int, enemy*>* getEnemyMap();
	static enemy* getObjectPtr(int id);
	static void deleteObject(int id);

	static void clearObject();
	static void renderAllObject(double dt, sf::RenderWindow& window, bool Update);
};