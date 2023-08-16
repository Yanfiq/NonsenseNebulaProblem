#pragma once
#include "SFML/Graphics.hpp"

class animationFrame {
private:
	sf::Texture texture;
	sf::RectangleShape frame;
	int row; int collumn; sf::Vector2f frameSize;

public:
	animationFrame(std::string textureDirectory, int _row, int _collumn, sf::Vector2f _position);
	sf::RectangleShape* getFrame();
	void updateFrame();
	bool isEnded();
};