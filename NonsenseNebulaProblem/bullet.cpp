#include "bullet.h"

std::unordered_map<int, bullet*> bullet::enemyBullet_map;
std::unordered_map<int, bullet*> bullet::playerBullet_map;

bullet::bullet(int _object_id, std::string texture_filename, float _positionX, float _positionY, float _velocityX, float _velocityY) : object(_positionX, _positionY, _velocityX, _velocityY) {
	sf::Texture* texture = textureManager::Instance()->getTexture(texture_filename);
	object_sprite.setTexture(texture);
	object_sprite.setSize(sf::Vector2f(texture->getSize()));
	object_sprite.setOrigin(sf::Vector2f(texture->getSize().x / 2, texture->getSize().y / 2));
	
	float left = object_sprite.getPosition().x - object_sprite.getOrigin().x;
	float top = object_sprite.getPosition().y - object_sprite.getOrigin().y;
	float width = object_sprite.getSize().x;
	float height = object_sprite.getSize().y;
	before_state = sf::FloatRect(left, top, width, height);

	if (velocityX > 0.0f) {
		playerBullet_map[playerBullet_obj + _object_id] = this;
		QuadtreeNode::root->insert(playerBullet_obj + _object_id, static_cast<object*>(this));
	}
	else if (velocityX < 0.0f) {
		enemyBullet_map[enemyBullet_obj + _object_id] = this;
		QuadtreeNode::root->insert(enemyBullet_obj + _object_id, static_cast<object*>(this));
	}
	soundManager::Instance()->playSound("sfx_shoot.ogg");
}

bullet* bullet::getObjectPtr(int id) {
	if(id - enemyBullet_obj > 0 && id - enemyBullet_obj < 1000)
		return (enemyBullet_map.find(id) != enemyBullet_map.end()) ? enemyBullet_map[id] : NULL;
	else if (id - playerBullet_obj > 0 && id - playerBullet_obj < 1000)
		return (playerBullet_map.find(id) != playerBullet_map.end()) ? playerBullet_map[id] : NULL;
	else
		return NULL;
}

float bullet::getDamageValue() const {
	return (this != NULL) ? this->damage : NULL;
}

void bullet::setDamageValue(float _damage) {
	this->damage = _damage;
}

std::unordered_map<int, bullet*>* bullet::getBulletMap(int objectType) {
	return (objectType == enemyBullet_obj) ? &enemyBullet_map : &playerBullet_map;
}

void bullet::deleteObject(int id) {
	if (getObjectPtr(id) == NULL) return;
	if (id - enemyBullet_obj > 0 && id - enemyBullet_obj < 1000) {
		QuadtreeNode::root->erase(id, enemyBullet_map[id]->before_state);
		QuadtreeNode::root->erase(id, static_cast<object*>(enemyBullet_map[id]));
		delete enemyBullet_map[id];
		enemyBullet_map.erase(id);
	}
	else if (id - playerBullet_obj > 0 && id - playerBullet_obj < 1000) {
		QuadtreeNode::root->erase(id, playerBullet_map[id]->before_state);
		QuadtreeNode::root->erase(id, static_cast<object*>(playerBullet_map[id]));
		delete playerBullet_map[id];
		playerBullet_map.erase(id);
	}
}

void bullet::clearObject() {
	for (auto it = enemyBullet_map.begin(); it != enemyBullet_map.end();) {
		QuadtreeNode::root->erase(it->first, it->second->before_state);
		QuadtreeNode::root->erase(it->first, static_cast<object*>(it->second));
		delete it->second;
		it = enemyBullet_map.erase(it);
	}
	for (auto it = playerBullet_map.begin(); it != playerBullet_map.end();) {
		QuadtreeNode::root->erase(it->first, it->second->before_state);
		QuadtreeNode::root->erase(it->first, static_cast<object*>(it->second));
		delete it->second;
		it = playerBullet_map.erase(it);
	}
}

void bullet::renderAllObject(double dt, sf::RenderWindow& window, int objectType, bool Update) {
	std::unordered_map<int, bullet*>* map = (objectType == enemyBullet_obj) ? &enemyBullet_map : &playerBullet_map;
	for (auto it = map->begin(); it != map->end();) {
		if (Update) {
			//QuadtreeNode::root->erase(it->first, static_cast<object*>(it->second));
			it->second->update(dt);
			//QuadtreeNode::root->insert(it->first, static_cast<object*>(it->second));
			float x = it->second->before_state.getPosition().x + it->second->getSprite()->getSize().x / 2;
			float y = it->second->before_state.getPosition().y + it->second->getSprite()->getSize().y / 2;
			sf::Vector2f old_position(x, y);
			sf::Vector2f new_position = it->second->getSprite()->getPosition();
			sf::Vector2f threshold = it->second->getSprite()->getSize();
			if ((fabs(old_position.x - new_position.x) >= threshold.x / 2) ||
				(fabs(old_position.y - new_position.y) >= threshold.y / 2)) {
				QuadtreeNode::root->erase(it->first, it->second->before_state);
				QuadtreeNode::root->insert(it->first, static_cast<object*>(it->second));

				float left = it->second->object_sprite.getPosition().x - it->second->object_sprite.getOrigin().x;
				float top = it->second->object_sprite.getPosition().y - it->second->object_sprite.getOrigin().y;
				float width = it->second->object_sprite.getSize().x;
				float height = it->second->object_sprite.getSize().y;
				it->second->before_state = sf::FloatRect(left, top, width, height);
			}
		}
		sf::RectangleShape* sprite = it->second->getSprite();
		window.draw(*sprite);

		if (it->second->getPosition().x < 0 || it->second->getPosition().x > window.getSize().x) {
			QuadtreeNode::root->erase(it->first, it->second->before_state);
			delete it->second;
			it = (objectType == enemyBullet_obj) ? enemyBullet_map.erase(it) : playerBullet_map.erase(it);
		}
		else {
			it++;
		}
	}
}