#include "Text.h"

namespace text {
	void fontInitialization(std::string fontDir) {
		font.loadFromFile(fontDir);
	}

	sfe::RichText bulletEmpty(int player) {
		font.loadFromFile("fonts/Poppins-SemiBold.ttf");
		sfe::RichText text(font);

		switch (player) {
		case 1:
		{
			text << sf::Color::White << "player_1's bullet is empty\n"
				<< sf::Color::White << "Press 'C' to reload the bullet";
			text.setPosition(30, 560);
			break;
		}
		case 2:
		{
			text << sf::Color::White << "player_2's bullet is empty\n"
				<< sf::Color::White << "Press '/' to reload the bullet";
			text.setPosition(700, 560);
			break;
		}
		}

		text.setCharacterSize(30);

		return text;
	}

	sfe::RichText gameTitle() {
		sfe::RichText text(font);

		text << sf::Color::White << "something is happening somewhere";

		text.setPosition(sf::Vector2f(100, 100));
		text.setCharacterSize(60);

		return text;
	}

	sfe::RichText lose() {
		sfe::RichText text(font);

		text << sf::Color::White << "YOU LOSE\nBETTER LUCK NEXT TIME"
			<< sf::Color::White << "\nPress 'R' to back to main menu";

		text.setPosition(100, 100);
		text.setCharacterSize(60);

		return text;
	}

	sfe::RichText startLevel(int level) {
		sfe::RichText text(font);

		text << sf::Color::White << "LEVEL " << sf::Color::Cyan << std::to_string(level)
			<< sf::Color::White << "\nPress ENTER to continue";

		text.setCharacterSize(50);
		text.setPosition(100, 100);
		return text;
	}

	sfe::RichText score(float point) {
		sfe::RichText text(font);

		text << sf::Color::White << "Score: " << sf::Color::Cyan << std::to_string(point);

		text.setCharacterSize(50);
		text.setPosition(30, 30);
		return text;
	}

	sfe::RichText win() {
		sfe::RichText text(font);

		text << sf::Color::White << "CONGRATULATION, YOU ARE THE WINNER\n"
			<< sf::Color::White << "Press 'R' to back to main menu";

		text.setPosition(100, 100);
		text.setCharacterSize(50);
		return text;
	}

	sfe::RichText pauseText() {
		sfe::RichText text(font);

		text << sf::Color::Cyan << "PAUSED\n"
			<< sf::Color::White <<"Press 'space' to back to the game";

		text.setPosition(100, 100);
		text.setCharacterSize(50);
		return text;
	}

	sfe::RichText startMenuChoice(int choice) {
		sfe::RichText text(font);
		switch (choice) {
		case 0:
		{
			text << sf::Color::Cyan << "START\n"
				<< sf::Color::White << "HELP\n"
				<< sf::Color::White << "EXIT";
			break;
		}
		case 1:
		{
			text << sf::Color::White << "START\n"
				<< sf::Color::Cyan << "HELP\n"
				<< sf::Color::White << "EXIT";
			break;
		}
		case 2:
		{
			text << sf::Color::White << "START\n"
				<< sf::Color::White << "HELP\n"
				<< sf::Color::Cyan << "EXIT";
			break;
		}
		}
		text.setCharacterSize(60);
		text.setPosition(100, 400);

		return text;
	}

	sfe::RichText singleMultiChoice(int choice) {
		sfe::RichText text(font);
		switch (choice) {
		case 0:
		{
			text << sf::Color::White << "Choose your gamemode: \n"
				<< sf::Color::Cyan << "Singleplayer\n"
				<< sf::Color::White << "Multiplayer";
			break;
		}
		case 1:
		{
			text << sf::Color::White << "Choose your gamemode: \n"
				<< sf::Color::White << "Singleplayer\n"
				<< sf::Color::Cyan << "Multiplayer";
			break;
		}
		}
		text.setCharacterSize(60);
		text.setPosition(100, 400);

		return text;
	}

	sfe::RichText text::tutorialStep(int step) {
		sfe::RichText text(font);
		switch (step)
		{
		case 1:
			text << sf::Color::Cyan << "Step 1\n"
				<< sf::Color::White << "use 'W' button to go up\n"
				<< sf::Color::White << "press enter to continue";
			text.setPosition(100, 100);
			break;
		case 2:
			text << sf::Color::White << "for the player_2, use 'Up' instead\n"
				<< sf::Color::White << "press enter to continue";
			text.setPosition(700, 150);
			break;
		case 3:
			text << sf::Color::Cyan << "Step 2\n"
				<< sf::Color::White << "use 'S' button to go down\n"
				<< sf::Color::White << "press enter to continue";
			text.setPosition(100, 100);
			break;
		case 4:
			text << sf::Color::White << "for the player_2, use 'Down' instead\n"
				<< sf::Color::White << "press enter to continue";
			text.setPosition(700, 150);
			break;
		case 5:
			text << sf::Color::Cyan << "Step 3\n"
				<< sf::Color::White << "use 'D' button to fire the bullet\n"
				<< sf::Color::White << "press enter to continue";
			text.setPosition(100, 100);
			break;
		case 6:
			text << sf::Color::White << "for the player_2, use 'Right' instead\n"
				<< sf::Color::White << "press enter to continue";
			text.setPosition(700, 150);
			break;
		case 7:
			text << sf::Color::Cyan << "Step 4\n"
				<< sf::Color::White << "use 'A' button to reload the bullet\n"
				<< sf::Color::White << "press enter to continue";
			text.setPosition(100, 100);
			break;
		case 8:
			text << sf::Color::White << "for the player_2, use 'Left' instead\n"
				<< sf::Color::White << "press enter to continue";
			text.setPosition(700, 150);
			break;
		case 9:
			text << sf::Color::Cyan << "Step 5\n"
				<< sf::Color::White << "use spacebar to pause the game\n"
				<< sf::Color::White << "press enter to continue";
			text.setPosition(400, 100);
			break;
		}

		text.setCharacterSize(30);
		return text;
	}
}