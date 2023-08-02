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
	sf::Event event;

	//create player
	objectsContainer::createObject("player", 100, 100, 60, 29, 0.0002f);
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
		if (levelUp) {
			window.clear(sf::Color(255, 255, 255));
			objectsContainer::clearObject();
			static int level = 0;
			level++;
			sf::Text confirm;
			confirm.setFont(font);
			confirm.setCharacterSize(100);
			confirm.setFillColor(sf::Color::Black);
			switch (level) {
			case 1:
				objectsContainer::createObject("enemy_1", 600, 100, 60, 29, 0.0002f); objectsContainer::show_object("enemy_1");
				objectsContainer::createObject("enemy_2", 600, 200, 60, 29, 0.0002f); objectsContainer::show_object("enemy_2");
				objectsContainer::createObject("enemy_3", 600, 300, 60, 29, 0.0002f); objectsContainer::show_object("enemy_3");
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
				objectsContainer::createObject("enemy_1", 500, 100, 60, 29, 0.0002f); objectsContainer::show_object("enemy_1");
				objectsContainer::createObject("enemy_2", 700, 100, 60, 29, 0.0002f); objectsContainer::show_object("enemy_2");
				objectsContainer::createObject("enemy_3", 500, 300, 60, 29, 0.0002f); objectsContainer::show_object("enemy_3");
				objectsContainer::createObject("enemy_4", 700, 300, 60, 29, 0.0002f); objectsContainer::show_object("enemy_4");
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
				confirm.setString("CONGRATULATION\nYOU ARE THE WINNER\npress 'r' to restart");
				window.draw(confirm);
				window.display();
				while (true) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
						level = 0;
						break;
					}
				}
				break;
			}
			window.clear(sf::Color(255, 255, 255));
			objectsContainer::get_object_player("player")->setPosition(100, 100);
			objectsContainer::get_object_player("player")->setVelocity(0, 0);
			levelUp = false;
		}
		
		if (objectsContainer::getEnemyMap()->empty()) {
			player* Player = objectsContainer::get_object_player("player");
			Player->resetBulletCount();
			levelUp = true;
		}
		
		//update & draw
		std::unordered_map<std::string, sf::RectangleShape*>* spritesMap = objectsContainer::getSpritesMap();
		double dt = clock.restart().asSeconds() * 1500;
		for (const auto& it : *spritesMap) {
			if (it.first.substr(0, 6) == "player") {
				player* Player = objectsContainer::get_object_player(it.first);
				objectsContainer::get_object_player(it.first)->update(dt);
				if (Player->getPositionY() >= 720 || Player->getPositionY() <= 0) {
					Player->setVelocity(Player->getVelocityX(),Player->getVelocityY() * -1);
				}
			}
			else if (it.first.substr(0, 6) == "bullet") {
				objectsContainer::get_object_bullet(it.first)->update(dt);
			}
			else if (it.first.substr(0, 5) == "enemy") {
				enemy* Enemy = objectsContainer::get_object_enemy(it.first);
				Enemy->update(dt);
				if (Enemy->getPositionY() >= 720) {
					Enemy->setVelocity(Enemy->getVelocityX(), Enemy->getVelocityY() * -1);
				}
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
			if (bullet_object->second->getPositionX()>=1280) {
				objectsContainer::unshow_object(bullet_object->first);
				objectsContainer::delete_object(bullet_object->first);
				bulletIntersects = true;
			}
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
					
					bullet_object = bulletMap->erase(bullet_object);
					goto skipIncrement;
				}
				else {
					++enemy_object;
				}
			}
			++bullet_object;
		skipIncrement:
			continue;
		}
	}
	return 0;
}