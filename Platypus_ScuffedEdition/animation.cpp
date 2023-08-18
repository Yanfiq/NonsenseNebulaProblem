#include "animation.h"

std::vector<animationFrame*> animate::playing;


void animate::play(std::string texture_filename, int _row, int _collumn, sf::Vector2f _position) {
	sf::Texture* texture = textureManager::getTexture(texture_filename);
	animationFrame* animation = new animationFrame(texture, _row, _collumn, _position);
	playing.push_back(animation);
}

void animate::monitoringAnimation(sf::RenderWindow& window) {
	for (auto it = playing.begin(); it != playing.end();) {
		animationFrame* frame = *it;
		sf::RectangleShape* framenow = frame->getFrame();
		window.draw(*framenow);
		if (frame->isEnded()) {
			delete frame;
			it = playing.erase(it);
		}
		else {
			frame->updateFrame();
			it++;
		}
	}
}