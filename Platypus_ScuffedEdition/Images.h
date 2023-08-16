#pragma once
#include "SFML/Graphics.hpp"
#include <filesystem>
#include <iostream>

namespace img {
	struct texture {
		static sf::Texture background;
		static sf::Texture keyboardLeft;
		static sf::Texture keyboardRight;
		static sf::Texture spacebarKey;
	};

	void initializeTexture();
	void displayImage(sf::RenderWindow& window, sf::Texture texture, float position_x, float position_y, sf::Vector2f size);
}