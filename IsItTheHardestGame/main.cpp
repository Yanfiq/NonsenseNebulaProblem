#include <string>
#include <vector>
#include <stdbool.h>
#include "manageObject.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//create player
	manageObject::createObject("player", 100, 100, 60, 29, 0.0002f);
	manageObject::show_object("player");

	//border
	manageObject::createObject("up", 0, 0, 1280, 1, 0);
	manageObject::show_object("up");

	manageObject::createObject("down", 0, 720, 1280, 1, 0);
	manageObject::show_object("down");

	manageObject::createObject("left", 0, 0, 1, 720, 0);
	manageObject::show_object("left");

	manageObject::createObject("right", 1000, 0, 1, 720, 0);
	manageObject::show_object("right");

	sf::Text text;
	sf::Font font; font.loadFromFile("fonts/SAOUITT-Regular.ttf");
	text.setString("The bullet is empty\nPress X to reload the bullet");
	text.setFont(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Black);
	bool bulletEmpty = false;

	while (window.isOpen()) {
		bool gas = false; static int bullet_count = 1;
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
				if (event.key.code == sf::Keyboard::LShift && manageObject::get_objectptr<player>("player")->getBulletCount() <= 30) {
					/*manageObject::get_objectptr<player>("player")->shoot();*/

					std::string bullet_id = "bullet_" + std::to_string(bullet_count);
					manageObject::createObject(bullet_id, manageObject::get_objectptr<player>("player")->getPositionX(), manageObject::get_objectptr<player>("player")->getPositionY(), 20, 20, 0);
					manageObject::get_objectptr<bullet>(bullet_id)->setVelocity(0.5, 0);
					manageObject::show_object(bullet_id);
					if (manageObject::get_objectptr<player>("player")->getBulletCount() > 30) {
						bulletEmpty = true;
					}
				}
				if (event.key.code == sf::Keyboard::X && bulletEmpty == true) {
					manageObject::get_objectptr<player>("player")->resetBulletCount();
					bulletEmpty = false;
				}
			}
		}

		if (gas == true) {
			manageObject::get_objectptr<player>("player")->thrust();
		}
		if (bulletEmpty == true) {
			window.draw(text);
		}
		
		//Reflection
		player* Player = manageObject::get_objectptr<player>("player");
		if (manageObject::isintersect(Player->getSprite(), manageObject::get_objectptr<inanimateObject>("down")->getSprite())) {
			float velocityY = Player->getVelocityY();
			Player->setVelocity(Player->getVelocityX(), velocityY * (-1));
		}

		//update & draw
		std::unordered_map<std::string, sf::RectangleShape*> spritesMap = manageObject::getSpritesMap();
		for (const auto& it : spritesMap) {
			if (it.first.substr(0, 6) == "player") {
				manageObject::get_objectptr<player>(it.first)->update(1);
			}
			else if (it.first.substr(0, 6) == "bullet") {
				manageObject::get_objectptr<bullet>(it.first)->update(1);
			}
			sf::RectangleShape *sprite = it.second;
			window.draw(*sprite);
			if (it.first.substr(0, 6) == "bullet" && manageObject::isintersect(it.second, manageObject::get_objectptr<inanimateObject>("right")->getSprite())) {
				manageObject::delete_object(it.first);
				manageObject::unshow_object(it.first);
			}
		}
		window.display();
	}
	return 0;
}