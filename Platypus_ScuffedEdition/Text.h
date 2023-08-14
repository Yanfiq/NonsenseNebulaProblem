#pragma once
#include "SFML/Graphics.hpp"
#include "RichText.hpp"
#include "Images.h"

class text {
private:
	static sf::Font font;
	enum part { start, settings, tutorial, transition, singleMulti, play, pause };

public:
	static void fontInitialization(std::string fontDir);

	static void displayText(sf::RenderWindow& window, std::string text, int size, sf::Color color, float position_x, float position_y);
	static void displayChoice(sf::RenderWindow& window, int choice, int scene, int bgmVol, int sfxVol);
	static void displayTutorial(sf::RenderWindow& window, int step);
};