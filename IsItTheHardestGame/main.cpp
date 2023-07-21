#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
#include <stdbool.h>
#include "objects.h"

std::unordered_map <std::string, object*> objects;
std::unordered_map <std::string, object*> bullets_object;
std::unordered_map<std::string, sf::RectangleShape*> spritesThatWillBeDrawn;

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//create player
	object* Plane = new object("player", 100, 100, 60, 29, 0.0002);
	objects["player"] = Plane;
	spritesThatWillBeDrawn["player"] = Plane->getSprite();

	//bullet counter
	static int bulletCount = 1;

	//border
	object* up = new object("up", 0, 0, 1280, 1, 0); objects[up->getId()] = up;
	spritesThatWillBeDrawn["up"] = up->getSprite();
	object* down = new object("down", 0, 720, 1280, 1, 0); objects[down->getId()] = down;
	spritesThatWillBeDrawn["down"] = down->getSprite();
	object* left = new object("left", 0, 0, 1, 720, 0); objects[left->getId()] = left;
	spritesThatWillBeDrawn["left"] = left->getSprite();
	object* right = new object("right", 1000, 0, 1, 720, 0); objects[right->getId()] = right;
	spritesThatWillBeDrawn["right"] = right->getSprite();

	while (window.isOpen()) {
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
				if (event.key.code == sf::Keyboard::LShift) {
					std::string bullet_id = "bullet_" + std::to_string(bulletCount);
					bulletCount++;
					object* bullet = new object(bullet_id, objects["player"]->getPositionX(), objects["player"]->getPositionY(), 20, 20, 0);
					bullet->setVelocity(0.5, 0);
					bullets_object[bullet_id] = bullet;
					spritesThatWillBeDrawn[bullet_id] = bullet->getSprite();
				}
			}
		}

		if (gas == true) {
			Plane->thrust();
		}

		object* Player = objects["player"];
		if (Player->getSprite()->getGlobalBounds().intersects(objects["up"]->getSprite()->getGlobalBounds()) || Player->getSprite()->getGlobalBounds().intersects(objects["down"]->getSprite()->getGlobalBounds())) {
			float velocityY = Player->getVelocityY();
			if (velocityY < 0) {
				Player->setVelocity(Player->getVelocityX(), velocityY * (-1));
			}
			else if (velocityY >= 0) {
				Player->setVelocity(Player->getVelocityX(), velocityY * (-1));
			}
		}
		if (Player->getSprite()->getGlobalBounds().intersects(objects["left"]->getSprite()->getGlobalBounds()) || Player->getSprite()->getGlobalBounds().intersects(objects["right"]->getSprite()->getGlobalBounds())) {
			float velocityX = Player->getVelocityX();
			if (velocityX < 0) {
				Player->setVelocity(velocityX * (-1), Player->getVelocityY());
			}
			else if (velocityX >= 0) {
				Player->setVelocity(velocityX * (-1), Player->getVelocityY());
			}
		}

		//update
		for (const auto& it : objects) {
			it.second->update(1);
		}
		for (const auto& it : bullets_object) {
			it.second->update(1);
		}

		// Collect keys of bullets to be deleted
		std::vector<std::string> bulletsToDelete;
		for (const auto& it : bullets_object) {
			object* Object = it.second;
			if (Object->getSprite()->getGlobalBounds().intersects(objects["right"]->getSprite()->getGlobalBounds())) {
				bulletsToDelete.push_back(it.first);
				spritesThatWillBeDrawn.erase(it.first);
				delete Object;
			}
		}
		// Erase bullets from bullets_object map
		for (const auto& bulletKey : bulletsToDelete) {
			bullets_object.erase(bulletKey);
		}

		//draw
		for (const auto& it : spritesThatWillBeDrawn) {
			sf::RectangleShape* sprite = it.second;
			window.draw(*sprite);
		}
		window.display();
	}
	return 0;
}