#include <string>
#include <map>
#include <iostream>
#include "objects.h"

std::map <std::string, object*> all_object;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//OBJECT ID: PLANE
	object *Plane = new object("player", 0, 0, 60, 29);
	all_object[Plane->getId()] = Plane;

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
			//	if (event.key.code == sf::Keyboard::Space)
			//	{
			//		object* Object = all_object["player"];
			//		Object->thrust();
			//	}
			}
		}


		//draw object
		for (const auto& it : all_object) {
			object *Object = it.second;
			window.draw(Object->getSprite());
			Object->Update(1);
		}
		window.display();
	}
	return 0;
}