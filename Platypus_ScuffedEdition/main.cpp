#include <string>
#include <iostream>
#include <set>
#include <stdbool.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "objects.h"
#include "messages.h"
#include "func.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Event event;

	// player object creation
	player* Player = new player("player", 100, 100, 60, 29, 0.0002f);
	Player->setPlayerHp(100);
 
	// enumeration for scene changes
	enum part { start, tutorial, transition, play };

	// variables that'll be used inside the main game
	bool gas = false;				// decides when the player object will reduce its velocityY value
	bool shoot = false;				// decides when the player object will execute the shoot() function
	int level = 0;					// as the name implies, to differentiate levels
	float currentPoint = 0;			// as the name implies, to save the point calculation result
	bool generateEnemy = false;		// decides whether to generate new enemies

	// variables that'll be used in the start menu
	int scene = start;				// decide what scene is being run
	int choice = 0;					// variables that will later change the scene in the start menu
	int stepTutorial = 1;			// saves the tutorial step that is being described

	// main game loop
	while (window.isOpen()) {
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
						if (choice == 0)
							scene = transition;
						if (choice == 1)
							scene = tutorial;
						if (choice == 2)
							window.close();
					}
					break;
				}
				case tutorial:
				{
					if (event.key.code == sf::Keyboard::Enter) {
						stepTutorial++;
					}
				}
				case play:
				{
					if (event.key.code == sf::Keyboard::Z) {
						gas = true;
					}
					if (event.key.code == sf::Keyboard::X) {
						shoot = true;
					}
					if (event.key.code == sf::Keyboard::C) {
						if (Player->getBulletCount() >= 30) {
							Player->resetBulletCount();
						}
					}
					break;
				}
				case transition:
				{
					if (event.key.code == sf::Keyboard::Enter && level != -1) {
						level++;
						generateEnemy = true; shoot = false; gas = false;
						scene = play;
						Player->setPosition(100, 100);	Player->setVelocity(0.0f, 0.0f);
						Player->setPlayerHp(100);		Player->resetBulletCount();
					}
					if (event.key.code == sf::Keyboard::R && (level == -1 || level == 2)) {
						level = 0; shoot = false; gas = false;
						Player->setPosition(100, 100);	Player->setVelocity(0.0f, 0.0f);
						Player->setPlayerHp(100);		Player->resetBulletCount();
						object::unhideObject("player", Player->getSprite());
						currentPoint = 0;
						scene = play;
					}
					break;
				}
				}
				break;

			case sf::Event::KeyReleased:
				switch (scene) {
				case play:
				{
					if (event.key.code == sf::Keyboard::Z)
						gas = false;
					if (event.key.code == sf::Keyboard::X)
						shoot = false;
					break;
				}
				}
				break;
			}
		}

		//outside pollEvent
		switch (scene) {
		case start:
		{
			window.draw(text::startMenuChoice(choice));
			break;
		}

		case tutorial:
		{
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(960, 540));
			rectangle.setPosition(100, 100);
			sf::Texture tutorial;
			tutorial.loadFromFile("images/keyboardNjirr.jpg");
			rectangle.setTexture(&tutorial);
			window.draw(rectangle);

			window.draw(text::tutorialStep(stepTutorial));

			if (stepTutorial == 4)
			{
				scene = start;
				stepTutorial = 1;
			}
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
			case 2: window.draw(text::win()); break;
			}
			break;
		}

		case play:
		{
			if (gas == true)
				Player->thrust();
			if (shoot == true && Player->getBulletCount() <= 30)
				Player->shoot();
			if (Player->getBulletCount() >= 30) {
				window.draw(text::bulletEmpty());
			}

			//level mechanics and enemy object creation
			if (generateEnemy) {
				bullet::clearObject();
				switch (level) {
				case 1:
				{
					for (int i = 1; i < getRandomInteger(2, 4); i++) {
						std::string id = "enemy_" + std::to_string(i);
						enemy* Enemy = new enemy(id, getRandomInteger(400, 1280), getRandomInteger(0, 720), 60, 29, 0.0f);
						Enemy->setVelocity(getRandomFloat(-0.3, 0.3), getRandomFloat(0.1, 0.3));
					}
					break;
				}
				case 2:
				{
					for (int i = 1; i < getRandomInteger(4, 8); i++) {
						std::string id = "enemy_" + std::to_string(i);
						enemy* Enemy = new enemy(id, getRandomInteger(400, 1280), getRandomInteger(0, 720), 60, 29, 0.0f);
						Enemy->setVelocity(getRandomFloat(-0.6, 0.6), getRandomFloat(-0.6, 0.6));
					}
					break;
				}
				}

				generateEnemy = false;
				break;
			}
			if (enemy::getEnemyMap()->empty()) {
				scene = transition;
				break;
			}

			//collision detection and object removal
			std::map<std::string, std::string> objectCollide = getCollisionData();

			//object removal
			for (const auto& it : objectCollide) {
				if (it.first.substr(0, 6) == "bullet") {
					bullet::deleteObject(it.first);
				}
				else if (it.first.substr(0, 5) == "enemy"){
					enemy* Enemy = enemy::getObjectPtr(it.first);
					bullet* Bullet = bullet::getObjectPtr(it.second);
					Enemy->reduceHp(Bullet->getDamageValue());
					currentPoint += Bullet->getDamageValue();
					if (Enemy->getHp() <= 0)
						enemy::deleteObject(it.first);
					bullet::deleteObject(it.second);
				}
				else if (it.first.substr(0, 6) == "player") {
					player* Player = player::getObjectPtr(it.first);
					bullet* Bullet = bullet::getObjectPtr(it.second);
					Player->reducePlayerHp(Bullet->getDamageValue());
					currentPoint -= Bullet->getDamageValue();
					if (Player->getPlayerHp() <= 0)
					{
						level = -1;
						scene = transition;
					}
					bullet::deleteObject(it.second);
				}
			}

			//enemy's attack algorithm
			std::unordered_map<std::string, enemy*>* enemyMap = enemy::getEnemyMap();
			for (auto enemy_object = enemyMap->begin(); enemy_object != enemyMap->end(); enemy_object++) {
				enemy* Enemy = enemy_object->second;
				if ((Enemy->getPositionY() < Player->getPositionY() + 5) &&
					(Enemy->getPositionY() > Player->getPositionY() - 5)) {
					Enemy->shoot();
				}
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