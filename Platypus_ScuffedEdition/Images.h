#pragma once
#include "SFML/Graphics.hpp"

namespace img {
	static sf::Texture backgroundTexture;
	static sf::Texture keyboardLeft;
	static sf::Texture keyboardRight;

	void initializeTexture();
	sf::RectangleShape background();
	sf::RectangleShape keybLeft();
	sf::RectangleShape keybRight();
}