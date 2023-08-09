#pragma once
#include <random>
#include <ctime>
#include <map>
#include "bullet.h"
#include "enemy.h"
#include "player.h"

enum objectType {
	player_obj = 100,
	playerBullet_obj = 200,
	enemy_obj = 300,
	enemyBullet_obj = 400
};

float getRandomFloat(float min, float max);
int getRandomInteger(int min, int max);
std::map<int, int> getCollisionData();