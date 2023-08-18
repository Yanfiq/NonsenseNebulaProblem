#pragma once
#include "SFML/Graphics.hpp"
#include "animationFrame.h"
#include "textureManager.h"

class animate {
private:
	static std::vector<animationFrame*> playing;

public:
	static void play(std::string texture_filename, int _row, int _collumn, sf::Vector2f _position);
	static void monitoringAnimation(sf::RenderWindow& window);
};