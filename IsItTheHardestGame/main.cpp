#include <string>
#include <stdbool.h>
#include "object_manager.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//create player
	manageObject::createObject("player", 100, 100, 60, 29, 0.0002f);
	manageObject::show_object("player");
	

	//bullet counter
	static int bulletCount = 1;

	//border
	manageObject::createObject("up", 0, 0, 1280, 1, 0);
	manageObject::show_object("up");

	manageObject::createObject("down", 0, 720, 1280, 1, 0);
	manageObject::show_object("down");

	manageObject::createObject("left", 0, 0, 1, 720, 0);
	manageObject::show_object("left");

	manageObject::createObject("right", 1000, 0, 1, 720, 0);
	manageObject::show_object("right");

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
					manageObject::createObject_bullet(bullet_id, manageObject::get_objectptr("player")->getPositionX(), manageObject::get_objectptr("player")->getPositionY(), 20, 20, 0);
					manageObject::get_objectptr(bullet_id)->setVelocity(0.5, 0);
					manageObject::show_object(bullet_id);
				}
			}
		}

		if (gas == true) {
			manageObject::get_objectptr("player")->setVelocity(manageObject::get_objectptr("player")->getVelocityX(), manageObject::get_objectptr("player")->getVelocityY() - 0.06);
		}
		
		//Reflection
		object* Player = manageObject::get_objectptr("player");
		if (manageObject::isintersect(Player->getSprite(), manageObject::get_objectptr("down")->getSprite())) {
			float velocityY = Player->getVelocityY();
			Player->setVelocity(Player->getVelocityX(), velocityY * (-1));
		}

		//update
		std::unordered_map<std::string, sf::RectangleShape*> spritesMap;
		spritesMap = manageObject::getSpritesMap();
		for (const auto& it : spritesMap) {
			object* Object = manageObject::get_objectptr(it.first);
			Object->update(1);
			sf::RectangleShape *sprite = it.second;
			window.draw(*sprite);
		}

		// Collect keys of bullets to be deleted
		//std::vector<std::string> bulletsToDelete;
		//for (const auto& it : bullets_object) {
		//	object* Object = it.second;
		//	if (Object->getSprite()->getGlobalBounds().intersects(objects["right"]->getSprite()->getGlobalBounds())) {
		//		bulletsToDelete.push_back(it.first);
		//		spritesThatWillBeDrawn.erase(it.first);
		//		delete Object;
		//	}
		//}
		//// Erase bullets from bullets_object map
		//for (const auto& bulletKey : bulletsToDelete) {
		//	bullets_object.erase(bulletKey);
		//}
		window.display();
	}
	return 0;
}