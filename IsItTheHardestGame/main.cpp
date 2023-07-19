#include "SFML/Graphics.hpp"
#include <stdbool.h>
#include "object.h"
#include "SFML/Window.hpp"
#include <string.h>
#include "SFML/Rect.hpp"
#include <string>
#include <iostream>
#include <stdlib.h>
#include"SFML/Audio.hpp"
#include "Func.h"
#include <map>

std::map <std::string, *object> all_object;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//OBJECT ID: PLANE
	object* Plane = new object("player", 200, 212, 60, 29);
	all_object["player"] = Plane;

	while (window.isOpen())
	{
		window.clear(sf::Color(255, 255, 255));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

				//case sf::Event::KeyPressed:
					//if (event.key.code == sf::Keyboard::Space)
					//{
					//	if (Plane.maxY > Plane.velocityY > Plane.minY)
					//	{
					//		thrust = true;
					//	}
					//}
			}
		}

		window.draw(Plane->draw_object());

		window.display();
	}
	return 0;
}