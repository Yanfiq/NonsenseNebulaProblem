#include "animationFrame.h"

animationFrame::animationFrame(sf::Texture* texture, int _row, int _collumn, sf::Vector2f _position) {
	int frame_width = texture->getSize().x / _collumn;
	int frame_height = texture->getSize().y / _row;

	frame.setSize(sf::Vector2f(frame_width, frame_height));
	frame.setTexture(texture);
	frame.setOrigin(sf::Vector2f(frame_width / 2, frame_height / 2));
	frame.setPosition(_position);
	this->row = _row;
	this->collumn = _collumn;
	frameSize = sf::Vector2f(frame_width, frame_height);
	sf::IntRect textureRect(0, 0, frame_width, frame_height);
	frame.setTextureRect(textureRect);
}

void animationFrame::updateFrame() {
	int left = frame.getTextureRect().left;
	int top = frame.getTextureRect().top;

	//start play the next row
	if (left == frameSize.x * (collumn - 1)) {
		left = frameSize.x * -1;
		top += frameSize.y; //update the top value
	}

	//update the left value
	left += frame.getTextureRect().width;

	//update the texturerect
	sf::IntRect textureRect(left, top, frameSize.x, frameSize.y);
	frame.setTextureRect(textureRect);
}

sf::RectangleShape* animationFrame::getFrame() {
	return &frame;
}

bool animationFrame::isEnded() {
	int left = frame.getTextureRect().left;
	int top = frame.getTextureRect().top;
	return (left == frameSize.x * (collumn - 1) && top == frameSize.y * (row - 1)) ? true : false;
}