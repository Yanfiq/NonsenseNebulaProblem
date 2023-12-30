#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Rect.hpp"

#include <unordered_map>
#include <stdbool.h>
#include <math.h>

class object {
protected:
	float velocityX = 0.f, velocityY = 0.f;
	float maxY = 0.5f;
	float minY = -0.5f;
	object* old_state;
	sf::RectangleShape object_sprite;

public:
	enum Type {
		player_obj = 1000,
		playerBullet_obj = 2000,
		enemy_obj = 3000,
		enemyBullet_obj = 4000
	};

	object(float _positionX, float _positionY, float _velocityX, float _velocityY);
	sf::RectangleShape* getSprite();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getSize();
	static int getObjectType(int id);
	void setVelocity(float vx, float vy);
	void setPosition(float px, float py);
	virtual void update(float time); 
	static bool isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2);
};