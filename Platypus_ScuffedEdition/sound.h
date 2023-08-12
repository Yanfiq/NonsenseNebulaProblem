#pragma once

#include "SFML/Audio.hpp"
#include <vector>

class sounds {
private:
	static sf::SoundBuffer shootSound;
	static sf::SoundBuffer boomSound;
	static std::vector<sf::Sound*> soundPlayed;

public:
	static void loadSound();
	static void playShootSound(int volume);
	static void checkAndDeleteSound();
	//static void playBoomSound();
};