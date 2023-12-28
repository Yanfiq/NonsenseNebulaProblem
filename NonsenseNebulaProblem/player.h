#pragma once
#include "objects.h"
#include "bullet.h"
#include "Text.h"
#include "bar.h"
#include "textureManager.h"
#include "soundManager.h"
#include "animationManager.h"
#include "QuadtreeNode.h"
#define MAX_PLAYER_HEALTH 400
#define MAX_PLAYER_BULLET 40

class player : public object {
protected:
	static std::unordered_map<int, player*> player_map;
	static int allBullet;
	static textRenderer TextRenderer;

	int bulletAvailable = MAX_PLAYER_BULLET;
	float hp = MAX_PLAYER_HEALTH;
	sf::Clock healTime;
	sf::Clock attackTimer;
	sf::Time attackCooldown = sf::milliseconds(150);
	bool allowedFire = false;
	bar HPBar;

public:
	player(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY);
	bar bulletBar;

	// returns a pointer to the object with the specified id
	static player* getObjectPtr(int id);

	// constructs a bullet type object with the sound of the shot
	void shoot();

	// resets the bullet_count variable
	void reloadBullet(int num);

	// returns a bullet_count variable with integer data type
	int getBulletRemain();

	void thrustUp();
	void thrustDown();
	float getPlayerHp() const;
	void setPlayerHp(float _hp);
	void reducePlayerHp(float damage);
	void healPlayer(float addHp);
	void update(float time) override;
	
	static void deleteObject(int id);
	static void clearObject();
	static std::unordered_map<int, player*>* getPlayerMap();
	static void renderAllObject(double dt, sf::RenderWindow& window, bool Update);
};