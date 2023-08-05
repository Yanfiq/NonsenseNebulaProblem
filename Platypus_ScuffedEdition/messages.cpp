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

sfe::RichText text::startMenuChoice(int choice) {
	font.loadFromFile("fonts/Poppins-SemiBold.ttf");

	sfe::RichText text(font);
	switch (choice) {
	case 0:
	{
		text << sf::Color::Blue << "START\n"
			<< sf::Color::Black << "HELP\n"
			<< sf::Color::Black << "EXIT";
		break;
	}
	case 1:
	{
		text << sf::Color::Black << "START\n"
			<< sf::Color::Blue << "HELP\n"
			<< sf::Color::Black << "EXIT";
		break;
	}
	case 2:
	{
		text << sf::Color::Black << "START\n"
			<< sf::Color::Black << "HELP\n"
			<< sf::Color::Blue << "EXIT";
		break;
	}
	}
	text.setCharacterSize(50);
	text.setPosition(100, 100);
		
	return text;
}