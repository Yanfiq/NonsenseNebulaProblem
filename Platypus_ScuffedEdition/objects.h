#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Rect.hpp"
#include <unordered_map>
#include <stdbool.h>

class player;
class enemy;
class bullet;

class object {
protected:
	float positionX = 0.f, positionY = 0.f;
	float velocityX = 0.f, velocityY = 0.f;
	float width = 0, height = 0;
	float gravity = 0.0002f;
	float maxY = 0.5f;
	float minY = -0.5f;
	sf::RectangleShape object_sprite;
	enum objectType{player_obj = 100, 
					playerBullet_obj = 200, 
					enemy_obj = 300, 
					enemyBullet_obj = 400};

public:
	object(float _positionX, float _positionY, float _velocityX, float _velocityY, float _width, float _height, float _gravity);
	sf::RectangleShape* getSprite();
	float getPositionX();
	float getPositionY();
	float getVelocityX();
	float getVelocityY();
	void setVelocity(float vx, float vy);
	void setPosition(float px, float py);
	void update(double time); 
	static bool isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2);
};