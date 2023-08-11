#pragma once
#include "objects.h"

class bullet : public object {
protected:
	float damage = 20.0f;
	static std::unordered_map<int, bullet*> bullet_map;
	static sf::Texture texture;

public:
	bullet(int _object_id, float _positionX, float _positionY, float _velocityX, float _velocityY);

	float getDamageValue() const;
	void setDamageValue(float _damage);

	static std::unordered_map<int, bullet*>* getBulletMap();
	static bullet* getObjectPtr(int id);
	static void deleteObject(int id);
	static void initializeTexture(std::string textureDir);

	static void clearObject();
	static void updateNDrawAllObject(double dt, sf::RenderWindow& window);
};