#include "animationFrame.h"

animationFrame::animationFrame(std::string textureDirectory, int _row, int _collumn, sf::Vector2f _position) {
	texture.loadFromFile(textureDirectory);
	frame.setTexture(&texture);
	frame.setPosition(_position);
	this->row = _row;
	this->collumn = _collumn;

	float frame_width = texture.getSize().x / _collumn;
	float frame_height = texture.getSize().y / _row;
	frameSize = sf::Vector2f(frame_width, frame_height);

	sf::IntRect textureRect(0, 0, frame_width, frame_height);
	frame.setTextureRect(textureRect);
}

void animationFrame::updateFrame() {
	int left = frame.getTextureRect().left;
	int top = frame.getTextureRect().top;
	//start play the next row
	if (left == frameSize.x * collumn - frameSize.x) {
		left = frameSize.x * -1;
		top += frameSize.y;
	}
	left += frame.getTextureRect().width;
	sf::IntRect textureRect(left, top, frameSize.x, frameSize.y);
	frame.setTextureRect(textureRect);
}

sf::RectangleShape* animationFrame::getFrame() {
	return &frame;
}

bool animationFrame::isEnded() {
	int left = frame.getTextureRect().left;
	int top = frame.getTextureRect().top;
	if (left == frameSize.x * collumn - frameSize.x && top == frameSize.y * row - frameSize.y)
		return true;
	return false;
}