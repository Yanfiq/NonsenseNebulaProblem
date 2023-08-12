#include "enemy.h"

std::unordered_map<int, enemy*> enemy::enemy_map;
int enemy::bullet_count = 1;
sf::Texture enemy::texture;

enemy::enemy(int _object_id, float _positionX, float _positionY, float _velocityX, float _velocityY) : object(_positionX, _positionY, _velocityX, _velocityY){
	object_sprite.setTexture(&texture);
	object_sprite.setSize(sf::Vector2f(texture.getSize()));
	object_sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));

	enemy_map[enemy_obj + _object_id] = this;
}

void enemy::initializeTexture(std::string textureDir) {
	texture.loadFromFile(textureDir);
}

std::unordered_map<int, enemy*>* enemy::getEnemyMap() {
	return &enemy_map;
}

enemy* enemy::getObjectPtr(int id) {
	if (enemy_map.find(id) != enemy_map.end())
		return enemy_map[id];
	else
		return NULL;
}

void enemy::deleteObject(int id) {
	delete enemy_map[id];
	enemy_map.erase(id);
}

void enemy::reduceHp(float damage) {
	hp -= damage;
}

float enemy::getHp() {
	return hp;
}

void enemy::shoot(int& sfxVol) {
	bullet* Bullet = new bullet(bullet_count++, positionX, positionY, -0.5f, 0.0f);
	Bullet->setDamageValue(20.0f);
	if (bullet_count == 99)
		bullet_count = 0;
	sounds::playShootSound(sfxVol);
}

void enemy::clearObject() {
	for (auto it = enemy_map.begin(); it != enemy_map.end();) {
		delete it->second;
		it = enemy_map.erase(it);
	}
}

void enemy::updateNDrawAllObject(double dt, sf::RenderWindow& window) {
	for (const auto& it : enemy_map) {
		it.second->update(dt);

		if (it.second->getPositionY() >= 720 || it.second->getPositionY() <= 0) {
			it.second->setVelocity(it.second->getVelocityX(), it.second->getVelocityY() * -1);
			if (it.second->getPositionY() >= 720)
				it.second->setPosition(it.second->getPositionX(), 720);
			else if (it.second->getPositionY() <= 0)
				it.second->setPosition(it.second->getPositionX(), 0);
		}
		if (it.second->getPositionX() >= 1280 || it.second->getPositionX() <= 400) {
			it.second->setVelocity(it.second->getVelocityX() * -1, it.second->getVelocityY());
			if (it.second->getPositionX() <= 400)
				it.second->setPosition(400, it.second->getPositionY());
			else if (it.second->getPositionX() >= 1280)
				it.second->setPosition(1280, it.second->getPositionY());
		}
		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);
	}
}