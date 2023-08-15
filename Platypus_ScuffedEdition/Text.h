#pragma once
#include "SFML/Graphics.hpp"
#include "RichText.hpp"
#include "Images.h"

class textRenderer {
private:
	sf::Font font;
	sf::Text Text;

public:
	textRenderer(std::string fontDirectory);
	sf::Font* getFont();
	void displayText(sf::RenderWindow& window, std::string string, int size, sf::Color color, float position_x, float position_y);
	void displayMultipleChoice(sf::RenderWindow& window, std::vector<std::string> choices, int choice, int size, sf::Color chosen, sf::Color notChosen, float position_x, float position_y);
};