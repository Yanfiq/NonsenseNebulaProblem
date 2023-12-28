#include "player.h"

std::unordered_map<int, player*> player::player_map;
int player::allBullet = 1;
textRenderer player::TextRenderer("fonts/Poppins-SemiBold.ttf");

player::player(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY) : 
	object(_positionX, _positionY, _velocityX, _velocityY), 
	HPBar(sf::Color::White, 2, sf::Color::Red, sf::Color::Green, MAX_PLAYER_HEALTH, textureManager::Instance()->getTexture(texture_filename)->getSize().x, textureManager::Instance()->getTexture(texture_filename)->getSize().y/10),
	bulletBar(sf::Color::White, 2, sf::Color::Red, sf::Color::Green, MAX_PLAYER_BULLET, 200, 30)
{
	sf::Texture* texture = textureManager::Instance()->getTexture(texture_filename);
	object_sprite.setTexture(texture);
	object_sprite.setSize(sf::Vector2f(texture->getSize()));
	object_sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
	
	player_map[player_obj + _object_id] = this;
	animationManager::Instance()->play("gameplay_spawn.png", 4, 4, getPosition());

	QuadtreeNode::root->insert(player_obj + _object_id, static_cast<object*>(this));
}

player* player::getObjectPtr(int id) {
	return (player_map.find(id) != player_map.end()) ? player_map[id] : NULL;
}

void player::shoot() {
	if (allowedFire) {
		allowedFire = false;
		attackTimer.restart();
		bullet* Bullet = new bullet(allBullet++, "gameplay_bullet_2.png", getPosition().x, getPosition().y, 900, 0);
		bulletAvailable--;
		Bullet->setDamageValue(20.0f);
		if (allBullet == 999)
			allBullet = 0;
	}
}

void player::reloadBullet(int num) {
	bulletAvailable += num;
}

int player::getBulletRemain() {
	return bulletAvailable;
}

void player::thrustUp() {
	setVelocity(getVelocity().x, getVelocity().y - 50.0f);
}

void player::thrustDown() {
	setVelocity(getVelocity().x, getVelocity().y + 50.0f);
}

float player::getPlayerHp() const {
	return this->hp;
}

void player::setPlayerHp(float _hp) {
	this->hp = _hp;
}

void player::reducePlayerHp(float damage) {
	this->hp -= damage;
}

void player::healPlayer(float addHp) {
	this->hp += addHp;
	if (this->hp > MAX_PLAYER_HEALTH)
		this->hp = MAX_PLAYER_HEALTH;
}

std::unordered_map<int, player*>* player::getPlayerMap() {
	return &player_map;
}

void player::deleteObject(int id) {
	animationManager::Instance()->play("gameplay_explode.png", 4, 5, sf::Vector2f(player_map[id]->getPosition().x, player_map[id]->getPosition().y));
	soundManager::Instance()->playSound("sfx_boom.ogg");
	QuadtreeNode::root->erase(id, static_cast<object*>(player_map[id]));
	delete player_map[id];
	player_map.erase(id);
}

void player::clearObject() {
	for (auto it = player_map.begin(); it != player_map.end();) {
		QuadtreeNode::root->erase(it->first, static_cast<object*>(it->second));
		delete it->second;
		it = player_map.erase(it);
	}
}

void player::update(float time) {
	if (velocityY > 0)
		velocityY -= 5;
	if (velocityY < 0)
		velocityY += 5;
	object_sprite.move(0, velocityY * time);
	
	//healing
	if (healTime.getElapsedTime().asSeconds() > 5) {
		healPlayer(10);
		healTime.restart();
	}

	//attack cooldown
	if (attackTimer.getElapsedTime() >= attackCooldown) {
		allowedFire = true;
	}
}

void player::renderAllObject(double dt, sf::RenderWindow& window, bool Update) {
	for (const auto& it : player_map) {
		if (Update) {
			QuadtreeNode::root->erase(it.first, it.second);
			it.second->update(dt);
			if (it.second->getPosition().y >= window.getSize().y) {
				it.second->setPosition(it.second->getPosition().x, window.getSize().y);
				it.second->setVelocity(it.second->getVelocity().x, it.second->getVelocity().y * -1 + 0.05);
			}
			else if (it.second->getPosition().y <= 0) {
				it.second->setPosition(it.second->getPosition().x, 0);
				it.second->setVelocity(it.second->getVelocity().x, it.second->getVelocity().y * -1 - 0.05);
			}
			QuadtreeNode::root->insert(it.first, it.second);
		}

		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);

		std::string string = "player " + std::to_string(it.first - player_obj);
		float x = it.second->getPosition().x;
		float y = it.second->getPosition().y + it.second->getSprite()->getOrigin().y;
		TextRenderer.displayText(window, string, 1, 20, sf::Color::White, x, y);
		it.second->HPBar.draw(window, it.second->getPlayerHp(), sf::Vector2f(it.second->getPosition().x, it.second->getPosition().y - it.second->getSprite()->getOrigin().y - 10));
	}
}