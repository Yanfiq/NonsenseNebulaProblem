#include "textureManager.h"

std::unordered_map<std::string, sf::Texture*> textureManager::textures_map;
sf::RectangleShape textureManager::shape;

void textureManager::initializeTexture() {
	for (const auto& entry : std::filesystem::directory_iterator("images")) {
		sf::Texture* texture = new sf::Texture();
		std::string path = entry.path().generic_string();
		std::string filename = entry.path().filename().generic_string();
		texture->loadFromFile(path);
		textures_map[filename] = texture;
	}
}

sf::Texture* textureManager::getTexture(std::string filename) {
	if (textures_map.find(filename) != textures_map.end()) {
		return textures_map[filename];
	}
	return NULL;
}

void textureManager::displayImage(sf::RenderWindow& window, std::string texture_filename, float position_x, float position_y, sf::Vector2f size) {
	sf::Texture* texture = getTexture(texture_filename);
	shape.setSize(size);
	shape.setTexture(texture);
	shape.setPosition(position_x, position_y);
	shape.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	sf::Vector2f textureSize = static_cast<sf::Vector2f>(texture->getSize());

	sf::IntRect textureRect;
	textureRect.left = 0;
	textureRect.top = 0;

	if (size.x / size.y <= textureSize.x / textureSize.y) {
		textureRect.width = (textureSize.y / size.y) * size.x;
		textureRect.height = textureSize.y;
	}
	else if (size.x / size.y > textureSize.x / textureSize.y) {
		textureRect.width = textureSize.x;
		textureRect.height = (textureSize.x / size.x) * size.y;
	}
	else {
		textureRect.width = textureSize.x;
		textureRect.height = textureSize.y;
	}
	shape.setTextureRect(textureRect);
	window.draw(shape);
}