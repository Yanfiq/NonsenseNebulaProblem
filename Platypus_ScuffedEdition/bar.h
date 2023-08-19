#pragma once
#include <SFML/Graphics.hpp>

class bar {
private:
	sf::RectangleShape frame;
	sf::RectangleShape theBar;
	sf::Color low;
	sf::Color normal;
	float maxValue;

public:
	bar(sf::Color frameColor, int _frameThickness, sf::Color _low, sf::Color _normal, float _maxValue, float _width, float _height);
	void draw(sf::RenderWindow& window, float currentValue, sf::Vector2f position);
};