#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SFML/Rect.hpp"

class object
{
private:
	float positionX, positionY;
	float velocityX = 0, velocityY = 0;
	float width, height;
	float gravity = 0.01f;
	float maxY = 2;
	float minY = -2;
	float HP = 100;
	std::string object_id;
	sf::RectangleShape object_sprite;

public:
	object(std::string _object_id, float _positionX, float _positionY, float _width, float _height);
	sf::RectangleShape draw_object();
	void reduceHP(float damage);
	float getPositionX();
	float getPositionY();
	void Update(float time);
};