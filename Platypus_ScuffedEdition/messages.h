#pragma once
#include "SFML/Graphics.hpp"
#include "RichText.hpp"
#include <string>

class text {
private:
	static sf::Font font;

public:
	static sfe::RichText bulletEmpty();
	static sfe::RichText lose();
	static sfe::RichText startLevel(int level);


	static sfe::RichText startMenuChoice(int choice);
};