#include "player.h"

std::unordered_map<int, player*> player::player_map;
int player::allBullet = 1;
textRenderer player::TextRenderer("fonts/Poppins-SemiBold.ttf");

player::player(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY) : object(_positionX, _positionY, _velocityX, _velocityY) {
	sf::Texture* texture = textureManager::getTexture(texture_filename);
	object_sprite.setTexture(texture);
	object_sprite.setSize(sf::Vector2f(texture->getSize()));
	object_sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
	
	player_map[player_obj + _object_id] = this;
}

player* player::getObjectPtr(int id) {
	if (player_map.find(id) == player_map.end())
		return NULL;
	return player_map[id];
}

void player::shoot(int &sfxVol) {
	bullet* Bullet = new bullet(allBullet++, "gameplay_bullet_2.png", positionX, positionY, 900, 0);
	bulletFired++;
	Bullet->setDamageValue(20.0f);
	sounds::playShootSound(sfxVol);
	if (allBullet == 99)
		allBullet = 0;
}

void player::resetBulletCount() {
	bulletFired = 0;
}

int player::getBulletCount() {
	if(this != NULL)
		return bulletFired;
}

void player::thrustUp() {
	setVelocity(getVelocityX(), getVelocityY() - 50.0f);
}

void player::thrustDown() {
	setVelocity(getVelocityX(), getVelocityY() + 50.0f);
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

void player::drawHpBar(sf::RenderWindow& window, float position_x, float position_y, float width, float height) {
	sf::RectangleShape rectangle;
	rectangle.setOutlineColor(sf::Color::White); 
	rectangle.setOutlineThickness(2);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setOrigin(sf::Vector2f(width / 2, height / 2));
	rectangle.setPosition(positionX, position_y);

	sf::RectangleShape hp_bar;
	hp_bar.setPosition(sf::Vector2f(rectangle.getPosition().x - rectangle.getOrigin().x, rectangle.getPosition().y - rectangle.getOrigin().y));
	hp_bar.setSize(sf::Vector2f(((this->hp / MAX_PLAYER_HEALTH) * width), height));
	if(this->hp >= MAX_PLAYER_HEALTH / 2)
		hp_bar.setFillColor(sf::Color::Green);
	else
		hp_bar.setFillColor(sf::Color::Red);

	window.draw(rectangle);
	window.draw(hp_bar);
}

std::unordered_map<int, player*>* player::getPlayerMap() {
	return &player_map;
}

void player::deleteObject(int id) {
	delete player_map[id];
	player_map.erase(id);
}

void player::clearObject() {
	for (auto it = player_map.begin(); it != player_map.end();) {
		delete it->second;
		it = player_map.erase(it);
	}
}

void player::update(double time) {
	positionY += velocityY * time;
	if (velocityY > 0)
		velocityY -= 5;
	if (velocityY < 0)
		velocityY += 5;
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
	
	//healing
	if (healTime.getElapsedTime().asSeconds() > 5) {
		healPlayer(10);
		healTime.restart();
	}
}

void player::updateNDrawAllObject(double dt, sf::RenderWindow& window) {
	for (const auto& it : player_map) {
		it.second->drawHpBar(window, it.second->getPositionX(), it.second->getPositionY() - it.second->getHeight() / 2 - 20, it.second->getWidth(), 10);
		it.second->update(dt);

		if (it.second->getPositionY() >= window.getSize().y) {
			it.second->setPosition(it.second->getPositionX(), window.getSize().y);
			it.second->setVelocity(it.second->getVelocityX(), it.second->getVelocityY() * -1 + 0.05);
		}
		else if (it.second->getPositionY() <= 0) {
			it.second->setPosition(it.second->getPositionX(), 0);
			it.second->setVelocity(it.second->getVelocityX(), it.second->getVelocityY() * -1 - 0.05);
		}
		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);

		std::string string = "player " + std::to_string(it.first - 100);
		float x = it.second->getPositionX() - it.second->getSprite()->getOrigin().x;
		float y = it.second->getPositionY() + it.second->getSprite()->getOrigin().y;
		TextRenderer.displayText(window, string, 20, sf::Color::White, x, y);
	}
}

void player::justDrawAllObject(sf::RenderWindow& window) {
	for (const auto& it : player_map) {
		it.second->drawHpBar(window, it.second->getPositionX(), it.second->getPositionY() - it.second->getHeight() / 2 - 20, it.second->getWidth(), 10);
		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);

		std::string string = "player " + std::to_string(it.first - 100);
		float x = it.second->getPositionX() - it.second->getSprite()->getOrigin().x;
		float y = it.second->getPositionY() + it.second->getSprite()->getOrigin().y;
		TextRenderer.displayText(window, string, 20, sf::Color::White, x, y);
	}
}