#pragma once
#include "SFML/Graphics.hpp"
#include "RichText.hpp"

class textRenderer {
private:
	sf::Font font;
	sf::Text Text;

public:
	textRenderer(std::string fontDirectory);
	sf::Font* getFont();

	// displaying text into the RenderWindow
	// align : 0 = align left, 1 = align center, 2 = align right
	void displayText(sf::RenderWindow& window, std::string string, int align, int size, sf::Color color, float position_x, float position_y);
	void displayMultipleChoice(sf::RenderWindow& window, std::vector<std::string> choices, int choice, int size, sf::Color chosen, sf::Color notChosen, float position_x, float position_y);
};