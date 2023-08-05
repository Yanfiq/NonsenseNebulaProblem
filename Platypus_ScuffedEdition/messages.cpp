#include "messages.h"

sf::Font text::font;

sfe::RichText text::bulletEmpty() {
	font.loadFromFile("fonts/Poppins-SemiBold.ttf");

	sfe::RichText text(font);

	text << sf::Color::Black << "The bullet is empty\n"
		<< sf::Color::Black << "Press 'X' to reload the bullet";

	text.setCharacterSize(50);
	text.setPosition(30, 560);

	return text;
}

sfe::RichText text::lose() {
	font.loadFromFile("fonts/Poppins-SemiBold.ttf");

	sfe::RichText text(font);

	text << sf::Color::Black << "YOU LOSE\nBETTER LUCK NEXT TIME"
		<< sf::Color::Black << "\nPress 'R' to continue";

	text.setCharacterSize(60);

	return text;
}

sfe::RichText text::startLevel(int level) {
	font.loadFromFile("fonts/Poppins-SemiBold.ttf");

	sfe::RichText text(font);

	text << sf::Color::Black << "LEVEL " << sf::Color::Blue << std::to_string(level)
		<< sf::Color::Black << "\nPress 'C' to continue";

	text.setCharacterSize(60);
	return text;
}

sfe::RichText text::score(float point) {
	font.loadFromFile("fonts/Poppins-SemiBold.ttf");

	sfe::RichText text(font);

	text << sf::Color::Black << "Score: " << sf::Color::Blue << std::to_string(point);

	text.setCharacterSize(60);
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
	text.setCharacterSize(100);
	text.setPosition(100, 100);
		
	return text;
}