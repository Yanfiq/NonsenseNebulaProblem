#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SFML/Rect.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Rect.hpp"

class object{
private:
	float positionX = 0.f, positionY = 0.f;
	float velocityX = 0.f, velocityY = 0.f;
	float width = 0, height = 0;
	float gravity = 0.0002f;
	float maxY = 0.4f;
	float minY = -0.4f;
	float HP = 100;
	std::string object_id;
	sf::RectangleShape object_sprite;

public:
	object(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);
	sf::RectangleShape getSprite();
	void reduceHP(float damage);
	float getPositionX();
	float getPositionY();
	void update(float time);
	void setVelocity(float vx, float vy);
	float getVelocityY();
	float getVelocityX();
	std::string getId();
	void thrust();
};