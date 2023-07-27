#ifndef OBJECT_H
#define OBJECT_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Rect.hpp"

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

public:
	object(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);
	sf::RectangleShape* getSprite();
	float getPositionX();
	float getPositionY();
	float getVelocityX();
	float getVelocityY();
	void setVelocity(float vx, float vy);
	void update(double time);
	std::string getId();
};

#endif