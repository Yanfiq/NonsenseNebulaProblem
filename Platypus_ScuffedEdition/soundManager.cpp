#include "soundManager.h"

std::vector<sf::Sound*> soundManager::soundPlayed;
std::unordered_map<std::string, sf::SoundBuffer*> soundManager::sounds_map;

int bgmVolume = 100;
int sfxVolume = 100;

void soundManager::loadSound() {
	for (const auto& entry : std::filesystem::directory_iterator("audio")) {
		// only load sfx to the map
		if (entry.path().filename().generic_string().substr(0, 3) == "sfx") {
			sf::SoundBuffer* sound = new sf::SoundBuffer();
			std::string path = entry.path().generic_string();
			std::string filename = entry.path().filename().generic_string();
			sound->loadFromFile(path);
			sounds_map[filename] = sound;
		}
	}
}

void soundManager::playSound(std::string fileName) {
	if (sounds_map.find(fileName) != sounds_map.end()) {
		sf::Sound* sound = new sf::Sound;
		sound->setBuffer(*sounds_map[fileName]);
		sound->setVolume(sfxVolume);
		sound->play();
		soundPlayed.push_back(sound);
	}
}

void soundManager::monitoring() {
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