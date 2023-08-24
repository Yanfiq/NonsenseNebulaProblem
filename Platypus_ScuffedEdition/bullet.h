#pragma once
#include "objects.h"
#include "textureManager.h"

class bullet : public object {
protected:
	float damage = 20.0f;
	static std::unordered_map<int, bullet*> enemyBullet_map;
	static std::unordered_map<int, bullet*> playerBullet_map;

public:
	bullet(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY);

	float getDamageValue() const;
	void setDamageValue(float _damage);

	static std::unordered_map<int, bullet*>* getBulletMap(int objectType);
	static bullet* getObjectPtr(int id);
	static void deleteObject(int id);

	static void clearObject();
	static void updateNDrawAllObject(double dt, sf::RenderWindow& window, int objectType);
	static void justDrawAllObject(sf::RenderWindow& window, int objectType);
};