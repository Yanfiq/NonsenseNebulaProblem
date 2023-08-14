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

void text::displayChoice(sf::RenderWindow& window, int choice, int scene, int bgmVol, int sfxVol) {
	sfe::RichText text(font);
	std::vector<std::string> startMenu_choices = { "START\n", "SETTINGS\n", "EXIT" };
	std::vector<std::string> setting_choices = { "BGM Volume : " + std::to_string(bgmVol) + '\n',
												 "SFX Volume : " + std::to_string(sfxVol) + '\n',
												 "Tutorial\n",
												 "Credit" };
	std::vector<std::string> singlemulti_choices = { "Singleplayer\n", "Multiplayer" };
	if (scene == start) {
		for (size_t i = 0; i < startMenu_choices.size(); i++) {
			if (i == choice)
				text << sf::Color::Cyan << startMenu_choices[i];
			else
				text << sf::Color::White << startMenu_choices[i];
		}
		text.setCharacterSize(60);
		text.setPosition(100, 400);
	}
	if (scene == settings) {
		text << sf::Color::White << "Settings: \n";
		for (size_t i = 0; i < setting_choices.size(); i++) {
			if (i == choice)
				text << sf::Color::Cyan << setting_choices[i];
			else
				text << sf::Color::White << setting_choices[i];
		}
		text.setCharacterSize(50);
		text.setPosition(100, 300);
	}
	if (scene == singleMulti) {
		text << sf::Color::White << "Gamemode: \n";
		for (size_t i = 0; i < singlemulti_choices.size(); i++) {
			if (i == choice)
				text << sf::Color::Cyan << singlemulti_choices[i];
			else
				text << sf::Color::White << singlemulti_choices[i];
		}
		text.setCharacterSize(60);
		text.setPosition(100, 400);
	}

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

		window.draw(img::keybLeft());
		window.draw(img::keybRight());
		break;
	case 2:
		text_1 << sf::Color::Cyan << "Step 2\n"
			<< sf::Color::White << "use 'S' button to go down\n";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Down' instead\n";
		text_2.setPosition(700, 150);

		window.draw(img::keybLeft());
		window.draw(img::keybRight());
		break;
	case 3:
		text_1 << sf::Color::Cyan << "Step 3\n"
			<< sf::Color::White << "use 'D' button to fire the bullet\n";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Right' instead\n";
		text_2.setPosition(700, 150);

		window.draw(img::keybLeft());
		window.draw(img::keybRight());
		break;
	case 4:
		text_1 << sf::Color::Cyan << "Step 4\n"
			<< sf::Color::White << "use 'A' button to reload the bullet\n";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Left' instead\n";
		text_2.setPosition(700, 150);

		window.draw(img::keybLeft());
		window.draw(img::keybRight());
		break;
	case 5:
		text_1 << sf::Color::Cyan << "Step 5\n"
			<< sf::Color::White << "use spacebar to pause the game\n";
		text_1.setPosition(400, 100);

		window.draw(img::spacebar());
		break;
	}

	text_1.setCharacterSize(30); text_2.setCharacterSize(30);
	window.draw(text_1);
	window.draw(text_2);
}
