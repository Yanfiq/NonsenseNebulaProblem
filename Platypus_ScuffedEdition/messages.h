#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class text {
private:
	static sf::Font font;

public:
	static sf::Text bulletEmpty();
	static sf::Text lose();
	static sf::Text startLevel(int level);
};