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
	static sfe::RichText score(float points);
	static sfe::RichText win();

	static sfe::RichText startMenuChoice(int choice);

	static sfe::RichText tutorialStep(int step);
};