#include "Images.h"

namespace img {
	sf::Texture texture::background;
	sf::Texture texture::keyboardLeft;
	sf::Texture texture::keyboardRight;
	sf::Texture texture::spacebarKey;


	void initializeTexture() {
		texture::background.loadFromFile("images/nebula.jpg");
		texture::keyboardLeft.loadFromFile("images/wasd.jpg");
		texture::keyboardRight.loadFromFile("images/updownleftright.jpg");
		texture::spacebarKey.loadFromFile("images/spacebar.jpg");
	}

	void displayImage(sf::RenderWindow& window, sf::Texture texture, float position_x, float position_y) {
		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(texture.getSize()));
		shape.setTexture(&texture);
		shape.setPosition(position_x, position_y);
		window.draw(shape);
	}
}