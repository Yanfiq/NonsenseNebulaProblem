#include "SFML/Graphics.hpp"
#include <stdbool.h>
#include "SFML/Window.hpp"
#include "func.h"
#include <string.h>
#include "SFML/Rect.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include"SFML/Audio.hpp"

//OBJECT CLASS
class object
{
public:
	float positionX, positionY;
	float velocityX = 0, velocityY = 0;
	float width, height;
	float gravity = 0.01f;
	float maxY = 2;
	float minY = -2;
	float HP = 100;
	void Update(float time)
	{
		positionX += velocityX * time;
		if (minY < velocityY < maxY)
		{
			positionY += velocityY * time;
			velocityY += gravity * time;
		}
	}
};

int main() {
	sf::RenderWindow window(sf::VideoMode(2400, 1350), "Platypus Scuffed Edition", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	//BACKGROUND
	sf::Texture background;
	background.loadFromFile("images/background.png");
	sf::RectangleShape Background;
	Background.setTexture(&background);
	Background.setSize(sf::Vector2f(2400, 1350));

	//OBJECT ID: PLANE
	object Plane;
	Plane.positionX = 200;
	Plane.positionY = 212;
	Plane.width = 120;
	Plane.height = 60;
	sf::RectangleShape spritePlane(sf::Vector2f(Plane.width, Plane.height));
	spritePlane.setFillColor(sf::Color(0, 255, 160));
	spritePlane.setOrigin(sf::Vector2f::Vector2(60.f, 30.f));

	//TIME LIMIT
	const int limit = 60;
	int remain = 60;
	sf::Text Time;
	sf::Font font;
	int time = 0;
	int last_time = 0;
	font.loadFromFile("fonts/OCR A Extended Regular.ttf");
	Time.setFont(font);
	Time.setPosition(1800, 50);
	Time.setCharacterSize(50);
	Time.setFillColor(sf::Color::Black);

	//OBJECT ID: BULLET
	sf::RectangleShape spriteBullet[30];
	object bullet[30];
	for (int i = 0; i < 30; i++)
	{
		bullet[i].gravity = 0;
		bullet[i].velocityY = 0;
		bullet[i].velocityX = 5;
		spriteBullet[i].setOrigin(sf::Vector2f::Vector2(15.f, 15.f));
		spriteBullet[i].setSize(sf::Vector2f::Vector2(30.f, 30.f));
		spriteBullet[i].setFillColor(sf::Color(255, 255, 255));
	}

	//OBJECT ID: ENEMY A
	sf::Texture EnemyATexture;
	EnemyATexture.loadFromFile("images/EnemyA.png");
	object enemyA[5];
	sf::RectangleShape spriteEnemyA[5];
	for (int i = 0; i < 5; i++)
	{
		enemyA[i].width = 120;
		enemyA[i].height = 60;
		enemyA[i].gravity = 0;
		spriteEnemyA[i].setSize(sf::Vector2f::Vector2(enemyA[i].width, enemyA[i].height));
		spriteEnemyA[i].setOrigin(sf::Vector2f::Vector2(60.f, 30.f));
		spriteEnemyA[i].setFillColor(sf::Color(0, 0, 0));
	}

	//OBJECT ID:: ENEMY B
	sf::Texture EnemyBTexture;
	EnemyBTexture.loadFromFile("images/EnemyB.png");
	object enemyB[5];
	sf::RectangleShape spriteEnemyB[5];
	for (int i = 0; i < 5; i++)
	{
		enemyB[i].width = 180;
		enemyB[i].height = 90;
		enemyB[i].gravity = 0;
		enemyB[i].HP = 50;
		spriteEnemyB[i].setSize(sf::Vector2f::Vector2(enemyB[i].width, enemyB[i].height));
		spriteEnemyB[i].setOrigin(sf::Vector2f::Vector2(90.f, 45.f));
		spriteEnemyB[i].setFillColor(sf::Color(0, 0, 0));
	}

	//SCORE
	int score = 0;
	sf::Text Score;
	sf::Font fontScore;
	fontScore.loadFromFile("fonts/OCR A Extended Regular.ttf");
	Score.setCharacterSize(50);
	Score.setPosition(50, 50);
	Score.setFillColor(sf::Color::Black);
	Score.setFont(fontScore);

	//PLAYFIELD BORDER DECLARATION
	sf::RectangleShape borderUp(sf::Vector2f(2400.f, 1.f));
	borderUp.setFillColor(sf::Color(0, 0, 0));
	borderUp.setPosition(0, 0);
	sf::RectangleShape borderDown(sf::Vector2f(2400.f, 1.f));
	borderDown.setFillColor(sf::Color(0, 0, 0));
	borderDown.setPosition(0, 1349);
	sf::RectangleShape borderLeft(sf::Vector2f(1.f, 1350.f));
	borderLeft.setFillColor(sf::Color(0, 0, 0));
	borderLeft.setPosition(0, 0);
	sf::RectangleShape borderRight(sf::Vector2f(1.f, 1350.f));
	borderRight.setFillColor(sf::Color(0, 0, 0));
	borderRight.setPosition(2401, 0);

	//MUSIC
	sf::Music music;
	(music.openFromFile("audio/Everything-is-Okay.ogg"));
	music.play();
	music.setLoop(true);

	//BOOLEANS AND VARIABLES
	bool thrust = false;
	static bool fire = false;
	int bulletCounterA = 0;
	int bulletCounterB = 0;
	bool emptyA = false;
	bool emptyB = true;
	int choose = 1;
	bool start = false;
	int bulletVisibility[30];
	bool stillShootA = false;
	bool stillShootB = false;
	int before = 0;
	int hitA[5];
	int hitB[5];
	bool help = false;
	bool next = true;
	bool win = false;
	bool menu = true;
	for (int a = 0; a < 30; a++) { bulletVisibility[a] = 1; }
	sf::Clock clock;

	while (window.isOpen())
	{
		window.clear(sf::Color(255, 255, 255));
		window.draw(Background);
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
					if (Plane.maxY > Plane.velocityY > Plane.minY)
					{
						thrust = true;
					}
				}
				if (event.key.code == sf::Keyboard::LShift && (emptyA == false || emptyB == false))
				{
					if (emptyA == false && emptyB == true)
					{
						bullet[bulletCounterA].positionX = Plane.positionX;
						bullet[bulletCounterA].positionY = Plane.positionY;
						stillShootA = true;
						bulletCounterA++;
					}
					if (emptyB == false && emptyA == true)
					{
						bullet[bulletCounterB].positionX = Plane.positionX;
						bullet[bulletCounterB].positionY = Plane.positionY;
						stillShootB = true;
						bulletCounterB++;
					}

				}
				if (event.key.code == sf::Keyboard::X)
				{
					if (before == 1)
					{
						emptyA = true;
						emptyB = false;
						stillShootB = true;
						bulletCounterB = 0;
					}
					if (before == 2)
					{
						emptyB = true;
						emptyA = false;
						stillShootA = true;
						bulletCounterA = 0;
					}
				}
				//jika user menekan 
				if (event.key.code == sf::Keyboard::Up)
				{
					choose--;
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					choose++;
				}
				if (event.key.code == sf::Keyboard::Enter && choose == 1 && menu == true)
				{
					start = true;
					clock.restart();
				}
				if (event.key.code == sf::Keyboard::Enter && choose == 3 && menu == true)
				{
					window.close();
				}
				if (event.key.code == sf::Keyboard::Enter && choose == 2 && menu == true)
				{
					help = true;
					menu = false;
				}
				if (event.key.code == sf::Keyboard::Escape && help == true)
				{
					help = false;
					menu = true;
				}
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Space)
				{
					if (Plane.maxY > Plane.velocityY > Plane.minY)
					{
						thrust = false;
					}
				}
				break;
			}
		}

		if (start == false && menu == true)
		{
			sf::Font font;
			font.loadFromFile("fonts/OCR A Extended Regular.ttf");

			sf::Texture texture;
			texture.loadFromFile("images/gameTitle.png");
			sf::RectangleShape title(sf::Vector2f(1010.f, 298.f));
			title.setOrigin(505, 149);
			title.setTexture(&texture);
			title.setPosition(1200, 250);

			sf::Text newGame;
			newGame.setPosition(1000, 500);
			newGame.setString("START");
			newGame.setFont(font);
			newGame.setCharacterSize(50);

			sf::Text tutorial;
			tutorial.setPosition(1000, 600);
			tutorial.setString("TUTORIAL");
			tutorial.setFont(font);
			tutorial.setCharacterSize(50);

			sf::Text exit;
			exit.setPosition(1000, 700);
			exit.setString("EXIT");
			exit.setFont(font);
			exit.setCharacterSize(50);

			if (choose < 1)
				choose = 1;
			if (choose > 3)
				choose = 3;

			if (choose == 1)
			{
				newGame.setFillColor(sf::Color::Red);
				tutorial.setFillColor(sf::Color::Blue);
				exit.setFillColor(sf::Color::Blue);
			}
			if (choose == 2)
			{
				newGame.setFillColor(sf::Color::Blue);
				tutorial.setFillColor(sf::Color::Red);
				exit.setFillColor(sf::Color::Blue);
			}
			if (choose == 3)
			{
				newGame.setFillColor(sf::Color::Blue);
				tutorial.setFillColor(sf::Color::Blue);
				exit.setFillColor(sf::Color::Red);
			}
			window.draw(title);
			window.draw(newGame);
			window.draw(tutorial);
			window.draw(exit);
		}

		if (start == false && help == true)
		{
			sf::Texture tutorial;
			tutorial.loadFromFile("images/tutorial.png");
			sf::RectangleShape Help;
			Help.setTexture(&tutorial);
			Help.setSize(sf::Vector2f(2400, 1350));
			window.draw(Help);
		}

		if (start == true)
		{
			//TIMER
			sf::Time Elapsed = clock.getElapsedTime();
			int elapsed = Elapsed.asSeconds();
			if (time > last_time)
				remain = limit - elapsed;
			last_time = time;
			time = elapsed;
			menu = false;

			//PLANE MECHANICS
			spritePlane.setPosition(sf::Vector2f(Plane.positionX, Plane.positionY));
			if (thrust == true)
				Plane.velocityY -= 0.02;

			if (Plane.velocityY < -0)
				spritePlane.setRotation(-30.f);
			else if (Plane.velocityY >= 0)
				spritePlane.setRotation(0.f);

			//BULLET MECHANICS

			if (emptyA == false || stillShootA == true)
			{
				for (int i = 0; i < bulletCounterA; i++)
				{
					if(bulletVisibility[i] == 1)
					{
						bullet[i].Update(1);
						spriteBullet[i].setPosition(bullet[i].positionX, bullet[i].positionY);
						window.draw(spriteBullet[i]);
						if (spriteBullet[i].getGlobalBounds().intersects(borderRight.getGlobalBounds()))
						{
							bulletVisibility[i] = 0;
							if (i == 29)
								stillShootA = false;
						}
					}
					if (bulletCounterA == 30)
					{
						emptyA = true;
						before = 1;
					}
				}
			}

			if (emptyB == false || stillShootB == true)
			{
				for (int i = 0; i < bulletCounterB; i++)
				{
					if (bulletVisibility[i] == 0)
					{
						bullet[i].Update(1);
						spriteBullet[i].setPosition(bullet[i].positionX, bullet[i].positionY);
						window.draw(spriteBullet[i]);
						if (spriteBullet[i].getGlobalBounds().intersects(borderRight.getGlobalBounds()))
						{
							bulletVisibility[i] = 1;
							if (i == 29)
								stillShootB = false;
						}
					}
					if (bulletCounterB == 30)
					{
						emptyB = true;
						before = 2;
					}
				}
			}

			//RELOAD SCREEN
			if ((emptyA == true && emptyB == true && bulletCounterA == 30) || (emptyB == true && emptyA == true && bulletCounterB == 30))
			{
				sf::Font font;
				font.loadFromFile("fonts/ComicSansMS3.ttf");
				sf::Text text;
				text.setPosition(100, 100);
				text.setString("PRESS X TO RELOAD THE BULLET");
				text.setFont(font);
				text.setCharacterSize(50);
				text.setFillColor(sf::Color::Red);
				window.draw(text);
			}

			//BORDER
			if (spritePlane.getGlobalBounds().intersects(borderDown.getGlobalBounds())) {
				Plane.velocityY = 0;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					Plane.velocityY = -0.1;
				}
			}
			if (spritePlane.getGlobalBounds().intersects(borderUp.getGlobalBounds())) {
				Plane.velocityY = 0.1;
				spritePlane.setRotation(0);
			}

			//LEVEL
			float XNowA[5];
			float XNowB[5];
			float YNowA[5];
			float YNowB[5];
			if (next == true)
			{
				for (int i = 0; i < 5; i++)
				{
					enemyA[i].positionX = 1500;
					enemyA[i].positionY = (100 * i) + 200;
					enemyB[i].positionX = 2000;
					enemyB[i].positionY = (100 * i) + 200;
				}
				for (int a = 0; a < 30; a++) { hitA[a] = 0; }
				for (int a = 0; a < 5; a++) { XNowA[a] = enemyA[a].positionX; }
				for (int a = 0; a < 5; a++) { XNowB[a] = enemyB[a].positionX; YNowB[a] = enemyB[a].positionY; }
			}
			next = false;
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 30; j++)
				{
					if (hitA[i] == 0)
					{
						static int horizontalA = 1;
						static int verticalA = 0;
						static int RevHorizontalA = 0;
						static int RevVerticalA = 0;
						if (horizontalA == 1)
						{
							enemyA[i].velocityX = 0.1;
							if (enemyA[i].positionX - XNowA[i] >= 500)
							{
								enemyA[i].velocityX = 0;
								if (enemyA[0].velocityX == 0 && enemyA[1].velocityX == 0 && enemyA[2].velocityX == 0 && enemyA[3].velocityX == 0 && enemyA[4].velocityX == 0)
								{
									horizontalA = 0;
									verticalA = 1;
									for (int a = 0; a < 5; a++) { YNowA[a] = enemyA[a].positionY; }
								}
							}
						}
						if (verticalA == 1)
						{
							enemyA[i].velocityY = 0.1;
							if (enemyA[i].positionY - YNowA[i] >= 500)
							{
								enemyA[i].velocityY = 0;
								if (enemyA[0].velocityY == 0 && enemyA[1].velocityY == 0 && enemyA[2].velocityY == 0 && enemyA[3].velocityY == 0 && enemyA[4].velocityY == 0)
								{
									verticalA = 0;
									RevHorizontalA = 1;
									for (int a = 0; a < 5; a++) { XNowA[a] = enemyA[a].positionX; }
								}
							}
						}
						if (RevHorizontalA == 1)
						{
							enemyA[i].velocityX = -0.1;
							if (enemyA[i].positionX - XNowA[i] <= -500)
							{
								enemyA[i].velocityX = 0;
								if (enemyA[0].velocityX == 0 && enemyA[1].velocityX == 0 && enemyA[2].velocityX == 0 && enemyA[3].velocityX == 0 && enemyA[4].velocityX == 0)
								{
									RevHorizontalA = 0;
									RevVerticalA = 1;
									for (int a = 0; a < 5; a++) { YNowA[a] = enemyA[a].positionY; }
								}
							}
						}
						if (RevVerticalA == 1)
						{
							enemyA[i].velocityY = -0.1;
							if (enemyA[i].positionY - YNowA[i] <= -500)
							{
								enemyA[i].velocityY = 0;
								if (enemyA[0].velocityY == 0 && enemyA[1].velocityY == 0 && enemyA[2].velocityY == 0 && enemyA[3].velocityY == 0 && enemyA[4].velocityY == 0)
								{
									RevVerticalA = 0;
									horizontalA = 1;
									for (int a = 0; a < 5; a++) { XNowA[a] = enemyA[a].positionX; }
								}
							}
						}
						enemyA[i].Update(1);
						spriteEnemyA[i].setPosition(enemyA[i].positionX, enemyA[i].positionY);
						window.draw(spriteEnemyA[i]);
						if (spriteEnemyA[i].getGlobalBounds().intersects(spriteBullet[j].getGlobalBounds()))
						{
							hitA[i] = 1;
							enemyA[i].velocityX = 0;
							enemyA[i].positionX = 0;
							enemyA[i].velocityY = 0;
							enemyA[i].positionY = 0;
							spriteEnemyA[i].setPosition(0, 0);
							spriteBullet[j].setPosition(0, 0);
							bulletVisibility[j] = 0;
							score = score + 10;
						} 
						if (hitA[0] == 1 && hitA[1] == 1 && hitA[2] == 1 && hitA[3] == 1 && hitA[4] == 1)
						{
							start = false;
							win = true;
						}
					}
				}
			}
			std::stringstream ss;
			ss << score;
			Score.setString("Score : " + ss.str());

			std::stringstream streamTime;
			streamTime << remain;
			Time.setString("Time remaining : " + streamTime.str());

			if (remain <= 0)
			{
				win = false;
				start = false;
			}

			window.draw(Time);
			window.draw(Score);
			window.draw(borderUp);
			window.draw(borderDown);
			window.draw(borderLeft);
			window.draw(borderRight);
			Plane.Update(1);
			window.draw(spritePlane);
		}
		
		if (win == true)
		{
			sf::Font font;
			font.loadFromFile("fonts/SAOUITT-Regular.ttf");
			sf::Text text;
			text.setFont(font);
			text.setCharacterSize(100);
			text.setPosition(50, 50);
			text.setString("CONGRATULATIONS\nYOU WIN");
			text.setFillColor(sf::Color::Black);
			window.draw(text);

			std::stringstream ss;
			ss << score;
			Score.setFont(font);
			Score.setPosition(100, 1200);
			Score.setCharacterSize(100);
			Score.setFillColor(sf::Color::White);
			Score.setString("Your final score is " + ss.str());
			window.draw(Score);
		}

		if (win == false && start == false && menu == false)
		{
			sf::Font font;
			font.loadFromFile("fonts/SAOUITT-Regular.ttf");
			sf::Text text;
			text.setFont(font);
			text.setCharacterSize(100);
			text.setPosition(50, 50);
			text.setString("YOU LOSE\nBETTER LUCK NEXT TIME");
			text.setFillColor(sf::Color::Black);
			window.draw(text);

			std::stringstream ss;
			ss << score;
			Score.setFont(font);
			Score.setPosition(100, 1200);
			Score.setCharacterSize(100);
			Score.setFillColor(sf::Color::White);
			Score.setString("Your final score is " + ss.str());
			window.draw(Score);
		}
		window.display();
	}
	return 0;
}