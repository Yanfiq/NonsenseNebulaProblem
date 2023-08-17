#pragma once
#include "SFML/Graphics.hpp"
#include "animationFrame.h"

class animate {
private:
	static std::vector<animationFrame*> playing;

public:
	static void play(sf::Texture* texture, int _row, int _collumn, sf::Vector2f _position);
	static void monitoringAnimation(sf::RenderWindow& window);
};