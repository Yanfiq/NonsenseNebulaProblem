#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SFML/Rect.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Rect.hpp"

class object {
private:
	float positionX = 0.f, positionY = 0.f;
	float velocityX = 0.f, velocityY = 0.f;
	float width = 0, height = 0;
	float gravity = 0.0002f;
	float maxY = 0.5f;
	float minY = -0.5f;
	float HP = 100;
	std::string object_id;
	sf::RectangleShape object_sprite;

public:
	object(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);
	sf::RectangleShape* getSprite();
	sf::RectangleShape shoot(float velocity_x, object shooter);
	void reduceHP(float damage);
	float getPositionX();
	float getPositionY();
	float getVelocityX();
	void thrust();
	float getVelocityY();
	void setVelocity(float vx, float vy);
	void update(float time);
	std::string getId();
};