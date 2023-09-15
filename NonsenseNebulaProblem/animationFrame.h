#pragma once
#include "SFML/Graphics.hpp"

class animationFrame {
private:
	sf::RectangleShape frame;
	int row; int collumn; sf::Vector2f frameSize;

public:
	animationFrame(sf::Texture* texture, int _row, int _collumn, sf::Vector2f _position);
	sf::RectangleShape* getFrame();
	void updateFrame();
	bool isEnded();
};