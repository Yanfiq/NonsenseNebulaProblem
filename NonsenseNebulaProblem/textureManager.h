#pragma once
#include "SFML/Graphics.hpp"
#include <filesystem>
#include <unordered_map>

class textureManager {
private:
	static textureManager* pInstance;
	textureManager();

	std::unordered_map<std::string, sf::Texture*> textures_map;
	sf::RectangleShape* shape;

public:
	static textureManager* Instance();
	void loadTexture();
	sf::Texture* getTexture(std::string filename);
	void displayImage(sf::RenderWindow& window, std::string texture_filename, float position_x, float position_y, sf::Vector2f size);
};