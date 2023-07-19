#include <string>
#include <map>
#include <iostream>
#include <stdbool.h>
#include "objects.h"

std::map <std::string, object*> objects;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//create player
	object *Plane = new object("player", 100, 100, 60, 29, 0.0002);
	objects[Plane->getId()] = Plane;

	//border
	object* up = new object("up", 0, 0, 1280, 1, 0); objects[up->getId()] = up;
	object* down = new object("down", 0, 720, 1280, 1, 0); objects[down->getId()] = down;
	object* left = new object("left", 0, 0, 1, 720, 0); objects[left->getId()] = left;
	object* right = new object("right", 1280, 0, 1, 720, 0); objects[right->getId()] = right;

	while (window.isOpen())
	{
		bool gas = false;
		window.clear(sf::Color(255, 255, 255));
		//draw object
		for (const auto& it : objects) {
			object* Object = it.second;
			Object->update(1);
			window.draw(Object->getSprite());
		}

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space)
				{
					gas = true;
				}
			}
		}

		if (gas == true) {
			objects["player"]->thrust();
		}

		object* Player = objects["player"];
		if (Player->getSprite().getGlobalBounds().intersects(objects["down"]->getSprite().getGlobalBounds())) {
			Player->setVelocity(0, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				Player->thrust();
			}
		}
		if (Player->getSprite().getGlobalBounds().intersects(objects["up"]->getSprite().getGlobalBounds())) {
			Player->setVelocity(0, Player->getVelocityY()*(-1));
		}
		window.display();
	}
	return 0;
}