#include <string>
//#include <iomanip>
//#include <iostream>
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
		window.clear(sf::Color(255, 255, 255));

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
					//player* Player = objectsContainer::get_object_player("player");
					//std::string bullet_id = "bullet_" + std::to_string(Player->getBulletCount());
					//objectsContainer::createObject(bullet_id, Player->getPositionX(), Player->getPositionY(), 20, 20, 0);
					//objectsContainer::get_object_bullet(bullet_id)->setVelocity(0.5, 0);
					//objectsContainer::show_object(bullet_id);
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

		//auto stop = std::chrono::high_resolution_clock::now();
		//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		//double deltaTime = duration.count();
		//std::cout << std::fixed << std::setprecision(3) << deltaTime << std::endl;
		//update & draw
		std::unordered_map<std::string, sf::RectangleShape*> spritesMap = objectsContainer::getSpritesMap();
		for (const auto& it : spritesMap) {
			if (it.first.substr(0, 6) == "player") {
				objectsContainer::get_object_player(it.first)->update(0.7);
			}
			else if (it.first.substr(0, 6) == "bullet") {
				objectsContainer::get_object_bullet(it.first)->update(0.7);
			}
			sf::RectangleShape *sprite = it.second;
			window.draw(*sprite);
			if (it.first.substr(0, 6) == "bullet" && objectsContainer::isintersect(it.second, objectsContainer::get_another_object("right")->getSprite())) {
				objectsContainer::delete_object(it.first);
				objectsContainer::unshow_object(it.first);
			}
		}
		window.display();
	}
	return 0;
}