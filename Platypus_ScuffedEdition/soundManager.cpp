#include "soundManager.h"

soundManager* soundManager::pInstance = NULL;

soundManager* soundManager::Instance() {
	if (pInstance == NULL)
		pInstance = new soundManager;

	return pInstance;
}

soundManager::soundManager(){
	bgm = new sf::Music;
}

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
		else if (entry.path().filename().generic_string().substr(0, 3) == "bgm") {
			musicList.push_back(entry.path().filename().generic_string());
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

void soundManager::changeVolume(int audio, int volume) {
	if (audio == 1) {
		bgmVolume += volume;
		if (bgmVolume < 0)bgmVolume = 0;
		if (bgmVolume > 100)bgmVolume = 100;
		bgm->setVolume(bgmVolume);
	}
	else if (audio == 2) {
		sfxVolume += volume;
		if (sfxVolume < 0)sfxVolume = 0;
		if (sfxVolume > 100)sfxVolume = 100;
	}
}

int soundManager::getVolume(int audio) {
	return (audio == 1) ? bgmVolume : sfxVolume;
}

void soundManager::monitor() {
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
	if (bgm->getStatus() == sf::SoundSource::Stopped) {
		static int playing = 0;
		std::string filename = "audio/" + musicList[playing++];
		bgm->openFromFile(filename);
		bgm->play();
		bgm->setVolume(bgmVolume);
		if (playing == musicList.size()) playing = 0;
	}
}