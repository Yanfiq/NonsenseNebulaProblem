#pragma once
#include "SFML/Graphics.hpp"
#include "RichText.hpp"

namespace text {
	static sf::Font font;
	void fontInitialization(std::string fontDir);

	sfe::RichText gameTitle();
	sfe::RichText bulletEmpty(int player);
	sfe::RichText lose();
	sfe::RichText startLevel(int level);
	sfe::RichText score(float points);
	sfe::RichText win();
	sfe::RichText pauseText();
	sfe::RichText startMenuChoice(int choice);
	sfe::RichText singleMultiChoice(int choice);
	sfe::RichText tutorialStep(int step);
};