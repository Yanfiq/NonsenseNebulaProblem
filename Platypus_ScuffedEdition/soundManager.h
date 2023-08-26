#pragma once
#include "SFML/Audio.hpp"
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <iostream>

class soundManager {
private:
	static soundManager* pInstance;
	soundManager();
	int bgmVolume = 100;
	int sfxVolume = 100;

	std::vector<sf::Sound*> soundPlayed;
	std::vector<std::string> musicList;
	std::unordered_map<std::string, sf::SoundBuffer*> sounds_map;
	sf::Music* bgm;

public:
	static soundManager* Instance();
	void loadSound();
	void playSound(std::string fileName);

	// get the volume value
	// audio -> 1 = music & 2 = sfx
	int getVolume(int audio);
	//changing the volume
	// audio -> 1 = music & 2 = sfx
	// volume -> changing the volume relative to the current volume
	void changeVolume(int audio, int volume);
	void monitoring();
};