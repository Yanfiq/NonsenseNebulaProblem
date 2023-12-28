#pragma once
#include <unordered_map>

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "QuadtreeNode.h"

class collisionHandler {
public:
	static int handleCollision(sf::RenderWindow& window);
	//static void checkCollision(std::unordered_map<int, object*> container, sf::Vector2f size);
};