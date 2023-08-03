#pragma once
#include "objects.h"
#include <unordered_map>

class bullet : public object {
protected:
	float damage = 20.0f;
	static std::unordered_map<std::string, bullet*> bullet_map;

public:
	bullet(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);

	float getDamageValue() const;
	void setDamageValue(float _damage);

	static std::unordered_map<std::string, bullet*>* getBulletMap();
	static bullet* getObjectPtr(std::string id);
	static void deleteObject(std::string id);

	static void clearObject();
};