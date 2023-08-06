#pragma once
#include "objects.h"
#include "bullet.h"
#include <unordered_map>

class player : public object {
protected:
	static std::unordered_map<std::string, player*> player_map;
	int bullet_count = 1;
	float hp = 100;

public:
	player(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);
	static player* getObjectPtr(std::string id);
	void shoot();
	void resetBulletCount();
	int getBulletCount();
	void thrust();
	float getPlayerHp() const;
	void setPlayerHp(float _hp);
	void reducePlayerHp(float damage);

	static void updateNDrawAllObject(double dt, sf::RenderWindow& window);
};