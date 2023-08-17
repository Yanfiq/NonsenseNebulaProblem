#include "textures.h"

std::unordered_map<std::string, sf::Texture*> textures::textures_map;

void textures::initializeTexture() {
	for (const auto& entry : std::filesystem::directory_iterator("images")) {
		sf::Texture* texture = new sf::Texture();
		std::string path = entry.path().generic_string();
		std::string filename = entry.path().filename().generic_string();
		texture->loadFromFile(path);
		textures_map[filename] = texture;
	}
}

sf::Texture* textures::getTexture(std::string filename) {
	if (textures_map.find(filename) != textures_map.end()) {
		return textures_map[filename];
	}
	else {
		return NULL;
	}
}

void textures::displayImage(sf::RenderWindow& window, sf::Texture* texture, float position_x, float position_y, sf::Vector2f size) {
	sf::RectangleShape shape;
	shape.setTexture(texture);
	shape.setPosition(position_x, position_y);
	sf::Vector2f textureSize = static_cast<sf::Vector2f>(texture->getSize());
	if (size.x == 0 && size.y == 0)
		shape.setSize(sf::Vector2f(textureSize));
	else if (size.x / size.y <= textureSize.x / textureSize.y)
		shape.setSize(sf::Vector2f((size.y / textureSize.y) * textureSize.x, size.y));
	else if (size.x / size.y > textureSize.x / textureSize.y)
		shape.setSize(sf::Vector2f(size.x, (size.x / textureSize.x) * textureSize.y));
	else
		shape.setSize(size);
	window.draw(shape);
}