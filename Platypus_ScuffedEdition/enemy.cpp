#include "enemy.h"

std::unordered_map<int, enemy*> enemy::enemy_map;
sf::Clock enemy::randomize;
int enemy::bullet_count = 1;

enemy::enemy(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY) : 
	object(_positionX, _positionY, _velocityX, _velocityY),
	HPBar(sf::Color::White, 2, sf::Color::Red, sf::Color::Green, MAX_ENEMY_HEALTH, textureManager::Instance()->getTexture(texture_filename)->getSize().x, textureManager::Instance()->getTexture(texture_filename)->getSize().y / 10)
{
	sf::Texture* texture = textureManager::Instance()->getTexture(texture_filename);
	object_sprite.setTexture(texture);
	object_sprite.setSize(sf::Vector2f(texture->getSize()));
	object_sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));

	float lowest, highest;
	if (_velocityX < _velocityY) {
		lowest = (_velocityX < 0) ? _velocityX : _velocityX * -1;
	}
	else {
		lowest = (_velocityY < 0) ? _velocityY : _velocityY * -1;
	}

	if (lowest == _velocityX || lowest == _velocityX * -1) {
		highest = (_velocityY > 0) ? _velocityY : _velocityY * -1;
	}
	else {
		highest = (_velocityX > 0) ? _velocityX : _velocityX * -1;
	}
	rangeVelocity = sf::Vector2f(lowest, highest);
	enemy_map[enemy_obj + _object_id] = this;
	animationManager::Instance()->play("gameplay_spawn.png", 4, 4, getPosition());
}

std::unordered_map<int, enemy*>* enemy::getEnemyMap() {
	return &enemy_map;
}

enemy* enemy::getObjectPtr(int id) {
	return (enemy_map.find(id) != enemy_map.end()) ? enemy_map[id] : NULL;
}

void enemy::deleteObject(int id) {
	animationManager::Instance()->play("gameplay_explode.png", 4, 5, sf::Vector2f(enemy_map[id]->getPosition().x, enemy_map[id]->getPosition().y));
	soundManager::Instance()->playSound("sfx_boom.ogg");
	delete enemy_map[id];
	enemy_map.erase(id);
}

void enemy::reduceHp(float damage) {
	hp -= damage;
}

float enemy::getHp() {	
	return hp;
}

sf::Vector2f* enemy::getBaseV() {
	return &rangeVelocity;
}

void enemy::shoot() {
	bullet* Bullet = new bullet(bullet_count, "gameplay_bullet_1.png", getPosition().x, getPosition().y, -900.0f, 0.0f);
	bullet_count = (bullet_count == 999) ? 0 : bullet_count + 1;

	Bullet->setDamageValue(20.0f);
}

void enemy::clearObject() {
	for (auto it = enemy_map.begin(); it != enemy_map.end();) {
		delete it->second;
		it = enemy_map.erase(it);
	}
}

void enemy::renderAllObject(double dt, sf::RenderWindow& window, bool Update) {
	for (const auto& it : enemy_map) {
		if (Update) {
			it.second->update(dt);
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
		}

		//more RNG
		if (randomize.getElapsedTime().asSeconds() > 5) {
			sf::Vector2f previousVelocity = it.second->getVelocity();
			it.second->setVelocity(RNG::generateRandomFloat(it.second->getBaseV()->x, it.second->getBaseV()->y), RNG::generateRandomFloat(it.second->getBaseV()->x, it.second->getBaseV()->y));
			std::unordered_map<int, enemy*>::iterator last = enemy_map.end(); last--;
			if (it.first == last->first) {
				std::cout << randomize.getElapsedTime().asSeconds() << std::endl;
				randomize.restart();
			}
		}

		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);
		it.second->HPBar.draw(window, it.second->getHp(), sf::Vector2f(it.second->getPosition().x, it.second->getPosition().y - it.second->getSprite()->getOrigin().y - 10));
	}
}