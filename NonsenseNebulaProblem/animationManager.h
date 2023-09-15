#pragma once
#include "SFML/Graphics.hpp"
#include "animationFrame.h"
#include "textureManager.h"

class animationManager {
private:
	static animationManager* pInstance;
	animationManager();

	std::vector<animationFrame*> playing;

public:
	static animationManager* Instance();
	void play(std::string texture_filename, int _row, int _collumn, sf::Vector2f _position);
	void monitor(sf::RenderWindow& window);
};