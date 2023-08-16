#include "Images.h"

namespace img {
	sf::Texture texture::background;
	sf::Texture texture::keyboardLeft;
	sf::Texture texture::keyboardRight;
	sf::Texture texture::spacebarKey;


	void initializeTexture() {
		texture::background.loadFromFile("images/nebula.jpg");
		texture::keyboardLeft.loadFromFile("images/wasd.jpg");
		texture::keyboardRight.loadFromFile("images/arrows.jpg");
		texture::spacebarKey.loadFromFile("images/spacebar.jpg");
		//std::string path = "images";
		//for (const auto& entry : std::filesystem::directory_iterator(path)) {
		//	std::cout << entry.path().filename() << std::endl;
		//}
	}

	void displayImage(sf::RenderWindow& window, sf::Texture texture, float position_x, float position_y, sf::Vector2f size) {
		sf::RectangleShape shape;
		shape.setTexture(&texture);
		shape.setPosition(position_x, position_y);
		sf::Vector2f textureSize = static_cast<sf::Vector2f>(texture.getSize());
		if (size.x == 0 && size.y == 0)
			shape.setSize(sf::Vector2f(textureSize));
		else if(size.x / size.y <= textureSize.x / textureSize.y)
			shape.setSize(sf::Vector2f((size.y/textureSize.y) * textureSize.x, size.y));
		else if (size.x / size.y > textureSize.x / textureSize.y)
			shape.setSize(sf::Vector2f(size.x, (size.x / textureSize.x) * textureSize.y));
		else
			shape.setSize(size);
		window.draw(shape);
	}
}