#include <string>
#include <iostream>
#include <vector>
#include <stdbool.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "objects.h"
#include <chrono>

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Clock clock_2;
	sf::Event event;

	//create player
	player* Player = new player("player", 100, 100, 60, 29, 0.0002f);
	Player->setPlayerHp(100);

	sf::Text bulletEmptyText;
	sf::Font font; font.loadFromFile("fonts/SAOUITT-Regular.ttf");
	bulletEmptyText.setString("The bullet is empty\nPress X to reload the bullet");
	bulletEmptyText.setFont(font);
	bulletEmptyText.setCharacterSize(100);
	bulletEmptyText.setFillColor(sf::Color::Black);
	bool gas = false; bool shoot = false; bool wait = false; int level = 0;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space) {
					gas = true;
				}
				if (event.key.code == sf::Keyboard::LShift) {
					shoot = true;
				}
				if (event.key.code == sf::Keyboard::X) {
					if (Player->getBulletCount() >= 30) {
						Player->resetBulletCount();
					}
				}
				if (event.key.code == sf::Keyboard::C && level != -1) {
					wait = false;
				}
				if (event.key.code == sf::Keyboard::R && level == -1) {
					level = 0;
					player* Player = player::getObjectPtr("player");
					Player->setPosition(100, 100);	Player->setVelocity(0.0f, 0.0f);
					Player->setPlayerHp(100);		Player->resetBulletCount();
					object::unhideObject("player", Player->getSprite());
					wait = false;
				}
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Space) {
					gas = false;
				}
				if (event.key.code == sf::Keyboard::LShift) {
					shoot = false;
				}
			}
		}

		//if wait is false
		if (!wait) {
			if (gas == true)
				Player->thrust();
			if (shoot == true && Player->getBulletCount() <= 30)
				Player->shoot();
			if (Player->getBulletCount() >= 30) {
				window.draw(bulletEmptyText);
			}

			//level mechanism
			if (enemy::getEnemyMap()->empty() || level == -1) {
				window.clear(sf::Color(255, 255, 255));
				level++;
				switch (level) {
				case 1:
				{
					enemy* enemy_1 = new enemy("enemy_1", 600, 100, 60, 29, 0.0f); enemy_1->setVelocity(0.2, 0.1);
					enemy* enemy_2 = new enemy("enemy_2", 600, 200, 60, 29, 0.0f); enemy_2->setVelocity(0.3, 0.1);
					enemy* enemy_3 = new enemy("enemy_3", 600, 300, 60, 29, 0.0f); enemy_3->setVelocity(0.3, 0.2);
					wait = true;
					break;
				}
				case 2:
				{
					enemy* enemy_1 = new enemy("enemy_1", 500, 100, 60, 29, 0.0f); enemy_1->setVelocity(0.2, 0.1);
					enemy* enemy_2 = new enemy("enemy_2", 700, 100, 60, 29, 0.0f); enemy_2->setVelocity(0.3, 0.4);
					enemy* enemy_3 = new enemy("enemy_3", 500, 300, 60, 29, 0.0f); enemy_3->setVelocity(0.1, 0.2);
					enemy* enemy_4 = new enemy("enemy_4", 700, 300, 60, 29, 0.0f); enemy_4->setVelocity(0.4, 0.3);
					wait = true;
					break;
				}
				default:
				{
					break;
				}
				}
			}

			//collision check & deletion
			std::unordered_map<std::string, bullet*>* bulletMap = bullet::getBulletMap();
			std::unordered_map<std::string, enemy*>* enemyMap = enemy::getEnemyMap();

			//check collision with the border border
			//for (auto bullet_object = bulletMap->begin(); bullet_object != bulletMap->end();) {
			//	bool bulletIntersects = false;
			//	if (bullet_object->second->getPositionX() >= 1280 || bullet_object->second->getPositionX() <= 0) {
			//		bullet::deleteObject(bullet_object->first);
			//		bulletIntersects = true;
			//	}

			//	//perform different increment method for different scenario
			//	if (bulletIntersects == true) {
			//		bullet_object = bulletMap->erase(bullet_object);
			//	}
			//	else if (bulletIntersects == false) {
			//		++bullet_object;
			//	}
			//}

			//check collision with the enemy object 
			for (auto bullet_object = bulletMap->begin(); bullet_object != bulletMap->end();) {
				bool somethingCollide = false;

				if (bullet_object->first.substr(7, 5) != "enemy") {
					for (auto enemy_object = enemyMap->begin(); enemy_object != enemyMap->end();) {
						if (object::isintersect(enemy_object->second->getSprite(), bullet_object->second->getSprite())) {
							float damage = bullet_object->second->getDamageValue();
							enemy_object->second->reduceHp(damage);
							std::cout << "enemy HP: " << enemy_object->second->getHp() << std::endl;
							std::cout << "bullet damage: " << damage << std::endl;
							bullet::deleteObject(bullet_object->first);
							if (enemy_object->second->getHp() <= 0) {
								enemy::deleteObject(enemy_object->first);
								enemy_object = enemyMap->erase(enemy_object);
							}
							else {
								++enemy_object;
							}
							//if the code reaches this part, it means that the object has been deleted,
							//so we need to move the iterator into the next object while remove it from the map
							bullet_object = bulletMap->erase(bullet_object);
							somethingCollide = true;
						}
						else {
							++enemy_object;
						}
					}
					if (bullet_object->second->getPositionX() >= 1000) {
						bullet::deleteObject(bullet_object->first);
						bullet_object = bulletMap->erase(bullet_object);
						somethingCollide = true;
					}
				}
				else if (bullet_object->first.substr(7, 5) == "enemy") {
					player* Player = player::getObjectPtr("player");
					if (object::isintersect(Player->getSprite(), bullet_object->second->getSprite())) {
						Player->reducePlayerHp(bullet_object->second->getDamageValue());
						std::cout << "player HP: " << Player->getPlayerHp() << std::endl;
						bullet::deleteObject(bullet_object->first);
						bullet_object = bulletMap->erase(bullet_object);
						if (Player->getPlayerHp() <= 0) {
							object::hideObject(Player->getId());
							level = -1;
							wait = true;
						}
						somethingCollide = true;
					}
					if (bullet_object->second->getPositionX() <= 0) {
						bullet::deleteObject(bullet_object->first);
						bullet_object = bulletMap->erase(bullet_object);
						somethingCollide = true;
					}
				}
				//if the code reaches this part, it means that no bullet has been collided, so it'll move the iterator normally using increment
				if(!somethingCollide)
					++bullet_object;
			}

			//update & draw
			std::unordered_map<std::string, sf::RectangleShape*>* spritesMap = object::getSpritesMap();
			double dt = clock.restart().asSeconds();
			dt *= 1500;
			for (const auto& it : *spritesMap) {
				if (it.first.substr(0, 6) == "player") {
					player* Player = player::getObjectPtr(it.first);
					Player->update(dt);
					if (Player->getPositionY() >= 720 || Player->getPositionY() <= 0)
						Player->setVelocity(Player->getVelocityX(), Player->getVelocityY() * -1);

					if (Player->getPositionY() >= 720)
						Player->setPosition(Player->getPositionX(), 720);
					else if (Player->getPositionY() <= 0)
						Player->setPosition(Player->getPositionX(), 0);
				}
				else if (it.first.substr(0, 6) == "bullet") {
					bullet* Bullet = bullet::getObjectPtr(it.first);
					Bullet->update(dt);
				}
				else if (it.first.substr(0, 5) == "enemy") {
					enemy* Enemy = enemy::getObjectPtr(it.first);
					Enemy->update(dt);
					if (Enemy->getPositionY() >= 720 || Enemy->getPositionY() <= 0) {
						Enemy->setVelocity(Enemy->getVelocityX(), Enemy->getVelocityY() * -1);
						if (Enemy->getPositionY() >= 720)
							Enemy->setPosition(Enemy->getPositionX(), 720);
						else if (Enemy->getPositionY() <= 0)
							Enemy->setPosition(Enemy->getPositionX(), 0);
					}
					if (Enemy->getPositionX() >= 1280 || Enemy->getPositionX() <= 400) {
						Enemy->setVelocity(Enemy->getVelocityX() * -1, Enemy->getVelocityY());
						if (Enemy->getPositionX() <= 400)
							Enemy->setPosition(400, Enemy->getPositionY());
						else if (Enemy->getPositionX() >= 1280)
							Enemy->setPosition(1280, Enemy->getPositionY());
					}

					float elapsed = clock_2.getElapsedTime().asSeconds();
					if (elapsed > 5 && elapsed < 5.03) {
						Enemy->shoot();
					}
					if (elapsed > 5.1)
						clock_2.restart();
				}
				sf::RectangleShape* sprite = it.second;
				window.draw(*sprite);
			}
		}

		else {
			sf::Text confirm;
			confirm.setFont(font);
			confirm.setCharacterSize(100);
			confirm.setFillColor(sf::Color::Black);

			switch (level) {
			case -1:
			{
				bullet::clearObject();
				enemy::clearObject();
				confirm.setString("YOU LOSE\nBETTER LUCK NEXT TIME\npress 'r' to restart"); break; 
			}
			case 1:	confirm.setString("LEVEL 1\nDO YOU READY\npress 'c' to continue"); break;
			case 2: confirm.setString("LEVEL 2\nDO YOU READY?\npress 'c' to continue"); break;
			default:confirm.setString("IDK\nF U");
			}
			window.draw(confirm);
		}
		window.display();
		window.clear(sf::Color(255, 255, 255));
	}
	return 0;
}