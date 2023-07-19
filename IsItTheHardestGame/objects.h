#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SFML/Rect.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Rect.hpp"

class object{
private:
	float positionX = 0, positionY = 0;
	float velocityX = 0, velocityY = 0;
	float width = 0, height = 0;
	float gravity = 0.01f;
	float maxY = 2;
	float minY = -2;
	float HP = 100;
	std::string object_id;
	sf::RectangleShape object_sprite;

public:
	object(std::string _object_id, float _positionX, float _positionY, float _width, float _height) {
		positionX = _positionX; positionY = _positionY; width = _width; height = _height; object_id = _object_id;
		object_sprite.setSize(sf::Vector2f(width, height));
		object_sprite.setFillColor(sf::Color(0, 0, 0, 255));
		object_sprite.setPosition(sf::Vector2f(positionX, positionY));
	}
	sf::RectangleShape getSprite();
	void reduceHP(float damage);
	float getPositionX();
	float getPositionY();
	void Update(float time);
	std::string getId();
	void thrust();
};