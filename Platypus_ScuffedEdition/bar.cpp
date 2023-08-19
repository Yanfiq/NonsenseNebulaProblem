#include "bar.h"

bar::bar(sf::Color frameColor, int _frameThickness, sf::Color _low, sf::Color _normal, float _maxValue, float _width, float _height) {
	maxValue = _maxValue;
	low = _low;
	normal = _normal;

	frame.setOutlineColor(frameColor);
	frame.setOutlineThickness(_frameThickness);
	frame.setFillColor(sf::Color::Transparent);
	frame.setSize(sf::Vector2f(_width, _height));
	frame.setOrigin(sf::Vector2f(_width / 2, _height / 2));

	theBar.setFillColor(_normal);
	theBar.setSize(sf::Vector2f(_width, _height));
}

void bar::draw (sf::RenderWindow& window, float currentValue, sf::Vector2f position) {
	frame.setPosition(position);
	theBar.setPosition(position.x - frame.getOrigin().x, position.y - frame.getOrigin().y);
	theBar.setSize(sf::Vector2f(((currentValue / maxValue) * frame.getSize().x), frame.getSize().y));

	if (currentValue <= maxValue / 2)
		theBar.setFillColor(low);
	else
		theBar.setFillColor(normal);
	window.draw(frame);
	window.draw(theBar);
}