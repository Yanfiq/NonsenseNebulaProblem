#pragma once

#include "SFML/Audio.hpp"
#include <vector>
#include <iostream>

extern int bgmVolume;
extern int sfxVolume;

class sounds {
private:
	static sf::SoundBuffer shootSound;
	static sf::SoundBuffer boomSound;
	static std::vector<sf::Sound*> soundPlayed;

public:
	static void loadSound();
	static void playShootSound();
	static void playBoomSound();
	static void monitoring();
};