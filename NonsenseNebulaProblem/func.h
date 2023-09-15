#pragma once
#include "bullet.h"
#include "enemy.h"
#include "textureManager.h"
#include "player.h"
#include <unordered_map>

// unodular function, created just to make main function cleaner
void displayTutorial(sf::RenderWindow& window, sf::Font* font, int step);
sfe::RichText displayCredit(sf::Font* font, float position_x, float position_y);