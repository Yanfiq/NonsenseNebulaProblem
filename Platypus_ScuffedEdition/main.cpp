#include <stdbool.h>
#include <iostream>
#include "SFML/Audio.hpp"

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "Text.h"
#include "func.h"
#include "Images.h"
#include "animation.h"

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	sf::View view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));
	window.setView(view);

	sf::Clock clock;
	sf::Clock clock_2;
	sf::Event event;
	sf::Music bgmusic;
	bgmusic.openFromFile("audio/Boooring.ogg");
	bgmusic.play();
	bgmusic.setLoop(true);
	
	//texture initialization
	player::initializeTexture("images/player.png");
	bullet::initializeTexture("images/bullet.png");
	enemy::initializeTexture("images/enemy.png");
	textRenderer TextRenderer("fonts/Poppins-SemiBold.ttf");
	img::initializeTexture();
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
	bool up_1 = false;				// decides when the player object will reduce its velocityY value
	bool down_1 = false;
	bool up_2 = false;
	bool down_2 = false;
	bool shoot_1 = false;			// decides when the player object will execute the shoot() function
	bool shoot_2 = false;
	int level = 0;					// as the name implies, to differentiate levels
	int currentPoint = 0;			// as the name implies, to save the point calculation result
	bool generateEnemy = false;		// decides whether to generate new enemies

	// variables that'll be used on multiple choices scene
	int scene = start;				// decide what scene is being run
	int choice = 0;					// variables that will later change the scene in the start menu

	// only for tutorial scene
	int stepTutorial = 1;

	//volumes
	int bgmVolume = 100;
	int sfxVolume = 100;

	bool cheat = false;

	// main game loop
	while (window.isOpen()) {
		bgmusic.setVolume(bgmVolume);
		sounds::checkAndDeleteSound();

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
			{
				sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
				std::cout << window.getSize().x << " ; " << window.getSize().y << std::endl;
				break;
			}
			case sf::Event::KeyPressed:
				switch (scene) {
				case start:
				{
					if (event.key.code == sf::Keyboard::Up) {
						choice--;
						if (choice < 0)
							choice = 0;
					}
					if (event.key.code == sf::Keyboard::Down) {
						choice++;
						if (choice > 2)
							choice = 2;
					}
					if (event.key.code == sf::Keyboard::Enter) {
						if (choice == 0) {
							//Animate.playAnimation(window);
							scene = singleMulti;
						}
						if (choice == 1) {
							scene = settings;
						}
						if (choice == 2) {
							window.close();
						}
						choice = 0;
					}
					break;
				}
				case tutorial:
				{
					if (event.key.code == sf::Keyboard::Enter && stepTutorial <= 9) {
						stepTutorial ++;
					}
					break;
				}
				case settings:
				{
					if (event.key.code == sf::Keyboard::Down) {
						choice++;
						if (choice > 4)
							choice = 4;
					}
					if (event.key.code == sf::Keyboard::Up) {
						choice--;
						if (choice < 0)
							choice = 0;
					}
					if (event.key.code == sf::Keyboard::Left) {
						if (choice == 0) {
							bgmVolume -= 5;
							if (bgmVolume < 0)
								bgmVolume = 0;
						}
						if (choice == 1) {
							sfxVolume -= 5;
							if (sfxVolume < 0)
								sfxVolume = 0;
							sounds::playShootSound(sfxVolume);
						}
						if (choice == 2) {
							cheat = false;
							window.create(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
							window.setFramerateLimit(60);
						}
					}
					if (event.key.code == sf::Keyboard::Right) {
						if (choice == 0) {
							bgmVolume += 5;
							if (bgmVolume > 100)
								bgmVolume = 100;
						}
						if (choice == 1) {
							sfxVolume += 5;
							if (sfxVolume > 100)
								sfxVolume = 100;
							sounds::playShootSound(sfxVolume);
						}
						if (choice == 2) {
							cheat = true;
							window.create(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
							window.setFramerateLimit(60);
						}
					}
					if (event.key.code == sf::Keyboard::Escape) {
						scene = start;
						choice = 0;
					}
					if (event.key.code == sf::Keyboard::Enter) {
						if (choice == 3)
							scene = tutorial;
						if (choice == 4)
							scene = credits;
					}
					break;
				}
				case singleMulti:
				{
					if (event.key.code == sf::Keyboard::Up) {
						choice--;
						if (choice < 0)
							choice = 0;
					}
					if (event.key.code == sf::Keyboard::Down) {
						choice++;
						if (choice > 1)
							choice = 1;
					}
					if (event.key.code == sf::Keyboard::Enter) {
						player* Player_1 = new player(1, 100, 100, 0, 0);
						if (choice == 1) {
							player* Player_2 = new player(2, 100, 300, 0, 0);
						}
						scene = transition;
						choice = 0;
					}
					break;
				}
				case play:
				{
					if (event.key.code == sf::Keyboard::W) {
						up_1 = true;
					}
					if (event.key.code == sf::Keyboard::S) {
						down_1 = true;
					}
					if (event.key.code == sf::Keyboard::D) {
						shoot_1 = true;
					}
					if (event.key.code == sf::Keyboard::A) {
						if (player::getObjectPtr(player_obj + 1)->getBulletCount() >= 30) {
							player::getObjectPtr(player_obj + 1)->resetBulletCount();
						}
					}

					if (event.key.code == sf::Keyboard::Up) {
						up_2 = true;
					}
					if (event.key.code == sf::Keyboard::Down) {
						down_2 = true;
					}
					if (event.key.code == sf::Keyboard::Right) {
						shoot_2 = true;
					}
					if (event.key.code == sf::Keyboard::Left) {
						if (player::getObjectPtr(player_obj + 2)->getBulletCount() >= 30) {
							player::getObjectPtr(player_obj + 2)->resetBulletCount();
						}
					}

					
					if (event.key.code == sf::Keyboard::Space) {
						scene = pause;
					}
					break;
				}
				case pause:
				{
					if (event.key.code == sf::Keyboard::Up) {
						choice--;
						if (choice < 0)
							choice = 0;
					}
					if (event.key.code == sf::Keyboard::Down) {
						choice++;
						if (choice > 1)
							choice = 1;
					}
					if (event.key.code == sf::Keyboard::Enter) {
						if (choice == 0) {
							scene = play;
							clock.restart();
						}
						else if (choice == 1) {
							scene = start;
							level = 0;
							currentPoint = 0;
							choice = 0;
							enemy::clearObject();
							bullet::clearObject();
							player::clearObject();
						}
					}
					break;
				}
				case transition:
				{
					if (event.key.code == sf::Keyboard::Enter && level != -1) {
						level++;
						generateEnemy = true; shoot_1 = false; shoot_2 = false; up_1 = false; up_2 = false; down_1 = false; down_2 = false;
						scene = play;
						//Player->setPosition(100, 100);	Player->setVelocity(0.0f, 0.0f);
						//Player->setPlayerHp(100);		Player->resetBulletCount();
					}
					if (event.key.code == sf::Keyboard::R && (level == -1 || level == 3)) {
						level = 0; shoot_1 = false; shoot_2 = false; up_1 = false; up_2 = false; down_1 = false; down_2 = false;
						//Player->setPosition(100, 100);	Player->setVelocity(0.0f, 0.0f);
						//Player->setPlayerHp(100);		Player->resetBulletCount();
						currentPoint = 0;
						scene = start;
					}
					break;
				}
				}
				break;

			case sf::Event::KeyReleased:
				switch (scene) {
				case play:
				{
					if (event.key.code == sf::Keyboard::W) {
						up_1 = false;
					}
					if (event.key.code == sf::Keyboard::S) {
						down_1 = false;
					}
					if (event.key.code == sf::Keyboard::D) {
						shoot_1 = false;
					}
					if (event.key.code == sf::Keyboard::Up) {
						up_2 = false;
					}
					if (event.key.code == sf::Keyboard::Down) {
						down_2 = false;
					}
					if (event.key.code == sf::Keyboard::Right) {
						shoot_2 = false;
					}
					break;
				}
				}
				break;
			}
		}

		// draw the background and animation
		img::displayImage(window, img::texture::background, 0, 0, sf::Vector2f(window.getSize()));
		animate::monitoringAnimation(window);

		//outside pollEvent
		switch (scene) {
		case start:
		{
			std::vector<std::string> choices = { "START", "SETTINGS", "EXIT" };
			TextRenderer.displayText(window, "something is happening somewhere", 50, sf::Color::White, 100, 100);
			TextRenderer.displayMultipleChoice(window, choices, choice, 50, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 300);
			break;
		}

		case tutorial:
		{
			displayTutorial(window, TextRenderer.getFont(), stepTutorial);
			if (stepTutorial > 5)
			{
				scene = settings;
				stepTutorial = 1;
			}
			TextRenderer.displayText(window, "Press ENTER to continue", 30, sf::Color::White, 100, 600);
			break;
		}

		case settings:
		{
			std::string Cheat = (cheat) ? "Enabled" : "Disabled";
			std::vector<std::string> choices = { "BGM Volume : <" + std::to_string(bgmVolume) + "%>",
												 "SFX Volume : <" + std::to_string(sfxVolume) + "%>",
												 "Cheat : < " + Cheat + " >",
												 "Tutorial",
												 "Credit"};
			TextRenderer.displayText(window, "something is happening somewhere", 50, sf::Color::White, 100, 100);
			TextRenderer.displayMultipleChoice(window, choices, choice, 40, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 360);
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
			std::vector<std::string> choices = { "Singleplayer", "Multiplayer" };
			TextRenderer.displayText(window, "something is happening somewhere", 50, sf::Color::White, 100, 100);
			TextRenderer.displayText(window, "Choose your gamemode: ", 40, sf::Color::White, 100, window.getSize().y - 220);
			TextRenderer.displayMultipleChoice(window, choices, choice, 40, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 180);
			break;
		}

		case transition:
		{
			bullet::clearObject();
			enemy::clearObject();
			if(level == -1){ //lOSE
				TextRenderer.displayText(window, "YOU LOSE :(\nBETTER LUCK NEXT TIME", 40, sf::Color::White, 100, 100);
				TextRenderer.displayText(window, "Your last score is " + std::to_string(currentPoint), 40, sf::Color::White, 100, 200);
				TextRenderer.displayText(window, "Press 'R' to back to main menu", 40, sf::Color::White, 100, window.getSize().y - 60);
			}
			else if (level > 2) { //WIN
				TextRenderer.displayText(window, "CONGRATULATION :)\nYOU'RE THE WINNER", 40, sf::Color::White, 100, 100);
				TextRenderer.displayText(window, "Your final score is " + std::to_string(currentPoint), 40, sf::Color::White, 100, 200);
				TextRenderer.displayText(window, "Press 'R' to back to main menu", 40, sf::Color::White, 100, window.getSize().y - 60);
			}
			else { //NEXT LEVEL
				TextRenderer.displayText(window, "LEVEL " + std::to_string(level + 1), 40, sf::Color::Cyan, 100, 100);
				TextRenderer.displayText(window, "Press ENTER to continue", 30, sf::Color::White, 100, window.getSize().y - 60);
			}
			break;
		}

		case pause:
		{
			TextRenderer.displayText(window, "PAUSE", 40, sf::Color::White, 100, 100);

			std::vector<std::string> choices = { "Resume", "Rage quit" };
			TextRenderer.displayMultipleChoice(window, choices, choice, 40, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 320);
			break;
		}

		case play:
		{
			//FIRST PLAYER
			if (player::getObjectPtr(101) != NULL) {
				player* player_1 = player::getObjectPtr(101);
				if (up_1)
					player_1->thrustUp();
				if (down_1)
					player_1->thrustDown();
				if (shoot_1 && player_1->getBulletCount() <= 30)
					player_1->shoot(sfxVolume);
				if (player_1->getBulletCount() >= 30)
					TextRenderer.displayText(window, "player_1's bullet is empty", 30, sf::Color::White, 30, window.getSize().y - 60);

				if (clock_2.getElapsedTime().asSeconds() >= 5) {
					player_1->healPlayer(getRandomFloat(10, 20));
				}
			}

			//SECOND PLAYER
			if (player::getObjectPtr(102) != NULL) {
				player* player_2 = player::getObjectPtr(102);
				if (up_2)
					player_2->thrustUp();
				if (down_2)
					player_2->thrustDown();
				if (shoot_2 && player_2->getBulletCount() <= 30)
					player_2->shoot(sfxVolume);
				if (player_2->getBulletCount() >= 30)
					TextRenderer.displayText(window, "player_2's bullet is empty", 30, sf::Color::White, 850, 650);
				if (clock_2.getElapsedTime().asSeconds() >= 5) {
					player_2->healPlayer(getRandomFloat(10, 20));
				}
			}

			if (clock_2.getElapsedTime().asSeconds() >= 5)
				clock_2.restart();

			//pause the game if the window lost its focus
			if (!window.hasFocus()) {
				scene = pause;
			}


			//level mechanics and enemy object creation
			if (generateEnemy) {
				bullet::clearObject();
				clock.restart();
				float min = (window.getSize().x / 288 > window.getSize().y / 176) ? window.getSize().y / 176 : window.getSize().x / 288;
				float max = (window.getSize().x / 288 > window.getSize().y / 176) ? window.getSize().x / 288 : window.getSize().y / 176;
				switch (level) {
				case 1:
				{
					for (int i = 1; i < getRandomFloat(min, max); i++) {
						enemy* Enemy = new enemy(i, getRandomFloat(400, window.getSize().x), getRandomFloat(0, window.getSize().y), getRandomFloat(-0.3, 0.3), getRandomFloat(0.1, 0.3));
					}
					break;
				}
				case 2:
				{
					for (int i = 1; i < getRandomInteger(min + 2, max + 3 ); i++) {
						enemy* Enemy = new enemy(i, getRandomFloat(400, window.getSize().x), getRandomFloat(0, window.getSize().y), getRandomFloat(-0.6, 0.6), getRandomFloat(-0.6, 0.6));
					}
					break;
				}
				case 3:
				{
					for (int i = 1; i < getRandomInteger(min + 3, max + 5 ); i++) {
						enemy* Enemy = new enemy(i, getRandomFloat(400, window.getSize().x), getRandomFloat(0, window.getSize().y), getRandomFloat(-0.9, 0.9), getRandomFloat(-0.9, 0.9));
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
			currentPoint += processCollision();
			TextRenderer.displayText(window, "Score : " + std::to_string(currentPoint), 40, sf::Color::White, 30, 30);

			//update & draw
			double dt = clock.restart().asSeconds() * 1500;
			player::updateNDrawAllObject(dt, window);
			enemy::updateNDrawAllObject(dt, window);
			bullet::updateNDrawAllObject(dt, window);
			break;
		}
		}
		window.display();
		window.clear();
	}
	return 0;
}