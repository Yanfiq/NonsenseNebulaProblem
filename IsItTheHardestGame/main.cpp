#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <stdbool.h>
#include "objectsContainer.h"
#include <chrono>

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//create player
	objectsContainer::createObject("player", 100, 100, 60, 29, 0.0002f);
	objectsContainer::show_object("player");

	//border
	objectsContainer::createObject("up", 0, 0, 1280, 1, 0);
	objectsContainer::show_object("up");

	objectsContainer::createObject("down", 0, 720, 1280, 1, 0);
	objectsContainer::show_object("down");

	objectsContainer::createObject("left", 0, 0, 1, 720, 0);
	objectsContainer::show_object("left");

	objectsContainer::createObject("right", 1000, 0, 1, 720, 0);
	objectsContainer::show_object("right");

	//enemy
	objectsContainer::createObject("enemy_1", 600, 100, 60, 90, 0.0002f);
	objectsContainer::show_object("enemy_1");

	sf::Text text;
	sf::Font font; font.loadFromFile("fonts/SAOUITT-Regular.ttf");
	text.setString("The bullet is empty\nPress X to reload the bullet");
	text.setFont(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Black);
	bool bulletEmpty = false;

	while (window.isOpen()) {
		/*auto start = std::chrono::high_resolution_clock::now();*/
		bool gas = false;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space) {
					gas = true;
				}
				if (event.key.code == sf::Keyboard::LShift && objectsContainer::get_object_player("player")->getBulletCount() <= 30) {
					object* Object = objectsContainer::get_object_player("player")->shoot();
					objectsContainer::assign_object(Object->getId(), Object);
					objectsContainer::show_object(Object->getId());
					if (objectsContainer::get_object_player("player")->getBulletCount() >= 30) {
						bulletEmpty = true;
					}
				}
				if (event.key.code == sf::Keyboard::X && bulletEmpty == true) {
					objectsContainer::get_object_player("player")->resetBulletCount();
					bulletEmpty = false;
				}
			}
		}

		if (gas == true) {
			objectsContainer::get_object_player("player")->thrust();
		}
		if (bulletEmpty == true) {
			window.draw(text);
		}
		
		//Reflection
		player* Player = objectsContainer::get_object_player("player");
		if (objectsContainer::isintersect(Player->getSprite(), objectsContainer::get_another_object("down")->getSprite())) {
			float velocityY = Player->getVelocityY();
			Player->setVelocity(Player->getVelocityX(), velocityY * (-1));
		}
		
		//update & draw
		std::unordered_map<std::string, sf::RectangleShape*>* spritesMap = objectsContainer::getSpritesMap();
		for (const auto& it : *spritesMap) {
			if (it.first.substr(0, 6) == "player") {
				objectsContainer::get_object_player(it.first)->update(0.7);
			}
			else if (it.first.substr(0, 6) == "bullet") {
				objectsContainer::get_object_bullet(it.first)->update(0.7);
			}
			sf::RectangleShape* sprite = it.second;
			window.draw(*sprite);

			//testing using the old code
			//if (it.first.substr(0, 6) == "bullet") {
			//	if (objectsContainer::isintersect(it.second, objectsContainer::get_another_object("right")->getSprite())) {
			//		objectsContainer::delete_object(it.first);
			//		objectsContainer::unshow_object(it.first);
			//	}
			//}
		}
		window.display();
		window.clear(sf::Color(255, 255, 255));

		//collision check & deletion
		std::unordered_map<std::string, bullet*>* bulletMap = objectsContainer::getBulletMap();
		std::unordered_map<std::string, enemy*>* enemyMap = objectsContainer::getEnemyMap();
		std::queue<std::string> willBeDeleted;

		for (auto bullet_object = bulletMap->begin(); bullet_object != bulletMap->end();) {
			//check collision with the enemy object
			//for (const auto& enemy_object : *enemyMap) {
			//	if (objectsContainer::isintersect(enemy_object.second->getSprite(), bullet_object.second->getSprite())) {
			//		willBeDeleted.push(enemy_object.first);
			//		willBeDeleted.push(bullet_object.first);
			//	}
			//}

			//check collision with the right border
			if (objectsContainer::isintersect(bullet_object->second->getSprite(), objectsContainer::get_another_object("right")->getSprite())) {
				//willBeDeleted.push(bullet_object->first);
				objectsContainer::unshow_object(bullet_object->first);
				objectsContainer::delete_object(bullet_object->first);
				bullet_object = bulletMap->erase(bullet_object);
			}
			else if(!enemyMap->empty()){
				for (auto enemy_object = enemyMap->begin(); enemy_object != enemyMap->end();) {
					if (objectsContainer::isintersect(enemy_object->second->getSprite(), bullet_object->second->getSprite())) {
						objectsContainer::unshow_object(enemy_object->first);
						objectsContainer::unshow_object(bullet_object->first);
						objectsContainer::delete_object(bullet_object->first);
						enemy_object = enemyMap->erase(enemy_object);
						bullet_object = bulletMap->erase(bullet_object);
					}
					else {
						++enemy_object;
						++bullet_object;
					}
				}
			}
			else {
				++bullet_object;
			}
		}

		//while (!willBeDeleted.empty()) {
		//	objectsContainer::unshow_object(willBeDeleted.front());
		//	objectsContainer::delete_object(willBeDeleted.front());
		//	willBeDeleted.pop();
		//}
	}
	return 0;
}