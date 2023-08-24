#pragma once
#include "objects.h"
#include "bullet.h"
#include "sound.h"
#include "Text.h"
#include "bar.h"
#include "textureManager.h"
#define MAX_PLAYER_HEALTH 200
#define MAX_PLAYER_BULLET 30

class player : public object {
protected:
	static std::unordered_map<int, player*> player_map;
	static int allBullet;
	static textRenderer TextRenderer;

	int bulletAvailable = MAX_PLAYER_BULLET;
	float hp = MAX_PLAYER_HEALTH;
	sf::Clock healTime;
	bar HPBar;

public:
	player(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY);

	// returns a pointer to the object with the specified id
	static player* getObjectPtr(int id);

	// constructs a bullet type object with the sound of the shot, its volume based on the function argument
	void shoot(int &sfxVol);

	// resets the bullet_count variable
	void reloadBullet(int num);

	// returns a bullet_count variable with integer data type
	int getBulletRemain();

	// 
	void thrustUp();
	void thrustDown();
	float getPlayerHp() const;
	bar bulletBar;
	void setPlayerHp(float _hp);
	void reducePlayerHp(float damage);
	void healPlayer(float addHp);
	void update(float time) override;
	
	static void deleteObject(int id);
	static void clearObject();
	static std::unordered_map<int, player*>* getPlayerMap();
	static void updateNDrawAllObject(double dt, sf::RenderWindow& window);
	static void justDrawAllObject(sf::RenderWindow& window);
};