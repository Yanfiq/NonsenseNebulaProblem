#include "func.h"


float getRandomFloat(float num_1, float num_2) {

	float min = (num_1 < num_2) ? num_1 : num_2;
	float max = (min == num_1) ? num_2 : num_1;

    // Seed the random number generator with the current time
    static std::mt19937 rng(static_cast<unsigned>(std::time(0)));

    // Define the distribution for floating-point numbers
    std::uniform_real_distribution<float> dist(min, max);

    // Generate and return a random float number within the specified range
    return dist(rng);
}

int getRandomInteger(int num_1, int num_2) {

	int min = (num_1 < num_2) ? num_1 : num_2;
	int max = (min == num_1) ? num_2 : num_1;

    // Define the random number generator engine
    std::random_device rd;
    std::default_random_engine rng(rd());

    // Define the uniform integer distribution using the specified range
    std::uniform_int_distribution<int> dist(min, max);

    return dist(rng);
}

int processCollision() {
	//collision detection and object removal
	std::unordered_map<int, bullet*>* bulletMap = bullet::getBulletMap();
	std::unordered_map<int, enemy*>* enemyMap = enemy::getEnemyMap();
	std::unordered_map<int, player*>* playerMap = player::getPlayerMap();

	//  something...collided with...something
	std::unordered_map<int, int> collideObject;
	for (auto bullet_object = bulletMap->begin(); bullet_object != bulletMap->end(); bullet_object++) {
		//bullets from the player
		if ((bullet_object->second != NULL) && (bullet_object->second->getVelocityX() > 0)) {
			for (auto enemy_object = enemyMap->begin(); enemy_object != enemyMap->end(); enemy_object++) {

				//collision happens between enemy and bullet
				if (enemy_object->second != NULL && object::isintersect(enemy_object->second->getSprite(), bullet_object->second->getSprite())) {
					//add the bullet's id and enemy's id to the map
					collideObject[enemy_object->first] = bullet_object->first;
				}
			}
		}

		//bullets from the enemy
		else if (bullet_object->second != NULL && bullet_object->second->getVelocityX() < 0) {
			for (auto player_object = playerMap->begin(); player_object != playerMap->end(); player_object++){
				//collision happens between player and the bullet
				if (player_object->second != NULL && object::isintersect(player_object->second->getSprite(), bullet_object->second->getSprite())) {
					//add the bullet's id and player's id to the map
					collideObject[player_object->first] = (bullet_object->first);
				}
			}
		}
	}
	
	int points = 0;
	for (const auto& it : collideObject) {
		if ((bullet::getObjectPtr(it.second) != NULL) &&
			(it.first - enemy_obj < 100 && it.first - enemy_obj > 0)) {
			enemy* Enemy = enemy::getObjectPtr(it.first);
			bullet* Bullet = bullet::getObjectPtr(it.second);
			Enemy->reduceHp(Bullet->getDamageValue());
			points += Bullet->getDamageValue();
			if (Enemy->getHp() <= 0) {
				animate::play("gameplay_explode.png", 4, 5, sf::Vector2f(Enemy->getPositionX(), Enemy->getPositionY()));
				sounds::playBoomSound(100);
				enemy::deleteObject(it.first);
			}
			bullet::deleteObject(it.second);
		}
		else if ((bullet::getObjectPtr(it.second) != NULL) &&
			(it.first - player_obj < 100 && it.first - player_obj > 0)) {
			player* Player = player::getObjectPtr(it.first);
			bullet* Bullet = bullet::getObjectPtr(it.second);
			Player->reducePlayerHp(Bullet->getDamageValue());
			points -= Bullet->getDamageValue();
			if (Player->getPlayerHp() <= 0) {
				animate::play("gameplay_explode.png", 4, 5, sf::Vector2f(Player->getPositionX(), Player->getPositionY()));
				sounds::playBoomSound(100);
				player::deleteObject(it.first);
			}
			bullet::deleteObject(it.second);
		}
	}
	return points;
}

void displayTutorial(sf::RenderWindow& window, sf::Font* font, int step) {
	sfe::RichText text_1(*font);
	sfe::RichText text_2(*font);
	switch (step)
	{
	case 1:
		text_1 << sf::Color::Cyan << "Step 1\n"
			<< sf::Color::White << "use 'W' button to go up";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Up' instead\n";
		text_2.setPosition(700, 150);

		textureManager::displayImage(window, "tutorial_wasd.jpg", 100, 300, sf::Vector2f(500, 281));
		textureManager::displayImage(window, "tutorial_arrows.jpg", 700, 300, sf::Vector2f(500, 281));
		break;
	case 2:
		text_1 << sf::Color::Cyan << "Step 2\n"
			<< sf::Color::White << "use 'S' button to go down\n";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Down' instead\n";
		text_2.setPosition(700, 150);

		textureManager::displayImage(window, "tutorial_wasd.jpg", 100, 300, sf::Vector2f(500, 281));
		textureManager::displayImage(window, "tutorial_arrows.jpg", 700, 300, sf::Vector2f(500, 281));
		break;
	case 3:
		text_1 << sf::Color::Cyan << "Step 3\n"
			<< sf::Color::White << "use 'D' button to fire the bullet\n";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Right' instead\n";
		text_2.setPosition(700, 150);

		textureManager::displayImage(window, "tutorial_wasd.jpg", 100, 300, sf::Vector2f(500, 281));
		textureManager::displayImage(window, "tutorial_arrows.jpg", 700, 300, sf::Vector2f(500, 281));
		break;
	case 4:
		text_1 << sf::Color::Cyan << "Step 4\n"
			<< sf::Color::White << "use 'A' button to reload the bullet\n";
		text_1.setPosition(100, 100);

		text_2 << sf::Color::White << "for the player_2, use 'Left' instead\n";
		text_2.setPosition(700, 150);

		textureManager::displayImage(window, "tutorial_wasd.jpg", 100, 300, sf::Vector2f(500, 281));
		textureManager::displayImage(window, "tutorial_arrows.jpg", 700, 300, sf::Vector2f(500, 281));
		break;
	case 5:
		text_1 << sf::Color::Cyan << "Step 5\n"
			<< sf::Color::White << "use spacebar to pause the game\n";
		text_1.setPosition(400, 100);

		textureManager::displayImage(window, "tutorial_spacebar.jpg", 380, 300, sf::Vector2f(500, 281));
		break;
	}

	text_1.setCharacterSize(30); text_2.setCharacterSize(30);
	window.draw(text_1);
	window.draw(text_2);
}

sfe::RichText displayCredit(sf::Font* font, float position_x, float position_y) {
	sfe::RichText text(*font);
	text.setCharacterSize(30);
	text.setPosition(position_x, position_y);

	text << sf::Color::Cyan << "CREDITS\n\n"
		<< sf::Color::Cyan << sf::Text::Underlined << "Game Design\n"
		<< sf::Color::White << sf::Text::Regular << "Muhammad Ryan Fikri Fakhrezi\n\n"
		<< sf::Color::Cyan << sf::Text::Underlined << "Special thanks: \n"
		<< sf::Color::Cyan << sf::Text::Underlined << "Music: \n"
		<< sf::Color::White << sf::Text::Regular << "Boooring! [Instrumental]\n"
		<< sf::Color::White << sf::Text::Regular << "By Assertive Fluttershy\n\n"
		<< sf::Color::Cyan << sf::Text::Underlined << "Font: \n"
		<< sf::Color::White << sf::Text::Regular << "Poppins\n"
		<< sf::Color::White << sf::Text::Regular << "Designed by Indian Type Foundry, Jonny Pinhorn\n\n"
		<< sf::Color::Cyan << sf::Text::Underlined << "Art: \n"
		<< sf::Color::White << sf::Text::Regular << "Nebula background by Starkiteckt\n"
		<< sf::Color::White << sf::Text::Regular << "https://www.deviantart.com/starkiteckt\n\n"
		<< sf::Color::White << sf::Text::Regular << "Player's texture from pngwing.com\n"
		<< sf::Color::White << sf::Text::Regular << "https://www.pngwing.com/en/free-png-bxslp\n\n"
		<< sf::Color::White << sf::Text::Regular << "Enemy's texture from pngwing.com\n"
		<< sf::Color::White << sf::Text::Regular << "https://www.pngwing.com/en/free-png-ykqrx\n\n"
		<< sf::Color::White << sf::Text::Regular << "Bullet's texture by GintasDX\n"
		<< sf::Color::White << sf::Text::Regular << "https://www.deviantart.com/gintasdx\n\n"
		<< sf::Color::White << sf::Text::Regular << "Explosion APNG from pngwing.com\n"
		<< sf::Color::White << sf::Text::Regular << "https://www.pngwing.com/en/free-png-plgdq\n\n";

	return text;
}