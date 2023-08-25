#pragma once
#include "bullet.h"
#include "enemy.h"
#include "textureManager.h"
#include "player.h"
#include "animation.h"

#include <random>
#include <ctime>
#include <unordered_map>

// generating random float between 2 number
float getRandomFloat(float num_1, float num_2);

// generating random integer between 2 number
int getRandomInteger(int num_1, int num_2);

// unodular function, created just to make main function cleaner
void displayTutorial(sf::RenderWindow& window, sf::Font* font, int step);
sfe::RichText displayCredit(sf::Font* font, float position_x, float position_y);