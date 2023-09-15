#include <stdbool.h>
#include <iostream>
#include "SFML/Audio.hpp"

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "Text.h"
#include "soundManager.h"
#include "func.h"
#include "RNG.h"
#include "bar.h"
#include "textureManager.h"
#include "InputManager.h"
#include "animationManager.h"
#include "collisionHandler.h"

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(1280, 720), "Nonsense Nebula's Problem Goes Pew Pew", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	sf::View view(sf::FloatRect(0.f, 0.f, 1280.f, 720.f));
	window.setView(view);

	sf::Clock clock;
	sf::Clock elapsed;
	sf::Event event;

	//fps
	const int numFramesToAverage = 60;
	std::vector<float> frameTimes(numFramesToAverage, 0.0f);
	int frameTimeIndex = 0;
	
	//texture initialization
	textRenderer TextRenderer("fonts/Poppins-SemiBold.ttf");
	textureManager::Instance()->loadTexture();
	soundManager::Instance()->loadSound();
 
	// enumeration for scene changes
	enum part { start, settings , tutorial, credits, transition, singleMulti, play, pause };

	// variables that'll be used inside the main game
	int level = 0;					// as the name implies, to differentiate levels
	int currentPoint = 0;			// as the name implies, to save the point calculation result
	bool generateEnemy = false;		// decides whether to generate new enemies
	bool endless = false;			// endless mode
	bool cheat = false;				// cheat
	int scene = start;				// decide what scene is being run

	//binding keys
	InputManager::Instance()->KBind("Enter", sf::Keyboard::Enter);
	InputManager::Instance()->KBind("Spacebar", sf::Keyboard::Space);
	InputManager::Instance()->KBind("Back", sf::Keyboard::Escape);
	InputManager::Instance()->KBind("Up_1", sf::Keyboard::Up);
	InputManager::Instance()->KBind("Up_2", sf::Keyboard::W);
	InputManager::Instance()->KBind("Down_1", sf::Keyboard::Down);
	InputManager::Instance()->KBind("Down_2", sf::Keyboard::S);
	InputManager::Instance()->KBind("Left_1", sf::Keyboard::Left);
	InputManager::Instance()->KBind("Left_2", sf::Keyboard::A);
	InputManager::Instance()->KBind("Right_1", sf::Keyboard::Right);
	InputManager::Instance()->KBind("Right_2", sf::Keyboard::D);

	// main game loop
	while (window.isOpen()) {
		// POLL EVENT SECTION ----------------------------------------------------------------------------------------------------------------------------------------------------------
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
			{
				int width = (event.size.width < 1280) ? 1280 : event.size.width;
				int height = (event.size.height < 720) ? 720 : event.size.height;
				sf::FloatRect visibleArea(0.f, 0.f, width, height);
				std::cout << width << " , " << height << std::endl;
				window.setSize(sf::Vector2u(width, height));
				window.setView(sf::View(visibleArea));
				break;
			}
			}
			InputManager::Instance()->KRUpdate(event);
		}
		// END OF POLL EVENT SECTION ---------------------------------------------------------------------------------------------------------------------------------------------------

		// RENDER SECTION --------------------------------------------------------------------------------------------------------------------------------------------------------------
		textureManager::Instance()->displayImage(window, "background_nebula.jpg", window.getSize().x/2, window.getSize().y/2, sf::Vector2f(window.getSize()));
		// delta time between frame
		float dt = clock.restart().asSeconds();
		if (scene == pause) {
			if (!cheat) {
				player::renderAllObject(dt, window, false);
				bullet::renderAllObject(dt, window, object::Type::playerBullet_obj, false);
				bullet::renderAllObject(dt, window, object::Type::enemyBullet_obj, false);
			}
			else {
				player::renderAllObject(dt, window, true);
				bullet::renderAllObject(dt, window, object::Type::playerBullet_obj, true);
				bullet::renderAllObject(dt, window, object::Type::enemyBullet_obj, false);
			}
			enemy::renderAllObject(dt, window, false);
		}
		else {
			player::renderAllObject(dt, window, true);
			bullet::renderAllObject(dt, window, object::Type::playerBullet_obj, true);
			bullet::renderAllObject(dt, window, object::Type::enemyBullet_obj, true);
			enemy::renderAllObject(dt, window, true);
		}
		currentPoint += collisionHandler::handleCollision();
		animationManager::Instance()->monitor(window);
		soundManager::Instance()->monitor();

		//fps displayer
		frameTimes[frameTimeIndex] = dt;
		frameTimeIndex = (frameTimeIndex + 1) % numFramesToAverage;
		float averageFrameTime = 0.0f;
		for (int i = 0; i < numFramesToAverage; i++) {
			averageFrameTime += frameTimes[i];
		}
		averageFrameTime /= numFramesToAverage;
		int fps = static_cast<int>(1.0f / averageFrameTime);
		TextRenderer.displayText(window, std::to_string(fps) + " FPS", 2, 40, sf::Color::White, window.getSize().x - 20, 20);
		// END OF RENDER RECTION -----------------------------------------------------------------------------------------------------------------------------------------------------------

		// SCENES AND VIDEO GAME LOGIC -----------------------------------------------------------------------------------------------------------------------------------------------------
		switch (scene) {
		case start:
		{
			bullet::clearObject();
			enemy::clearObject();
			TextRenderer.displayText(window, "Nonsense Nebula's Problem\n\t\t\t\tGoes Pew Pew", 1, 60, sf::Color::White, window.getSize().x / 2, 100);

			static int choice = 0;
			std::vector<std::string> choices = { "START", "SETTINGS", "EXIT" };
			TextRenderer.displayMultipleChoice(window, choices, choice, 50, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 300);

			if (InputManager::Instance()->KeyPress("Up_1"))   choice = (choice == 0) ? 0 : choice - 1;
			if (InputManager::Instance()->KeyPress("Down_1")) choice = (choice == 2) ? 2 : choice + 1;
			if (InputManager::Instance()->KeyPress("Enter")) {
				switch (choice) {
				case 0:scene = singleMulti; break;
				case 1:scene = settings; break;
				case 2: window.close(); break;
				}
				choice = 0;
			}
			break;
		}
		case tutorial:
		{
			static int step = 1;
			displayTutorial(window, TextRenderer.getFont(), step);
			TextRenderer.displayText(window, "Press ENTER to continue", 1, 30, sf::Color::White, window.getSize().x/2, window.getSize().y - 110);
			if (InputManager::Instance()->KeyPress("Enter")) step++;
			if (step > 11) {
				scene = settings;
				step = 1;
			}
			break;
		}

		case settings:
		{
			TextRenderer.displayText(window, "Nonsense Nebula's Problem\n\t\t\t\tGoes Pew Pew", 1, 60, sf::Color::White, window.getSize().x / 2, 100);

			static int choice = 0;
			std::string Cheat = (cheat) ? "Enabled" : "Disabled";
			std::vector<std::string> choices = { "BGM Volume : <" + std::to_string(soundManager::Instance()->getVolume(1)) + "%>",
												 "SFX Volume : <" + std::to_string(soundManager::Instance()->getVolume(2)) + "%>",
												 "Cheat : < " + Cheat + " >",
												 "Tutorial",
												 "Credit",
												 "Back to main menu"};
			TextRenderer.displayMultipleChoice(window, choices, choice, 40, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 450);


			// ACTION
			// moving between choices
			if (InputManager::Instance()->KeyPress("Up_1")) choice = (choice == 0) ? 0 : choice - 1;
			if (InputManager::Instance()->KeyPress("Down_1")) choice = (choice == 5) ? 5 : choice + 1;

			// Decrease / disable
			if (InputManager::Instance()->KeyPress("Left_1")) {
				switch (choice) {
				case 0:soundManager::Instance()->changeVolume(1, -5); break;
				case 1:soundManager::Instance()->changeVolume(2, -5); soundManager::Instance()->playSound("sfx_shoot.ogg"); break;
				case 2:cheat = false; window.create(sf::VideoMode(1280, 720), "Nonsense Nebula's Problem Goes Pew Pew", sf::Style::Titlebar | sf::Style::Close); window.setFramerateLimit(60);  break;
				}
			}

			// Increase / enable
			if (InputManager::Instance()->KeyPress("Right_1")) {
				switch (choice) {
				case 0:soundManager::Instance()->changeVolume(1, +5); break;
				case 1:soundManager::Instance()->changeVolume(2, +5); soundManager::Instance()->playSound("sfx_shoot.ogg"); break;
				case 2:cheat = true; window.create(sf::VideoMode(1280, 720), "Nonsense Nebula's Problem Goes Pew Pew", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize); window.setFramerateLimit(60);  break;
				}
			}

			// scene changes
			if (InputManager::Instance()->KeyPress("Enter")) {
				switch (choice) {
				case 3:scene = tutorial; break;
				case 4:scene = credits; break;
				case 5:scene = start; break;
				}
				choice = 0;
			}
			break;
		}

		case credits:
		{
			float windowY = window.getSize().y;
			static float slideUp = 0;
			sfe::RichText text = displayCredit(TextRenderer.getFont(), 100, windowY - slideUp);
			window.draw(text);
			slideUp += 5;
			if (slideUp > 2050 + windowY) {
				scene = settings;
				slideUp = 0;
			}
			break;
		}

		case singleMulti:
		{
			static int choice;
			std::vector<std::string> choices = { "Singleplayer", "Multiplayer" };
			TextRenderer.displayText(window, "Nonsense Nebula's Problem\n\t\t\t\tGoes Pew Pew", 1, 50, sf::Color::White, window.getSize().x/2, 100);
			TextRenderer.displayText(window, "Choose your gamemode: ", 0, 40, sf::Color::White, 100, window.getSize().y - 220);
			TextRenderer.displayMultipleChoice(window, choices, choice, 40, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 180);

			// moving between choices
			if (InputManager::Instance()->KeyPress("Up_1"))   choice = 0;
			if (InputManager::Instance()->KeyPress("Down_1")) choice = 1;
			if (InputManager::Instance()->KeyPress("Enter")){
				if (choice == 0) {
					player* Player_1 = new player(1, "gameplay_player.png", 100, static_cast<float>(window.getSize().y) * 1/2, 0, 0);
				}
				if (choice == 1) {
					player* Player_1 = new player(1, "gameplay_player.png", 100, static_cast<float>(window.getSize().y) * 1/3, 0, 0);
					player* Player_2 = new player(2, "gameplay_player.png", 100, static_cast<float>(window.getSize().y) * 2/3, 0, 0);
				}
				scene = play;
				choice = 0;
			}
			break;
		}

		case transition:
		{
			if(level == -1){ //lOSE
				TextRenderer.displayText(window, "YOU LOSE :(\nBETTER LUCK NEXT TIME", 0, 40, sf::Color::White, 100, 100);
				TextRenderer.displayText(window, "Your last score is " + std::to_string(currentPoint), 0, 40, sf::Color::White, 100, 200);
				TextRenderer.displayText(window, "Press Enter to back to main menu", 1, 40, sf::Color::White, window.getSize().x/2, window.getSize().y - 60);
				if (InputManager::Instance()->KeyPress("Enter")) {
					player::clearObject();
					enemy::clearObject();
					level = 0;
					currentPoint = 0;
					scene = start;
					endless = false;
				}
			}
			else if (level > 2) { //WIN
				static int choice = 0;
				TextRenderer.displayText(window, "CONGRATULATION :)\nYOU'RE THE WINNER", 0, 40, sf::Color::White, 100, 120);
				TextRenderer.displayText(window, "Your final score is " + std::to_string(currentPoint), 0, 40, sf::Color::White, 100, 210);
				std::vector<std::string>choices = {"ENDLESS MODE", "Main menu"};
				TextRenderer.displayMultipleChoice(window, choices, choice, 40, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 180);

				if (InputManager::Instance()->KeyPress("Up_1"))   choice = 0;
				if (InputManager::Instance()->KeyPress("Down_1")) choice = 1;
				if (InputManager::Instance()->KeyPress("Enter")) {
					if (choice == 0) {
						endless = true;
						scene = play;
					}
					else if (choice == 1) {
						player::clearObject();
						level = 0;
						currentPoint = 0;
						scene = start;
					}
				}
			}
			else { //NEXT LEVEL
				TextRenderer.displayText(window, "LEVEL " + std::to_string(level + 1), 0, 40, sf::Color::Cyan, 100, 100);
				TextRenderer.displayText(window, "Press ENTER to continue", 1, 30, sf::Color::White, window.getSize().x/2, window.getSize().y - 60);
				if (InputManager::Instance()->KeyPress("Enter")) {
					level++;
					generateEnemy = true;
					scene = play;
				}
			}
			break;
		}

		case pause:
		{
			static int choice = 0;
			TextRenderer.displayText(window, "PAUSE", 0, 40, sf::Color::White, 100, 100);
			std::vector<std::string> choices = { "Resume", "Rage quit" };
			TextRenderer.displayMultipleChoice(window, choices, choice, 40, sf::Color::Cyan, sf::Color::White, 100, window.getSize().y - 160);

			if (InputManager::Instance()->KeyPress("Up_1"))   choice = 0;
			if (InputManager::Instance()->KeyPress("Down_1")) choice = 1;
			if (InputManager::Instance()->KeyPress("Enter")) {
				switch (choice) {
				case 0:
					scene = play;  
					break;
				case 1:
					scene = start; 
					level = 0;
					endless = false;
					player::clearObject();
					enemy::clearObject();
					break;
				}
			}
			break;
		}

		case play:
		{
			//pause the game if the window lost its focus
			if (!window.hasFocus()) {
				scene = pause;
			}

			if (endless) {
				static float difficulty = 3;
				static int counts = 1; // just for id
				if (elapsed.getElapsedTime().asSeconds() > 10 || enemy::getEnemyMap()->size() < 3) {
					//generate enemy
					int counter = 0;
					for (int i = counts; i < counts + ((RNG::generateRandomFloat(window.getSize().x / 288, window.getSize().y / 176)) * difficulty); i++) {
						enemy* Enemy = new enemy(i, "gameplay_enemy.png", RNG::generateRandomFloat(400, window.getSize().x), RNG::generateRandomFloat(0, window.getSize().y), RNG::generateRandomFloat(-1000, 1000), RNG::generateRandomFloat(-1000, 1000));
						counter++;
					}
					counts += counter;
					if (counts == 999)counts = 1;
					difficulty += 0.5;
					elapsed.restart();
				}
			}


			//level mechanics and enemy object creation
			if (generateEnemy) {
				bullet::clearObject();
				switch (level) {
				case 1:
				{
					for (int i = 1; i < RNG::generateRandomFloat(window.getSize().x / 288, window.getSize().y / 176); i++) {
						enemy* Enemy = new enemy(i, "gameplay_enemy.png", RNG::generateRandomFloat(400, window.getSize().x), RNG::generateRandomFloat(0, window.getSize().y), RNG::generateRandomFloat(-500, 500), RNG::generateRandomFloat(-500, 500));
					}
					break;
				}
				case 2:
				{
					for (int i = 1; i < RNG::generateRandomFloat((window.getSize().x / 288), (window.getSize().y / 176)) * 2; i++) {
						enemy* Enemy = new enemy(i, "gameplay_enemy.png", RNG::generateRandomFloat(400, window.getSize().x), RNG::generateRandomFloat(0, window.getSize().y), RNG::generateRandomFloat(-750, 750), RNG::generateRandomFloat(-750, 750));
					}
					break;
				}
				case 3:
				{
					for (int i = 1; i < RNG::generateRandomFloat((window.getSize().x / 288), (window.getSize().y / 176)) * 3; i++) {
						enemy* Enemy = new enemy(i, "gameplay_enemy.png", RNG::generateRandomFloat(400, window.getSize().x), RNG::generateRandomFloat(0, window.getSize().y), RNG::generateRandomFloat(-1000, 1000), RNG::generateRandomFloat(-1000, 1000));
					}
					break;
				}
				}
				generateEnemy = false;
				break;
			}

			//level up when the enemy is 0
			if ((enemy::getEnemyMap()->empty() || player::getPlayerMap()->empty())) {
				scene = transition;
				enemy::clearObject();
				level = (player::getPlayerMap()->empty()) ? -1 : level;
				break;
			}

			if (InputManager::Instance()->KeyPress("Spacebar")) {
				if (player::getObjectPtr(object::Type::player_obj + 1) != NULL) player::getObjectPtr(object::Type::player_obj + 1)->setVelocity(0, 0);
				if (player::getObjectPtr(object::Type::player_obj + 2) != NULL) player::getObjectPtr(object::Type::player_obj + 2)->setVelocity(0, 0);
				scene = pause;
			}

			//enemy's attack algorithm
			std::unordered_map<int, enemy*>* enemyMap = enemy::getEnemyMap();
			std::unordered_map<int, player*>* playerMap = player::getPlayerMap();
			for (auto enemy_object = enemyMap->begin(); enemy_object != enemyMap->end(); enemy_object++) {
				enemy* Enemy = enemy_object->second;
				for (auto player_object = playerMap->begin(); player_object != playerMap->end(); player_object++) {
					player* Player = player_object->second;
					if ((Enemy->getPosition().y < Player->getPosition().y + 15) &&
						(Enemy->getPosition().y > Player->getPosition().y - 15)) {
						Enemy->shoot();
					}
				}
			}

			TextRenderer.displayText(window, "Score : " + std::to_string(currentPoint), 0, 40, sf::Color::White, 30, 30);
			break;
		}
		}

		/*VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV PLAYER'S CONTROL VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV*/
		if ((scene != pause) || (scene == pause && cheat)) {
			//FIRST PLAYER
			if (player::getObjectPtr(object::Type::player_obj + 1) != NULL) {
				static bool cooldown = false;
				player* player_1 = player::getObjectPtr(object::Type::player_obj + 1);
				player_1->bulletBar.draw(window, player_1->getBulletRemain(), sf::Vector2f(150, window.getSize().y - 50));
				TextRenderer.displayText(window, "player_1's bullet", 1, 20, sf::Color::Black, 150, window.getSize().y - 50);
				if (InputManager::Instance()->KeyDown("Up_1"))
					player_1->thrustUp();
				if (InputManager::Instance()->KeyDown("Down_1"))
					player_1->thrustDown();
				if (InputManager::Instance()->KeyDown("Right_1") && player_1->getBulletRemain() >= 1 && !cooldown)
					player_1->shoot();
				if (InputManager::Instance()->KeyPress("Left_1")) 
					cooldown = true;
				if (cooldown) {
					if (player_1->getBulletRemain() >= MAX_PLAYER_BULLET) {
						cooldown = false;
					}
					else
						player_1->reloadBullet(1);
				}
			}

			//SECOND PLAYER
			if (player::getObjectPtr(object::Type::player_obj + 2) != NULL) {
				static bool cooldown = false;
				player* player_2 = player::getObjectPtr(object::Type::player_obj + 2);
				player_2->bulletBar.draw(window, player_2->getBulletRemain(), sf::Vector2f(window.getSize().x - 150, window.getSize().y - 50));
				TextRenderer.displayText(window, "player_2's bullet", 1, 20, sf::Color::Black, window.getSize().x - 150, window.getSize().y - 50);
				if (InputManager::Instance()->KeyDown("Up_2"))
					player_2->thrustUp();
				if (InputManager::Instance()->KeyDown("Down_2"))
					player_2->thrustDown();
				if (InputManager::Instance()->KeyDown("Right_2") && player_2->getBulletRemain() >= 1 && !cooldown)
					player_2->shoot();
				if (InputManager::Instance()->KeyPress("Left_2"))
					cooldown = true;
				if (cooldown) {
					if (player_2->getBulletRemain() >= MAX_PLAYER_BULLET) {
						cooldown = false;
					}
					else {
						player_2->reloadBullet(1);
					}
				}
			}
		}
		/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ PLAYER'S CONTROL ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
		sf::Listener::setPosition(0, 0, 0);
		window.display();
		window.clear();
		InputManager::Instance()->Update();
	}
	return 0;
}