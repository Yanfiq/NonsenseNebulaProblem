#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Rect.hpp"
#include <unordered_map>
#include <vector>
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
	std::string object_id;
	sf::RectangleShape object_sprite;
	static std::unordered_map<std::string, sf::RectangleShape*> sprites_map;

public:
	object(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);
	sf::RectangleShape* getSprite();
	float getPositionX();
	float getPositionY();
	float getVelocityX();
	float getVelocityY();
	void setVelocity(float vx, float vy);
	void setPosition(float px, float py);
	void update(double time);
	std::string getId();

	static std::unordered_map<std::string, sf::RectangleShape*>* getSpritesMap();
	static bool isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2);
	static void hideObject(std::string id);
	static void unhideObject(std::string id, sf::RectangleShape* sprite);
};