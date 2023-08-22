#include "enemy.h"

std::unordered_map<int, enemy*> enemy::enemy_map;
int enemy::bullet_count = 1;

enemy::enemy(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY) : 
	object(_positionX, _positionY, _velocityX, _velocityY),
	HPBar(sf::Color::White, 2, sf::Color::Red, sf::Color::Green, MAX_ENEMY_HEALTH, textureManager::getTexture(texture_filename)->getSize().x, textureManager::getTexture(texture_filename)->getSize().y / 10)
{
	sf::Texture* texture = textureManager::getTexture(texture_filename);
	object_sprite.setTexture(texture);
	object_sprite.setSize(sf::Vector2f(texture->getSize()));
	object_sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));

	enemy_map[enemy_obj + _object_id] = this;
}

std::unordered_map<int, enemy*>* enemy::getEnemyMap() {
	return &enemy_map;
}

enemy* enemy::getObjectPtr(int id) {
	return (enemy_map.find(id) != enemy_map.end()) ? enemy_map[id] : NULL;
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
	bullet* Bullet = new bullet(bullet_count, "gameplay_bullet_1.png", positionX, positionY, -900.0f, 0.0f);
	bullet_count = (bullet_count == 999) ? 0 : bullet_count + 1;

	Bullet->setDamageValue(20.0f);
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
		it.second->HPBar.draw(window, it.second->getHp(), sf::Vector2f(it.second->getPosition().x, it.second->getPosition().y - it.second->getSprite()->getOrigin().y - 10));

		if (it.second->getPosition().y > window.getSize().y || it.second->getPosition().y < 0) {
			it.second->setVelocity(it.second->getVelocity().x, it.second->getVelocity().y * -1);
			if (it.second->getPosition().y > window.getSize().y)
				it.second->setPosition(it.second->getPosition().x, window.getSize().y);
			else if (it.second->getPosition().y <= 0)
				it.second->setPosition(it.second->getPosition().x, 0);
		}
		if (it.second->getPosition().x > window.getSize().x || it.second->getPosition().x < 400) {
			it.second->setVelocity(it.second->getVelocity().x * -1, it.second->getVelocity().y);
			if (it.second->getPosition().x <= 400)
				it.second->setPosition(400, it.second->getPosition().y);
			else if (it.second->getPosition().x > window.getSize().x)
				it.second->setPosition(window.getSize().x, it.second->getPosition().y);
		}
		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);
	}
}

void enemy::justDrawAllObject(sf::RenderWindow& window) {
	for (const auto& it : enemy_map) {
		it.second->HPBar.draw(window, it.second->getHp(), sf::Vector2f(it.second->getPosition().x, it.second->getPosition().y - it.second->getSprite()->getOrigin().y - 10));
		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);
	}
}