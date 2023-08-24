#include "sound.h"

sf::SoundBuffer sounds::shootSound;
sf::SoundBuffer sounds::boomSound;
std::vector<sf::Sound*> sounds::soundPlayed;

int bgmVolume = 100;
int sfxVolume = 100;

void sounds::loadSound() {
	shootSound.loadFromFile("audio/sfx_shoot.ogg");
	boomSound.loadFromFile("audio/sfx_boom.ogg");
}

void sounds::playShootSound() {
	sf::Sound* sound = new sf::Sound;
	sound->setBuffer(shootSound);
	sound->setVolume(sfxVolume);
	sound->play();
	soundPlayed.push_back(sound);
}

void sounds::playBoomSound() {
	sf::Sound* sound = new sf::Sound;
	sound->setBuffer(boomSound);
	sound->setVolume(sfxVolume);
	sound->play();
	soundPlayed.push_back(sound);
}

void sounds::monitoring() {
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