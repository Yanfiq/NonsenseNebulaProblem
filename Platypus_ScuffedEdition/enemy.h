#pragma once
#include "objects.h"
#include "bullet.h"

class enemy : public object {
protected:
	float hp = 100.0f;
	static sf::Texture texture;
	static int bullet_count;
	static std::unordered_map<int, enemy*> enemy_map;

public:
	enemy(int _object_id, float _positionX, float _positionY, float _velocityX, float _velocityY, float _gravity);

	void reduceHp(float damage);
	void shoot();
	float getHp();

	static std::unordered_map<int, enemy*>* getEnemyMap();
	static enemy* getObjectPtr(int id);
	static void deleteObject(int id);
	static void initializeTexture(std::string textureDir);

	static void clearObject();
	static void updateNDrawAllObject(double dt, sf::RenderWindow& window);
};