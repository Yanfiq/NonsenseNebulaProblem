#include <string>
#include <iostream>
#include <vector>
#include <stdbool.h>
#include "objectsContainer.h"
#include <chrono>

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Clock clock_2;
	sf::Event event;

	//create player
	objectsContainer::createObject("player", 100, 100, 60, 29, 0.0002f);
	objectsContainer::get_object_player("player")->setPlayerHp(100);
	objectsContainer::show_object("player");

	sf::Text text;
	sf::Font font; font.loadFromFile("fonts/SAOUITT-Regular.ttf");
	text.setString("The bullet is empty\nPress X to reload the bullet");
	text.setFont(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Black);
	bool bulletEmpty = false;

	while (window.isOpen()) {
		bool gas = false;
		static bool levelUp = false;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space) {
					//objectsContainer::get_object_player("player")->thrust();
					gas = true;
				}
				if (event.key.code == sf::Keyboard::LShift) {
					if (objectsContainer::get_object_player("player")->getBulletCount() <= 30) {
						bullet* Bullet = objectsContainer::get_object_player("player")->shoot();
						objectsContainer::assign_bullet(Bullet->getId(), Bullet);
						objectsContainer::show_object(Bullet->getId());
					}
					if (objectsContainer::get_object_player("player")->getBulletCount() >= 30) {
						bulletEmpty = true;
					}
				}
				if (event.key.code == sf::Keyboard::X) {
					if (bulletEmpty == true) {
						objectsContainer::get_object_player("player")->resetBulletCount();
						bulletEmpty = false;
					}
				}
			}
		}

		if (gas == true) {
			objectsContainer::get_object_player("player")->thrust();
		}
		if (bulletEmpty == true) {
			window.draw(text);
		}

		//level mechanism
		static int level = 0;
		if (levelUp) {
			window.clear(sf::Color(255, 255, 255));
			objectsContainer::clearObject();
			level++;
			sf::Text confirm;
			confirm.setFont(font);
			confirm.setCharacterSize(100);
			confirm.setFillColor(sf::Color::Black);
			switch (level) {
			case 1:
				objectsContainer::createObject("enemy_1", 600, 100, 60, 29, 0.0f); objectsContainer::show_object("enemy_1"); objectsContainer::get_object_enemy("enemy_1")->setVelocity(0.2, 0.1);
				objectsContainer::createObject("enemy_2", 600, 200, 60, 29, 0.0f); objectsContainer::show_object("enemy_2"); objectsContainer::get_object_enemy("enemy_2")->setVelocity(0.3, 0.1);
				objectsContainer::createObject("enemy_3", 600, 300, 60, 29, 0.0f); objectsContainer::show_object("enemy_3"); objectsContainer::get_object_enemy("enemy_3")->setVelocity(0.3, 0.2);
				confirm.setString("LEVEL 1\nDO YOU READY\npress 'c' to continue");
				window.draw(confirm);
				window.display();
				while (true) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
						break;
					}
				}
				break;
			case 2:
				objectsContainer::createObject("enemy_1", 500, 100, 60, 29, 0.0f); objectsContainer::show_object("enemy_1"); objectsContainer::get_object_enemy("enemy_1")->setVelocity(0.2, 0.1);
				objectsContainer::createObject("enemy_2", 700, 100, 60, 29, 0.0f); objectsContainer::show_object("enemy_2"); objectsContainer::get_object_enemy("enemy_2")->setVelocity(0.3, 0.4);
				objectsContainer::createObject("enemy_3", 500, 300, 60, 29, 0.0f); objectsContainer::show_object("enemy_3"); objectsContainer::get_object_enemy("enemy_3")->setVelocity(0.1, 0.2);
				objectsContainer::createObject("enemy_4", 700, 300, 60, 29, 0.0f); objectsContainer::show_object("enemy_4"); objectsContainer::get_object_enemy("enemy_4")->setVelocity(0.4, 0.3);
				confirm.setString("LEVEL 2\nDO YOU READY?\npress 'c' to continue");
				window.draw(confirm);
				window.display();
				while (true) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
						break;
					}
				}
				break;
			default:
				confirm.setString("YOU LOSE\nBETTER LUCK NEXT TIME\npress 'r' to restart");
				window.draw(confirm);
				window.display();
				while (true) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
						level = 0;
						objectsContainer::show_object("player");
						goto restart;
						break;
					}
				}
				break;
			}
			window.clear(sf::Color(255, 255, 255));
			levelUp = false;
		restart:
			objectsContainer::get_object_player("player")->setPosition(100, 100);
			objectsContainer::get_object_player("player")->setVelocity(0, 0);
			objectsContainer::get_object_player("player")->setPlayerHp(100);
			objectsContainer::get_object_player("player")->resetBulletCount();
			continue;
		}
		
		if (objectsContainer::getEnemyMap()->empty()) {
			player* Player = objectsContainer::get_object_player("player");
			Player->resetBulletCount();
			levelUp = true;
		}
		
		//update & draw
		std::unordered_map<std::string, sf::RectangleShape*>* spritesMap = objectsContainer::getSpritesMap();
		double dt = clock.restart().asSeconds();
		dt *= 1500;
		for (const auto& it : *spritesMap) {
			if (it.first.substr(0, 6) == "player") {
				player* Player = objectsContainer::get_object_player(it.first);
				objectsContainer::get_object_player(it.first)->update(dt);
				if (Player->getPositionY() >= 720 || Player->getPositionY() <= 0)
					Player->setVelocity(Player->getVelocityX(),Player->getVelocityY() * -1);

				if (Player->getPositionY() >= 720)
					Player->setPosition(Player->getPositionX(), 720);
				else if(Player->getPositionY() <= 0)
					Player->setPosition(Player->getPositionX(), 0);
			}
			else if (it.first.substr(0, 6) == "bullet") {
				objectsContainer::get_object_bullet(it.first)->update(dt);
				bullet* Bullet = objectsContainer::get_object_bullet(it.first);
			}
			else if (it.first.substr(0, 5) == "enemy") {
				enemy* Enemy = objectsContainer::get_object_enemy(it.first);
				Enemy->update(dt);
				if (Enemy->getPositionY() >= 720 || Enemy->getPositionY() <= 0) {
					Enemy->setVelocity(Enemy->getVelocityX(), Enemy->getVelocityY() * -1);
					if(Enemy->getPositionY() >= 720)
						Enemy->setPosition(Enemy->getPositionX(), 720);
					else if(Enemy->getPositionY() <= 0)
						Enemy->setPosition(Enemy->getPositionX(), 0);
				}
				if (Enemy->getPositionX() >=1280 || Enemy->getPositionX() <=400) {
					Enemy->setVelocity(Enemy->getVelocityX() * -1, Enemy->getVelocityY());
					if(Enemy->getPositionX() <= 400)
						Enemy->setPosition(400, Enemy->getPositionY());
					else if(Enemy->getPositionX() >= 1280)
						Enemy->setPosition(1280, Enemy->getPositionY());
				}

				float elapsed = clock_2.getElapsedTime().asSeconds();
				if (elapsed > 5 && elapsed < 5.03) {
					bullet* Bullet = Enemy->shoot();
					objectsContainer::assign_bullet(Bullet->getId(), Bullet);
					objectsContainer::show_object(Bullet->getId());
				}
				if (elapsed > 5.1)
					clock_2.restart();
			}
			sf::RectangleShape* sprite = it.second;
			window.draw(*sprite);
		}
		window.display();
		window.clear(sf::Color(255, 255, 255));

		//collision check & deletion
		std::unordered_map<std::string, bullet*>* bulletMap = objectsContainer::getBulletMap();
		std::unordered_map<std::string, enemy*>* enemyMap = objectsContainer::getEnemyMap();

		//check collision with the right border
		for (auto bullet_object = bulletMap->begin(); bullet_object != bulletMap->end();) {
			bool bulletIntersects = false;
			if (bullet_object->second->getPositionX() >= 1280 || bullet_object->second->getPositionX() <= 0) {
				objectsContainer::unshow_object(bullet_object->first);
				objectsContainer::delete_object(bullet_object->first);
				bulletIntersects = true;
			}

			//perform different increment method for different scenario
			if (bulletIntersects == true) {
				bullet_object = bulletMap->erase(bullet_object);
			}
			else if (bulletIntersects == false) {
				++bullet_object;
			}
		}

		//check collision with the enemy object 
		for (auto bullet_object = bulletMap->begin(); bullet_object != bulletMap->end();) {
			bool skipBulletIncrement = false;
			if (bullet_object->first.substr(7, 5) != "enemy") {
				for (auto enemy_object = enemyMap->begin(); enemy_object != enemyMap->end();) {
					if (objectsContainer::isintersect(enemy_object->second->getSprite(), bullet_object->second->getSprite())) {
						float damage = bullet_object->second->getDamageValue();
						enemy_object->second->reduceHp(damage);
						std::cout << "enemy HP: " << enemy_object->second->getHp() << std::endl;
						std::cout << "bullet damage: " << damage << std::endl;
						objectsContainer::unshow_object(bullet_object->first);
						objectsContainer::delete_object(bullet_object->first);
						if (enemy_object->second->getHp() <= 0) {
							objectsContainer::unshow_object(enemy_object->first);
							objectsContainer::delete_object(enemy_object->first);
							enemy_object = enemyMap->erase(enemy_object);
						}
						else {
							++enemy_object;
						}
						//if the code reaches this part, it means that the object has been deleted,
						//so we need to move the iterator into the next object while remove it from the map
						bullet_object = bulletMap->erase(bullet_object);
						goto skipIncrement;
					}
					else {
						++enemy_object;
					}
				}
			}
			else if (bullet_object->first.substr(7, 5) == "enemy") {
				player* Player = objectsContainer::get_object_player("player");
				if (objectsContainer::isintersect(Player->getSprite(), bullet_object->second->getSprite())) {
					Player->reducePlayerHp(bullet_object->second->getDamageValue());
					std::cout << "player HP: " << Player->getPlayerHp() << std::endl;
					if (Player->getPlayerHp() <= 0) {
						objectsContainer::unshow_object(Player->getId());
						level = -1;
						levelUp = true;
					}
				}
			}
			//if the code reaches this part, it means that no bullet has been collided, so it'll move the iterator normally using increment
			++bullet_object;
		skipIncrement:
			continue;
		}
	}
	return 0;
}