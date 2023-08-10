#include "messages.h"

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

	sfe::RichText lose() {
		sfe::RichText text(font);

		text << sf::Color::White << "YOU LOSE\nBETTER LUCK NEXT TIME"
			<< sf::Color::White << "\nPress 'R' to continue";

		text.setCharacterSize(60);

		return text;
	}

	sfe::RichText startLevel(int level) {
		sfe::RichText text(font);

		text << sf::Color::White << "LEVEL " << sf::Color::Cyan << std::to_string(level)
			<< sf::Color::White << "\nPress ENTER to continue";

		text.setCharacterSize(60);
		return text;
	}

	sfe::RichText score(float point) {
		sfe::RichText text(font);

		text << sf::Color::White << "Score: " << sf::Color::Cyan << std::to_string(point);

		text.setCharacterSize(60);
		return text;
	}

	sfe::RichText win() {
		sfe::RichText text(font);

		text << sf::Color::White << "CONGRATULATION, YOU ARE THE WINNER\n"
			<< sf::Color::White << "Press 'R' to restart";

		text.setCharacterSize(60);
		return text;
	}

	sfe::RichText pauseText() {
		sfe::RichText text(font);

		text << sf::Color::White << "PAUSED\n"
			<< sf::Color::White << "Press 'space' to back to the game";

		text.setCharacterSize(60);
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
		text.setCharacterSize(100);
		text.setPosition(100, 100);

		return text;
	}

	sfe::RichText singleMultiChoice(int choice) {
		sfe::RichText text(font);
		switch (choice) {
		case 0:
		{
			text << sf::Color::Cyan << "Singleplayer\n"
				<< sf::Color::White << "Multiplayer";
			break;
		}
		case 1:
		{
			text << sf::Color::White << "Singleplayer\n"
				<< sf::Color::Cyan << "Multiplayer";
			break;
		}
		}
		text.setCharacterSize(100);
		text.setPosition(100, 100);

		return text;
	}

	sfe::RichText text::tutorialStep(int step) {
		sfe::RichText text(font);
		switch (step)
		{
		case 1:
			text << sf::Color::Cyan << "Step 1\n"
				<< sf::Color::White << "use the Z button to counter gravity\n"
				<< sf::Color::White << "press enter to continue";
			break;
		case 2:
			text << sf::Color::Cyan << "Step 2\n"
				<< sf::Color::White << "use the X button to fire the shot\n"
				<< sf::Color::White << "press enter to continue";
			break;
		case 3:
			text << sf::Color::Cyan << "Step 3\n"
				<< sf::Color::White << "use the C button to reload the bullet\n"
				<< sf::Color::White << "press enter to continue";
			break;
		case 4:
			text << sf::Color::Cyan << "Step 4\n"
				<< sf::Color::White << "use the spacebar to pause the game\n"
				<< sf::Color::White << "press enter to continue";
			break;
		}

		text.setCharacterSize(30);
		text.setPosition(50, 50);
		return text;
	}
}