#include <stdbool.h>
#include <iostream>
#include "SFML/Audio.hpp"

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "Text.h"
#include "func.h"
#include "Images.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);

	sf::Clock clock;
	sf::Event event;
	sf::Music bgmusic;
	bgmusic.openFromFile("audio/Boooring.ogg");
	bgmusic.play();
	bgmusic.setLoop(true);
	

	//texture initialization
	player::initializeTexture("images/player.png");
	bullet::initializeTexture("images/bullet.png");
	enemy::initializeTexture("images/enemy.png");
	text::fontInitialization("fonts/Poppins-SemiBold.ttf");
	img::initializeTexture();
	sounds::loadSound();
 
	// enumeration for scene changes
	enum part { start, settings , tutorial, transition, singleMulti, play, pause };
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
	float currentPoint = 0;			// as the name implies, to save the point calculation result
	bool generateEnemy = false;		// decides whether to generate new enemies

	// variables that'll be used in the start menu
	int scene = start;				// decide what scene is being run
	int choice = 0;					// variables that will later change the scene in the start menu
	int stepTutorial = 1;

	int bgmVolume = 50;
	int sfxVolume = 50;

	// main game loop
	while (window.isOpen()) {
		bgmusic.setVolume(bgmVolume);
		sounds::checkAndDeleteSound();
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
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
						stepTutorial += 2;
					}
					break;
				}
				case settings:
				{
					if (event.key.code == sf::Keyboard::Down) {
						choice++;
						if (choice > 3)
							choice = 3;
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
					}
					if (event.key.code == sf::Keyboard::Escape) {
						scene = start;
						choice = 0;
					}
					if (event.key.code == sf::Keyboard::Enter) {
						if (choice == 2)
							scene = tutorial;
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
						if (choice == 0) {
							player* Player = new player(1, 100, 100, 0, 0);
							Player->setPlayerHp(100);
						}
						if (choice == 1) {
							player* Player_1 = new player(1, 100, 100, 0, 0);
							Player_1->setPlayerHp(100);

							player* Player_2 = new player(2, 100, 300, 0, 0);
							Player_2->setPlayerHp(100);
						}
						scene = transition;
						choice = 0;
					}
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
					if (event.key.code == sf::Keyboard::Space) {
						scene = play;
						clock.restart();
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
		window.draw(img::background());

		//outside pollEvent
		switch (scene) {
		case start:
		{
			window.draw(text::gameTitle());
			window.draw(text::startMenuChoice(choice));
			break;
		}

		case tutorial:
		{
			if (stepTutorial < 9) {
				window.draw(img::keybLeft());
				window.draw(img::keybRight());
				window.draw(text::tutorialStep(stepTutorial));
				window.draw(text::tutorialStep(stepTutorial + 1));
			}
			if (stepTutorial == 9) {
				window.draw(img::spacebar());
				window.draw(text::tutorialStep(stepTutorial));
			}
			if (stepTutorial > 10)
			{
				scene = settings;
				stepTutorial = 1;
			}
			break;
		}

		case settings:
		{
			window.draw(text::gameTitle());
			window.draw(text::settingsChoice(choice, bgmVolume, sfxVolume));
			break;
		}

		case singleMulti:
		{
			window.draw(text::gameTitle());
			window.draw(text::singleMultiChoice(choice));
			break;
		}

		case transition:
		{
			switch (level) {
			case -1:
			{
				bullet::clearObject();
				enemy::clearObject();
				window.draw(text::lose());
				break;
			}
			case 0: window.draw(text::startLevel(1)); break;
			case 1: window.draw(text::startLevel(2)); break;
			case 2: window.draw(text::startLevel(3)); break;
			case 3: window.draw(text::win()); break;
			}
			break;
		}

		case pause:
		{
			window.draw(text::pauseText());
			break;
		}

		case play:
		{
			if (player::getObjectPtr(101) != NULL) {
				player* player_1 = player::getObjectPtr(101);
				player_1->drawHpBar(window, player_1->getPositionX() - player_1->getWidth() / 2, player_1->getPositionY() - player_1->getHeight() / 2 - 20, player_1->getWidth(), 10);
				if (up_1)
					player_1->thrustUp();
				if (down_1)
					player_1->thrustDown();
				if (shoot_1 && player_1->getBulletCount() <= 30)
					player_1->shoot(sfxVolume);
				if (player_1->getBulletCount() >= 30)
					window.draw(text::bulletEmpty(1));
			}

			if (player::getObjectPtr(102) != NULL) {
				player* player_2 = player::getObjectPtr(102);
				player_2->drawHpBar(window, player_2->getPositionX() - player_2->getWidth() / 2, player_2->getPositionY() - player_2->getHeight() / 2 - 20, player_2->getWidth(), 10);
				if (up_2)
					player_2->thrustUp();
				if (down_2)
					player_2->thrustDown();
				if (shoot_2 && player_2->getBulletCount() <= 30)
					player_2->shoot(sfxVolume);
				if (player_2->getBulletCount() >= 30)
					window.draw(text::bulletEmpty(2));
			}

			//pause the game if the window lost its focus
			if (!window.hasFocus()) {
				scene = pause;
			}


			//level mechanics and enemy object creation
			if (generateEnemy) {
				bullet::clearObject();
				clock.restart();
				switch (level) {
				case 1:
				{
					for (int i = 1; i < getRandomInteger(2, 4); i++) {
						enemy* Enemy = new enemy(i, getRandomFloat(400, 1280), getRandomFloat(0, 720), getRandomFloat(-0.3, 0.3), getRandomFloat(0.1, 0.3));
					}
					break;
				}
				case 2:
				{
					for (int i = 1; i < getRandomInteger(4, 7); i++) {
						enemy* Enemy = new enemy(i, getRandomFloat(400, 1280), getRandomFloat(0, 720), getRandomFloat(-0.6, 0.6), getRandomFloat(-0.6, 0.6));
					}
					break;
				}
				case 3:
				{
					for (int i = 1; i < getRandomInteger(7, 11); i++) {
						enemy* Enemy = new enemy(i, getRandomFloat(400, 1280), getRandomFloat(0, 720), getRandomFloat(-0.9, 0.9), getRandomFloat(-0.9, 0.9));
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

			//lose
			if (player::getPlayerMap()->empty()) {
				level = -1;
				scene = transition;
				break;
			}

			//update & draw
			double dt = clock.restart().asSeconds() * 1500;
			player::updateNDrawAllObject(dt, window);
			enemy::updateNDrawAllObject(dt, window);
			bullet::updateNDrawAllObject(dt, window);

			window.draw(text::score(currentPoint));
			break;
		}
		}
		window.display();
		window.clear(sf::Color(255, 255, 255));
	}
	return 0;
}