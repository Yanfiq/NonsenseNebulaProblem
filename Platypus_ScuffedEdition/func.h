#pragma once
#include "bullet.h"
#include "enemy.h"
#include "player.h"

#include <random>
#include <ctime>
#include <unordered_map>

enum objectType {
	player_obj = 100,
	playerBullet_obj = 200,
	enemy_obj = 300,
	enemyBullet_obj = 400
};

float getRandomFloat(float min, float max);
int getRandomInteger(int min, int max);
int processCollision();