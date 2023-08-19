#include <stdbool.h>
#include <iostream>
#include "SFML/Audio.hpp"

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "Text.h"
#include "func.h"
#include "textureManager.h"
#include "InputManager.h"
#include "animation.h"

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	sf::View view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));
	window.setView(view);

	sf::Clock clock;
	sf::Event event;
	sf::Music bgmusic;
	bgmusic.openFromFile("audio/Boooring.ogg");
	bgmusic.play();
	bgmusic.setLoop(true);
	
	//texture initialization
	textRenderer TextRenderer("fonts/Poppins-SemiBold.ttf");
	textureManager::initializeTexture();
	sounds::loadSound();
 
	// enumeration for scene changes
	enum part { start, settings , tutorial, credits, transition, singleMulti, play, pause };
	// enumeration for objectType
	enum objectType {
		player_obj = 100,
		playerBullet_obj = 200,
		enemy_obj = 300,
		enemyBullet_obj = 400
	};

	// variables that'll be used inside the main game
	int level = 0;					// as the name implies, to differentiate levels
	int currentPoint = 0;			// as the name implies, to save the point calculation result
	bool generateEnemy = false;		// decides whether to generate new enemies

	// variables that'll be used on multiple choices scene
	int scene = start;				// decide what scene is being run

	// only for tutorial scene
	int stepTutorial = 1;

	//volumes
	int bgmVolume = 100;
	int sfxVolume = 100;

	bool cheat = false;

	//binding keys
	InputManager::Instance()->KBind("Enter", sf::Keyboard::Enter);
	InputManager::Instance()->KBind("Spacebar", sf::Keyboard::Space);
	InputManager::Instance()->KBind("Back", sf::Keyboard::Escape);
	InputManager::Instance()->KBind("Up_1", sf::Keyboard::Up);
	InputManager::Instance()->KBind("Up_2", sf::Keyboard::W);
	InputManager::Instance()->KBind("Down_1", sf::Keyboard::Down);
	InputManager::Instance()->KBind("Down_2", sf::Keyboard::S);
	InputManager::Instance()->KBind("Left_1", sf::Keyboard::Left);
	InputManager::Instance()->KBind("Left_2", sf::Keyboard::A);
	InputManager::Instance()->KBind("Right_1", sf::Keyboard::Right);
	InputManager::Instance()->KBind("Right_2", sf::Keyboard::D);

	// main game loop
	while (window.isOpen()) {
		bgmusic.setVolume(bgmVolume);
		sounds::monitoring();

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
			{
				int width = event.size.width; int height = event.size.height;
				if (width < 1280)
					width = 1280;
				if (height < 720)
					height = 720;
				sf::FloatRect visibleArea(0.f, 0.f, width, height);
				window.setSize(sf::Vector2u(width, height));
				window.setView(sf::View(visibleArea));
				break;
			}
			}
			InputManager::Instance()->KRUpdate(event);
		}

		// draw the background and animation
		textureManager::displayImage(window, "background_nebula.jpg", 0, 0, sf::Vector2f(window.getSize()));
		// sprites render
		float dt = clock.restart().asSeconds();
		if (scene == pause) {
			if (!cheat) {
				player::justDrawAllObject(window);
				bullet::justDrawAllObject(window);
			}
			else {
				player::updateNDrawAllObject(dt, window);
				bullet::updateNDrawAllObject(dt, window);
			}

			enemy::justDrawAllObject(window);
		}
		else {
			player::updateNDrawAllObject(dt, window);
			bullet::updateNDrawAllObject(dt, window);
			enemy::updateNDrawAllObject(dt, window);
		}
		currentPoint += processCollision();
		animate::monitoringAnimation(window);

		//outside pollEvent
		switch (scene) {
		case start:
		{
			bullet::clearObject();
			enemy::clearObject();
			static int choice = 0;
			std::vector<std::string> choices = { "START", "SETTINGS", "EXIT" };
			TextRenderer.displayText(window, "something is happening somewhere", 50, sf::Color::White, 100, 100);
			TextRenderer.displayMultipleChoice(window, choices, choice, 50, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 300);

			if (InputManager::Instance()->KeyPress("Up_1"))   choice = (choice == 0) ? 0 : choice - 1;
			if (InputManager::Instance()->KeyPress("Down_1")) choice = (choice == 2) ? 2 : choice + 1;
			if (InputManager::Instance()->KeyPress("Enter")) {
				switch (choice) {
				case 0:scene = singleMulti; break;
				case 1:scene = settings; break;
				case 2: window.close(); break;
				}
				choice = 0;
			}
			break;
		}
		case tutorial:
		{
			static int step = 1;
			displayTutorial(window, TextRenderer.getFont(), step);
			TextRenderer.displayText(window, "Press ENTER to continue", 30, sf::Color::White, 100, 600);
			if (InputManager::Instance()->KeyPress("Enter")) step++;
			if (step > 5) {
				scene = settings;
				step = 1;
			}
			break;
		}

		case settings:
		{
			static int choice = 0;
			std::string Cheat = (cheat) ? "Enabled" : "Disabled";
			std::vector<std::string> choices = { "BGM Volume : <" + std::to_string(bgmVolume) + "%>",
												 "SFX Volume : <" + std::to_string(sfxVolume) + "%>",
												 "Cheat : < " + Cheat + " >",
												 "Tutorial",
												 "Credit",
												 "Back to main menu"};
			TextRenderer.displayText(window, "something is happening somewhere", 50, sf::Color::White, 100, 100);
			TextRenderer.displayMultipleChoice(window, choices, choice, 40, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 400);

			// moving between choices
			if (InputManager::Instance()->KeyPress("Up_1")) choice = (choice == 0) ? 0 : choice - 1;
			if (InputManager::Instance()->KeyPress("Down_1")) choice = (choice == 5) ? 5 : choice + 1;

			// Decrease
			if (InputManager::Instance()->KeyPress("Left_1")) {
				switch (choice) {
				case 0:bgmVolume = (bgmVolume == 0) ? 0 : bgmVolume - 5; break; 
				case 1:sfxVolume = (sfxVolume == 0) ? 0 : sfxVolume - 5; sounds::playShootSound(sfxVolume); break;
				case 2:cheat = false; window.create(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close); window.setFramerateLimit(60);  break;
				}
			}

			//Increase
			if (InputManager::Instance()->KeyPress("Right_1")) {
				switch (choice) {
				case 0:bgmVolume = (bgmVolume == 100) ? 100 : bgmVolume + 5; break;
				case 1:sfxVolume = (sfxVolume == 100) ? 100 : sfxVolume + 5; sounds::playShootSound(sfxVolume); break;
				case 2:cheat = true; window.create(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize); window.setFramerateLimit(60);  break;
				}
			}

			// move scene
			if (InputManager::Instance()->KeyPress("Enter")) {
				switch (choice) {
				case 3:scene = tutorial; break;
				case 4:scene = credits; break;
				case 5:scene = start; break;
				}
				choice = 0;
			}
			break;
		}

		case credits:
		{
			static float positionY = window.getSize().y;
			sfe::RichText text = displayCredit(TextRenderer.getFont(), 100, positionY);
			window.draw(text);
			positionY -= 5;
			if (positionY < (- 1500)) {
				scene = settings;
				positionY = 800;
			}
			break;
		}

		case singleMulti:
		{
			static int choice;
			std::vector<std::string> choices = { "Singleplayer", "Multiplayer" };
			TextRenderer.displayText(window, "something is happening somewhere", 50, sf::Color::White, 100, 100);
			TextRenderer.displayText(window, "Choose your gamemode: ", 40, sf::Color::White, 100, window.getSize().y - 220);
			TextRenderer.displayMultipleChoice(window, choices, choice, 40, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 180);

			// moving between choices
			if (InputManager::Instance()->KeyPress("Up_1"))   choice = 0;
			if (InputManager::Instance()->KeyPress("Down_1")) choice = 1;
			if (InputManager::Instance()->KeyPress("Enter")){
				player* Player_1 = new player(1, "gameplay_player.png", 100, 100, 0, 0);
				if (choice == 1) {
					player* Player_2 = new player(2, "gameplay_player.png", 100, 300, 0, 0);
				}
				scene = play;
				choice = 0;
			}
			break;
		}

		case transition:
		{
			if(level == -1){ //lOSE
				TextRenderer.displayText(window, "YOU LOSE :(\nBETTER LUCK NEXT TIME", 40, sf::Color::White, 100, 100);
				TextRenderer.displayText(window, "Your last score is " + std::to_string(currentPoint), 40, sf::Color::White, 100, 200);
				TextRenderer.displayText(window, "Press Enter to back to main menu", 40, sf::Color::White, 100, window.getSize().y - 60);
				if (InputManager::Instance()->KeyPress("Enter")) {
					level = 0;
					currentPoint = 0;
					scene = start;
				}
			}
			else if (level > 2) { //WIN
				TextRenderer.displayText(window, "CONGRATULATION :)\nYOU'RE THE WINNER", 40, sf::Color::White, 100, 100);
				TextRenderer.displayText(window, "Your final score is " + std::to_string(currentPoint), 40, sf::Color::White, 100, 200);
				TextRenderer.displayText(window, "Press Enter to back to main menu", 40, sf::Color::White, 100, window.getSize().y - 60);
				if (InputManager::Instance()->KeyPress("Enter")) {
					level = 0;
					currentPoint = 0;
					scene = start;
				}
			}
			else { //NEXT LEVEL
				TextRenderer.displayText(window, "LEVEL " + std::to_string(level + 1), 40, sf::Color::Cyan, 100, 100);
				TextRenderer.displayText(window, "Press ENTER to continue", 30, sf::Color::White, 100, window.getSize().y - 60);
				if (InputManager::Instance()->KeyPress("Enter")) {
					level++;
					generateEnemy = true;
					scene = play;
				}
			}
			break;
		}

		case pause:
		{
			static int choice = 0;
			TextRenderer.displayText(window, "PAUSE", 40, sf::Color::White, 100, 100);
			std::vector<std::string> choices = { "Resume", "Rage quit" };
			TextRenderer.displayMultipleChoice(window, choices, choice, 40, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 160);

			if (InputManager::Instance()->KeyPress("Up_1"))   choice = 0;
			if (InputManager::Instance()->KeyPress("Down_1")) choice = 1;
			if (InputManager::Instance()->KeyPress("Enter")) {
				switch (choice) {
				case 0:
					scene = play;  
					break;
				case 1:
					scene = start; 
					level = 0;
					player::clearObject();
					break;
				}
			}
			break;
		}

		case play:
		{
			//pause the game if the window lost its focus
			if (!window.hasFocus()) {
				scene = pause;
			}


			//level mechanics and enemy object creation
			if (generateEnemy) {
				bullet::clearObject();
				switch (level) {
				case 1:
				{
					for (int i = 1; i < getRandomFloat(window.getSize().x / 288, window.getSize().y / 176); i++) {
						enemy* Enemy = new enemy(i, "gameplay_enemy.png", getRandomFloat(400, window.getSize().x), getRandomFloat(0, window.getSize().y), getRandomFloat(-500, 500), getRandomFloat(-500, 500));
						animate::play("gameplay_spawn.png", 4, 4, sf::Vector2f(Enemy->getPositionX(), Enemy->getPositionY()));
					}
					break;
				}
				case 2:
				{
					for (int i = 1; i < getRandomFloat((window.getSize().x / 288) * 2, (window.getSize().y / 176) * 2); i++) {
						enemy* Enemy = new enemy(i, "gameplay_enemy.png", getRandomFloat(400, window.getSize().x), getRandomFloat(0, window.getSize().y), getRandomFloat(-750, 750), getRandomFloat(-750, 750));
						animate::play("gameplay_spawn.png", 4, 4, sf::Vector2f(Enemy->getPositionX(), Enemy->getPositionY()));
					}
					break;
				}
				case 3:
				{
					for (int i = 1; i < getRandomFloat((window.getSize().x / 288) * 3, (window.getSize().y / 176) * 3); i++) {
						enemy* Enemy = new enemy(i, "gameplay_enemy.png", getRandomFloat(400, window.getSize().x), getRandomFloat(0, window.getSize().y), getRandomFloat(-1000, 1000), getRandomFloat(-1000, 1000));
						animate::play("gameplay_spawn.png", 4, 4, sf::Vector2f(Enemy->getPositionX(), Enemy->getPositionY()));
					}
					break;
				}
				}
				generateEnemy = false;
				break;
			}

			//level up when the enemy is 0
			if (enemy::getEnemyMap()->empty()) {
				scene = transition;
				break;
			}

			//lose when the player is 0
			if (player::getPlayerMap()->empty()) {
				level = -1;
				scene = transition;
				break;
			}

			if (InputManager::Instance()->KeyPress("Spacebar")) {
				scene = pause;
			}

			//enemy's attack algorithm
			std::unordered_map<int, enemy*>* enemyMap = enemy::getEnemyMap();
			std::unordered_map<int, player*>* playerMap = player::getPlayerMap();
			for (auto enemy_object = enemyMap->begin(); enemy_object != enemyMap->end(); enemy_object++) {
				enemy* Enemy = enemy_object->second;
				for (auto player_object = playerMap->begin(); player_object != playerMap->end(); player_object++) {
					player* Player = player_object->second;
					if ((Enemy->getPositionY() < Player->getPositionY() + 5) &&
						(Enemy->getPositionY() > Player->getPositionY() - 5)) {
						Enemy->shoot(sfxVolume);
					}
				}
			}

			//collision detection and object removal
			TextRenderer.displayText(window, "Score : " + std::to_string(currentPoint), 40, sf::Color::White, 30, 30);
			break;
		}
		}

		if ((scene != pause) || (scene == pause && cheat)) {
			//FIRST PLAYER
			if (player::getObjectPtr(101) != NULL) {
				player* player_1 = player::getObjectPtr(101);
				if (InputManager::Instance()->KeyDown("Up_1"))
					player_1->thrustUp();
				if (InputManager::Instance()->KeyDown("Down_1"))
					player_1->thrustDown();
				if (InputManager::Instance()->KeyDown("Right_1") && player_1->getBulletCount() <= 30)
					player_1->shoot(sfxVolume);
				if (player_1->getBulletCount() >= 30 && (scene == play || scene == pause)) {
					TextRenderer.displayText(window, "player_1's bullet is empty", 30, sf::Color::White, 30, window.getSize().y - 60);
					if (InputManager::Instance()->KeyPress("Left_1")) player_1->resetBulletCount();
				}
			}

			//SECOND PLAYER
			if (player::getObjectPtr(102) != NULL) {
				player* player_2 = player::getObjectPtr(102);
				if (InputManager::Instance()->KeyDown("Up_2"))
					player_2->thrustUp();
				if (InputManager::Instance()->KeyDown("Down_2"))
					player_2->thrustDown();
				if (InputManager::Instance()->KeyDown("Right_2") && player_2->getBulletCount() <= 30)
					player_2->shoot(sfxVolume);
				if (player_2->getBulletCount() >= 30 && (scene == play || scene == pause)) {
					TextRenderer.displayText(window, "player_2's bullet is empty", 30, sf::Color::White, 850, 650);
					if (InputManager::Instance()->KeyPress("Left_2")) player_2->resetBulletCount();
				}
			}
		}

		window.display();
		window.clear();
		InputManager::Instance()->Update();
	}
	return 0;
}