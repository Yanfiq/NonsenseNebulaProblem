#include "Images.h"

namespace img {
	void initializeTexture() {
		backgroundTexture.loadFromFile("images/nebula.jpg");
		keyboardLeft.loadFromFile("images/leftKeyb.jpg");
		keyboardRight.loadFromFile("images/rightKeyb.jpg");
	}

	sf::RectangleShape background() {
		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(backgroundTexture.getSize()));
		shape.setTexture(&backgroundTexture);
		return shape;
	}

	sf::RectangleShape keybLeft() {
		sf::RectangleShape shape;
		shape.setPosition(100, 300);
		shape.setSize(sf::Vector2f(keyboardLeft.getSize()));
		shape.setTexture(&keyboardLeft);
		return shape;
	}

	sf::RectangleShape keybRight() {
		sf::RectangleShape shape;
		shape.setPosition(700, 300);
		shape.setSize(sf::Vector2f(keyboardRight.getSize()));
		shape.setTexture(&keyboardRight);
		return shape;
	}
}