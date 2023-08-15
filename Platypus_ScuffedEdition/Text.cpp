#include "Text.h"

textRenderer::textRenderer(std::string fontDirectory) {
	font.loadFromFile(fontDirectory);
	Text.setFont(font);
}



void textRenderer::displayText(sf::RenderWindow& window, std::string string, int size, sf::Color color, float position_x, float position_y) {
	Text.setString(string);
	Text.setCharacterSize(size);
	Text.setPosition(position_x, position_y);
	Text.setFillColor(color);
	window.draw(Text);
}

sf::Font* textRenderer::getFont() {
	return &font;
}

void textRenderer::displayMultipleChoice(sf::RenderWindow& window, std::vector<std::string> choices, int choice, int size, sf::Color chosen, sf::Color notChosen, float position_x, float position_y) {
	sfe::RichText text(font);
	for (size_t i = 0; i < choices.size(); i++) {
		if (i == choice)
			text << chosen << choices[i] << '\n';
		else
			text << notChosen << choices[i] << '\n';
	}

	text.setCharacterSize(size);
	text.setPosition(position_x, position_y);
	window.draw(text);
}