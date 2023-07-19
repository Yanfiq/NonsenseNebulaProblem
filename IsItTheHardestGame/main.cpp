#include <string>
#include <map>
#include <iostream>
#include <stdbool.h>
#include "objects.h"

std::map <std::string, object*> all_object;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//OBJECT ID: PLANE
	object *Plane = new object("player", 100, 100, 60, 29, 0.0002);
	all_object[Plane->getId()] = Plane;

	//border
	object* down = new object("down", 0, 720, 1280, 1, 0); all_object[down->getId()] = down;
	object* up = new object("up", 0, 0, 1280, 1, 0); all_object[up->getId()] = up;

	while (window.isOpen())
	{
		bool gas = false;
		window.clear(sf::Color(255, 255, 255));
		//draw object
		for (const auto& it : all_object) {
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
			all_object["player"]->thrust();
		}

		object* Player = all_object["player"];
		if (Player->getSprite().getGlobalBounds().intersects(all_object["down"]->getSprite().getGlobalBounds())) {
			Player->setVelocity(0, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				Player->thrust();
			}
		}
		if (Player->getSprite().getGlobalBounds().intersects(all_object["up"]->getSprite().getGlobalBounds())) {
			Player->setVelocity(0, Player->getVelocityY()*(-1));
		}
		window.display();
	}
	return 0;
}