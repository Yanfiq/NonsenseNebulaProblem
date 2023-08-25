#pragma once
#include "SFML/Audio.hpp"
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <iostream>

extern int bgmVolume;
extern int sfxVolume;

class soundManager {
private:
	static std::vector<sf::Sound*> soundPlayed;
	static std::unordered_map<std::string, sf::SoundBuffer*> sounds_map;

public:
	static void loadSound();
	static void playSound(std::string fileName);
	static void monitoring();
};