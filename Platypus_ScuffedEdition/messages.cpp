#include "messages.h"

sf::Text bulletEmpty() {
	sf::Text text;
	text.setString("The bullet is empty\nPress X to reload the bullet");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Black);

	return text;
}

sf::Text lose() {
	sf::Text text;
	text.setString("YOU LOSE\nBETTER LUCK NEXT TIME\npress 'r' to restart");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Black);

	return text;
}

sf::Text startLevel(int level) {
	sf::Text text;

	std::string _string = "LEVEL " + std::to_string(level) + '\n' + "DO YOU READY?\npress 'c' to continue";
	text.setString(_string);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Black);

	return text;
}