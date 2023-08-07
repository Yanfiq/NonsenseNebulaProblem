#pragma once
#include <random>
#include <ctime>
#include <map>
#include "bullet.h"
#include "enemy.h"
#include "player.h"

float getRandomFloat(float min, float max);
int getRandomInteger(int min, int max);
std::map<std::string, std::string> getCollisionData();