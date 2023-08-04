#include "messages.h"

sf::Font text::font;

sf::Text text::bulletEmpty() {
	sf::Text text;
	font.loadFromFile("fonts/Poppins-SemiBold.ttf");
	text.setFont(font);
	text.setString("The bullet is empty\nPress X to reload the bullet");
	text.setCharacterSize(80);
	text.setFillColor(sf::Color::Black);

	return text;
}

sf::Text text::lose() {
	sf::Text text;
	font.loadFromFile("fonts/Poppins-SemiBold.ttf");
	text.setFont(font);
	text.setString("YOU LOSE\nBETTER LUCK NEXT TIME\npress 'r' to restart");
	text.setCharacterSize(80);
	text.setFillColor(sf::Color::Black);

	return text;
}

sf::Text text::startLevel(int level) {
	sf::Text text;
	font.loadFromFile("fonts/Poppins-SemiBold.ttf");
	text.setFont(font);
	std::string _string = "LEVEL " + std::to_string(level) + '\n' + "DO YOU READY?\npress 'c' to continue";
	text.setString(_string);
	text.setCharacterSize(80);
	text.setFillColor(sf::Color::Black);

	return text;
}