#pragma once
#include "objects.h"
#include <unordered_map>
#include <iostream>

class bullet : public object {
protected:
	float damage = 20.0f;
	static std::unordered_map<int, bullet*> bullet_map;

public:
	bullet(int _object_id, float _positionX, float _positionY, float _velocityX, float _velocityY, float _width, float _height, float _gravity);

	float getDamageValue() const;
	void setDamageValue(float _damage);

	static std::unordered_map<int, bullet*>* getBulletMap();
	static bullet* getObjectPtr(int id);
	static void deleteObject(int id);

	static void clearObject();
	static void updateNDrawAllObject(double dt, sf::RenderWindow& window);
};