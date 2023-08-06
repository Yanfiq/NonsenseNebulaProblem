#include <string>
#include <iostream>
#include <set>
#include <cmath>
#include <stdbool.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "objects.h"
#include "messages.h"

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
						generateEnemy = true;
						scene = play;
						Player->setPosition(100, 100);	Player->setVelocity(0.0f, 0.0f);
						Player->setPlayerHp(100);		Player->resetBulletCount();
					}
					if (event.key.code == sf::Keyboard::R && level == -1) {
						level = 0;
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
				if (event.key.code == sf::Keyboard::Z)
					gas = false;
				if (event.key.code == sf::Keyboard::X)
					shoot = false;
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
					enemy* enemy_1 = new enemy("enemy_1", 600, 100, 60, 29, 0.0f); enemy_1->setVelocity(0.2, 0.1);
					enemy* enemy_2 = new enemy("enemy_2", 600, 200, 60, 29, 0.0f); enemy_2->setVelocity(0.3, 0.1);
					enemy* enemy_3 = new enemy("enemy_3", 600, 300, 60, 29, 0.0f); enemy_3->setVelocity(0.3, 0.2);
					break;
				}
				case 2:
				{
					enemy* enemy_1 = new enemy("enemy_1", 500, 100, 60, 29, 0.0f); enemy_1->setVelocity(0.2, 0.1);
					enemy* enemy_2 = new enemy("enemy_2", 700, 100, 60, 29, 0.0f); enemy_2->setVelocity(0.3, 0.4);
					enemy* enemy_3 = new enemy("enemy_3", 500, 300, 60, 29, 0.0f); enemy_3->setVelocity(0.1, 0.2);
					enemy* enemy_4 = new enemy("enemy_4", 700, 300, 60, 29, 0.0f); enemy_4->setVelocity(0.4, 0.3);
					enemy* enemy_5 = new enemy("enemy_5", 600, 200, 60, 29, 0.0f); enemy_5->setVelocity(0.4, 0.5);
					enemy* enemy_6 = new enemy("enemy_6", 600, 200, 60, 29, 0.0f); enemy_6->setVelocity(0.5, 0.2);
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
			std::unordered_map<std::string, bullet*>* bulletMap = bullet::getBulletMap();
			std::unordered_map<std::string, enemy*>* enemyMap = enemy::getEnemyMap();
			std::set<std::string> willBeDeleted;
			for (auto bullet_object = bulletMap->begin(); bullet_object != bulletMap->end(); bullet_object++) {
				//bullets from the player
				if (bullet_object->second->getVelocityX() > 0) {
					for (auto enemy_object = enemyMap->begin(); enemy_object != enemyMap->end(); enemy_object++) {
						if (object::isintersect(enemy_object->second->getSprite(), bullet_object->second->getSprite())) {

							//reduce the enemy HP & adding point
							float damage = bullet_object->second->getDamageValue();
							enemy_object->second->reduceHp(damage);
							currentPoint += damage;

							//add the bullet's id to the vector
							if (willBeDeleted.find(bullet_object->first) == willBeDeleted.end())
								willBeDeleted.insert(bullet_object->first);

							//add the enemy's id to the vector if the HP's is zeroed
							if (enemy_object->second->getHp() <= 0 && willBeDeleted.find(enemy_object->first) == willBeDeleted.end()) {
								willBeDeleted.insert(enemy_object->first);
							}
						}
					}
					if ((bullet_object->second->getPositionX() >= 1280) &&
						(willBeDeleted.find(bullet_object->first) == willBeDeleted.end())) {
						//add the bullet's id to the vector
						willBeDeleted.insert(bullet_object->first);
					}
				}

				//bullets from the enemy
				else if (bullet_object->second->getVelocityX() < 0) {
					player* Player = player::getObjectPtr("player");
					if (object::isintersect(Player->getSprite(), bullet_object->second->getSprite())) {

						//reduce player's HP
						float damage = bullet_object->second->getDamageValue();
						Player->reducePlayerHp(damage);
						currentPoint -= damage;

						//add the bullet's id to the vector
						if (willBeDeleted.find(bullet_object->first) == willBeDeleted.end())
							willBeDeleted.insert(bullet_object->first);

						//game over
						if (Player->getPlayerHp() <= 0) {
							object::hideObject(Player->getId());
							level = -1;
							scene = transition;
							break;
						}
					}
					if (bullet_object->second->getPositionX() <= 0 && willBeDeleted.find(bullet_object->first) == willBeDeleted.end()) {
						//add the bullet's id to the vector
						willBeDeleted.insert(bullet_object->first);
					}
				}
			}

			//object removal
			for (const auto& it : willBeDeleted) {
				if (it.substr(0, 6) == "bullet") {
					bullet::deleteObject(it);
				}
				else if (it.substr(0, 5) == "enemy")
					enemy::deleteObject(it);
			}
			willBeDeleted.clear();

			//enemy's attack algorithm
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