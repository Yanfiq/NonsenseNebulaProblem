#pragma once
#include "objects.h"
#include "bullet.h"
#include "sound.h"

class player : public object {
protected:
	static std::unordered_map<int, player*> player_map;
	static int allBullet;
	static sf::Texture texture;
	int bulletFired = 0;
	float hp = 100;

public:
	player(int _object_id, float _positionX, float _positionY, float _velocityX, float _velocityY);
	static player* getObjectPtr(int id);
	void shoot(int &sfxVol);
	void resetBulletCount();
	int getBulletCount();
	void thrustUp();
	void thrustDown();
	float getPlayerHp() const;
	void setPlayerHp(float _hp);
	void reducePlayerHp(float damage);
	void update(double time) override;
	
	static void deleteObject(int id);
	static void clearObject();
	static void initializeTexture(std::string textureDir);
	static std::unordered_map<int, player*>* getPlayerMap();
	static void updateNDrawAllObject(double dt, sf::RenderWindow& window);
};