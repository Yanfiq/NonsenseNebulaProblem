#include "player.h"

std::unordered_map<int, player*> player::player_map;
int player::allBullet = 1;
sf::Texture player::texture;


player::player(int _object_id, float _positionX, float _positionY, float _velocityX, float _velocityY) : object(_positionX, _positionY, _velocityX, _velocityY) {
	object_sprite.setTexture(&texture);
	object_sprite.setSize(sf::Vector2f(texture.getSize()));
	object_sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
	
	player_map[player_obj + _object_id] = this;
}

void player::initializeTexture(std::string textureDir) {
	texture.loadFromFile(textureDir);
}

player* player::getObjectPtr(int id) {
	if (player_map.find(id) == player_map.end())
		return NULL;
	return player_map[id];
}

void player::shoot(int &sfxVol) {
	bullet* Bullet = new bullet(allBullet++, positionX, positionY, 0.5, 0);
	bulletFired++;
	Bullet->setDamageValue(20.0f);
	sounds::playShootSound(sfxVol);
}

void player::resetBulletCount() {
	allBullet -= 30;
	bulletFired = 0;
}

int player::getBulletCount() {
	if(this != NULL)
		return bulletFired;
}

void player::thrustUp() {
	setVelocity(getVelocityX(), getVelocityY() - 0.03f);
}

void player::thrustDown() {
	setVelocity(getVelocityX(), getVelocityY() + 0.03f);
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

void player::drawHpBar(sf::RenderWindow& window, float position_x, float position_y, float width, float height) {
	sf::RectangleShape rectangle;
	rectangle.setOutlineColor(sf::Color::White); 
	rectangle.setOutlineThickness(2);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setPosition(sf::Vector2f(position_x, position_y));
	rectangle.setSize(sf::Vector2f(width, height));

	sf::RectangleShape hp_bar;
	hp_bar.setPosition(sf::Vector2f(position_x, position_y));
	hp_bar.setSize(sf::Vector2f(((this->hp / 100) * width), height));
	if(this->hp >= 50)
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
		velocityY -= 0.002;
	if (velocityY < 0)
		velocityY += 0.002;
	object_sprite.setPosition(sf::Vector2f(positionX, positionY));
}

void player::updateNDrawAllObject(double dt, sf::RenderWindow& window) {
	for (const auto& it : player_map) {
		it.second->update(dt);

		if (it.second->getPositionY() >= 720) {
			it.second->setPosition(it.second->getPositionX(), 720);
			it.second->setVelocity(it.second->getVelocityX(), it.second->getVelocityY() * -1 + 0.05);
		}
		else if (it.second->getPositionY() <= 0) {
			it.second->setPosition(it.second->getPositionX(), 0);
			it.second->setVelocity(it.second->getVelocityX(), it.second->getVelocityY() * -1 - 0.05);
		}

		sf::RectangleShape* sprite = it.second->getSprite();
		window.draw(*sprite);
	}
}