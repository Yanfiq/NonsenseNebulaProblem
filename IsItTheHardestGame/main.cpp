#include <string>
#include <unordered_map>
#include <vector>
#include <stdbool.h>
#include "objects.h"

int main(){
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//create player
	object *Plane = new object("player", 100, 100, 60, 29, 0.0002f);
	manageObject::assign_objectptr("player", Plane);
	manageObject::show_object("player");

	//bullet counter
	static int bulletCount = 1;

	//border
	object* up = new object("up", 0, 0, 1280, 1, 0);
	manageObject::assign_objectptr("up", up);
	manageObject::show_object("up");
	object* down = new object("down", 0, 720, 1280, 1, 0); 
	manageObject::assign_objectptr("down", down);
	manageObject::show_object("down");
	object* left = new object("left", 0, 0, 1, 720, 0); 
	manageObject::assign_objectptr("left", left);
	manageObject::show_object("left");
	object* right = new object("right", 1000, 0, 1, 720, 0); 
	manageObject::assign_objectptr("right", right);
	manageObject::show_object("right");

	while (window.isOpen()){
		bool gas = false;
		window.clear(sf::Color(255, 255, 255));

		while (window.pollEvent(event)){
			switch (event.type){
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space){
					gas = true;
				}
				if (event.key.code == sf::Keyboard::LShift) {
					std::string bullet_id = "bullet_" + std::to_string(bulletCount);
					bulletCount++;
					object* player = manageObject::get_objectptr("player");
					object* bullet = new object(bullet_id, player->getPositionX(), player->getPositionY(), 20, 20, 0);
					bullet->setVelocity(0.5, 0);
					manageObject::assign_bulletptr(bullet_id, bullet);
					manageObject::show_object(bullet_id);
				}
			}
		}

		if (gas == true) {
			Plane->thrust();
		}

		object* Player = manageObject::get_objectptr("player");
		if (manageObject::isintersect("player", "up") || manageObject::isintersect("player", "down")) {
			float velocityY = Player->getVelocityY();
			if (velocityY < 0) {
				Player->setVelocity(Player->getVelocityX(), velocityY * (-1));
			}
			else if(velocityY >= 0){
				Player->setVelocity(Player->getVelocityX(), velocityY * (-1));
			}
		}

		//update
		for (const auto& it : manageObject::getSpritesMap()) {
			manageObject::get_objectptr(it.first)->update(1);
			sf::RectangleShape* sprite = it.second;
			window.draw(*sprite);
		}

		// Collect keys of bullets to be deleted
		std::vector<std::string> bulletsToDelete;
		for (const auto& it : manageObject::getBulletsMap()) {
			object* Object = it.second;
			if (manageObject::isintersect("bullet", "right")) {
				bulletsToDelete.push_back(it.first);
				delete Object;
			}
		}
		// Erase bullets from bullets_object map
		for (const auto& bulletKey : bulletsToDelete) {
			manageObject::deassign_bulletptr(bulletKey, manageObject::get_objectptr(bulletKey));
		}

		//draw
		for (const auto& it : manageObject::getSpritesMap()) {
			sf::RectangleShape* sprite = it.second;
			window.draw(*sprite);
		}
		window.display();
	}
	return 0;
}