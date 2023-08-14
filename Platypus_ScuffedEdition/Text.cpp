#include "Text.h"

sf::Font text::font;

void text::fontInitialization(std::string fontDir) {
	font.loadFromFile(fontDir);
}

void text::displayText(sf::RenderWindow& window, std::string text, int size, sf::Color color, float position_x, float position_y) {
	sf::Text Text;
	Text.setFont(font);
	Text.setString(text);
	Text.setCharacterSize(size);
	Text.setPosition(position_x, position_y);
	Text.setFillColor(color);
	window.draw(Text);
}

void text::displayMultipleChoice(sf::RenderWindow& window, std::vector<std::string> choices, int choice, int size, sf::Color chosen, sf::Color notChosen, float position_x, float position_y) {
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


void text::displayTutorial(sf::RenderWindow& window, int step) {
	sfe::RichText text_1(font);
	sfe::RichText text_2(font);
	switch (step)
	{
	case 1:
		text_1 << sf::Color::Cyan << "Step 1\n"
			<< sf::Color::White << "use 'W' button to go up";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Up' instead\n";
		text_2.setPosition(700, 150);

		img::displayImage(window, img::texture::keyboardLeft, 100, 300);
		img::displayImage(window, img::texture::keyboardRight, 700, 300);
		break;
	case 2:
		text_1 << sf::Color::Cyan << "Step 2\n"
			<< sf::Color::White << "use 'S' button to go down\n";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Down' instead\n";
		text_2.setPosition(700, 150);

		img::displayImage(window, img::texture::keyboardLeft, 100, 300);
		img::displayImage(window, img::texture::keyboardRight, 700, 300);
		break;
	case 3:
		text_1 << sf::Color::Cyan << "Step 3\n"
			<< sf::Color::White << "use 'D' button to fire the bullet\n";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Right' instead\n";
		text_2.setPosition(700, 150);

		img::displayImage(window, img::texture::keyboardLeft, 100, 300);
		img::displayImage(window, img::texture::keyboardRight, 700, 300);
		break;
	case 4:
		text_1 << sf::Color::Cyan << "Step 4\n"
			<< sf::Color::White << "use 'A' button to reload the bullet\n";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Left' instead\n";
		text_2.setPosition(700, 150);

		img::displayImage(window, img::texture::keyboardLeft, 100, 300);
		img::displayImage(window, img::texture::keyboardRight, 700, 300);
		break;
	case 5:
		text_1 << sf::Color::Cyan << "Step 5\n"
			<< sf::Color::White << "use spacebar to pause the game\n";
		text_1.setPosition(400, 100);

		img::displayImage(window, img::texture::spacebarKey, 380, 300);
		break;
	}

	text_1.setCharacterSize(30); text_2.setCharacterSize(30);
	window.draw(text_1);
	window.draw(text_2);
}

sfe::RichText text::displayCredit(float position_x, float position_y) {
	sfe::RichText text(font);
	text.setCharacterSize(30);
	text.setPosition(position_x, position_y);

	text << sf::Color::Cyan << "CREDITS\n\n"
		<< sf::Color::Cyan << sf::Text::Underlined << "Game Design\n"
		<< sf::Color::White << sf::Text::Regular << "Muhammad Ryan Fikri Fakhrezi\n\n"
		<< sf::Color::Cyan << sf::Text::Underlined << "Special thanks: \n"
		<< sf::Color::Cyan << sf::Text::Underlined << "Music: \n"
		<< sf::Color::White << sf::Text::Regular << "Boooring! [Instrumental]\n"
		<< sf::Color::White << sf::Text::Regular << "By Assertive Fluttershy\n\n"
		<< sf::Color::Cyan << sf::Text::Underlined << "Font: \n"
		<< sf::Color::White << sf::Text::Regular << "Poppins\n"
		<< sf::Color::White << sf::Text::Regular << "Designed by Indian Type Foundry, Jonny Pinhorn\n\n"
		<< sf::Color::Cyan << sf::Text::Underlined << "Art: \n"
		<< sf::Color::White << sf::Text::Regular << "Nebula background by Starkiteckt\n"
		<< sf::Color::White << sf::Text::Regular << "https://www.deviantart.com/starkiteckt\n\n"
		<< sf::Color::White << sf::Text::Regular << "Player's texture from pngwing.com\n"
		<< sf::Color::White << sf::Text::Regular << "https://www.pngwing.com/en/free-png-bxslp\n\n"
		<< sf::Color::White << sf::Text::Regular << "Enemy's texture from pngwing.com\n"
		<< sf::Color::White << sf::Text::Regular << "https://www.pngwing.com/en/free-png-ykqrx\n\n"
		<< sf::Color::White << sf::Text::Regular << "Bullet's texture by GintasDX\n"
		<< sf::Color::White << sf::Text::Regular << "https://www.deviantart.com/gintasdx\n\n";

	return text;
}