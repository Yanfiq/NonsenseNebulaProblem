#pragma once
#include "bullet.h"
#include "enemy.h"
#include "textureManager.h"
#include "player.h"
#include "animation.h"

#include <random>
#include <ctime>
#include <unordered_map>

enum objectType {
	player_obj = 100,
	playerBullet_obj = 200,
	enemy_obj = 300,
	enemyBullet_obj = 400
};

float getRandomFloat(float num_1, float num_2);
int getRandomInteger(int num_1, int num_2);

int processCollision();
void displayTutorial(sf::RenderWindow& window, sf::Font* font, int step);
sfe::RichText displayCredit(sf::Font* font, float position_x, float position_y);