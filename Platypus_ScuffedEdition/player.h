#pragma once
#include "objects.h"
#include "bullet.h"
#include "sound.h"
#include "Text.h"
#include "textures.h"
#define MAX_PLAYER_HEALTH 200

class player : public object {
protected:
	static std::unordered_map<int, player*> player_map;
	static int allBullet;
	int bulletFired = 0;
	float hp = MAX_PLAYER_HEALTH;
	static textRenderer TextRenderer;

public:
	player(int _object_id, sf::Texture* texture, float _positionX, float _positionY, float _velocityX, float _velocityY);
	static player* getObjectPtr(int id);
	void shoot(int &sfxVol);
	void resetBulletCount();
	int getBulletCount();
	void thrustUp();
	void thrustDown();
	float getPlayerHp() const;
	void setPlayerHp(float _hp);
	void reducePlayerHp(float damage);
	void healPlayer(float addHp);
	void update(double time) override;
	void drawHpBar(sf::RenderWindow& window, float position_x, float position_y, float width, float height);
	
	static void deleteObject(int id);
	static void clearObject();
	static std::unordered_map<int, player*>* getPlayerMap();
	static void updateNDrawAllObject(double dt, sf::RenderWindow& window);
};