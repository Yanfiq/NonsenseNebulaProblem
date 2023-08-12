#include "sound.h"

sf::SoundBuffer sounds::shootSound;
sf::SoundBuffer sounds::boomSound;
std::vector<sf::Sound*> sounds::soundPlayed;

void sounds::loadSound() {
	shootSound.loadFromFile("audio/shoot_2.ogg");
}

void sounds::playShootSound(int volume) {
	sf::Sound* sound = new sf::Sound;
	sound->setBuffer(shootSound);
	sound->setVolume(volume);
	sound->play();
	soundPlayed.push_back(sound);
}

void sounds::checkAndDeleteSound() {
	for (auto it = soundPlayed.begin(); it != soundPlayed.end();) {
		sf::Sound* sound = *it;
		if (sound->getStatus() == sf::SoundSource::Status::Stopped) {
			delete *it;
			it = soundPlayed.erase(it);
		}
		else {
			it++;
		}
	}
}