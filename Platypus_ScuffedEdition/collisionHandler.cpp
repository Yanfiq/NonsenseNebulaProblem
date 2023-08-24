#include "collisionHandler.h"

int collisionHandler::handleCollision() {
	//collision detection and object removal
	std::unordered_map<int, bullet*>* bulletPlayerMap = bullet::getBulletMap(object::Type::playerBullet_obj);
	std::unordered_map<int, bullet*>* bulletEnemyMap = bullet::getBulletMap(object::Type::enemyBullet_obj);
	std::unordered_map<int, enemy*>* enemyMap = enemy::getEnemyMap();
	std::unordered_map<int, player*>* playerMap = player::getPlayerMap();

	int points = 0;
	//bullets from the player
	for (auto bullet_object = bulletPlayerMap->begin(); bullet_object != bulletPlayerMap->end(); bullet_object++) {
		for (auto enemy_object = enemyMap->begin(); enemy_object != enemyMap->end(); enemy_object++) {

			//collision happens between enemy and bullet
			if (object::isintersect(enemy_object->second->getSprite(), bullet_object->second->getSprite())) {
				enemy_object->second->reduceHp(bullet_object->second->getDamageValue());

				points += bullet_object->second->getDamageValue();
				if (enemy_object->second->getHp() <= 0) {
					enemy::deleteObject(enemy_object->first);
				}
				bullet::deleteObject(bullet_object->first);
				break;
			}
		}
	}

	//bullets from the enemy
	for (auto bullet_object = bulletEnemyMap->begin(); bullet_object != bulletEnemyMap->end(); bullet_object++) {
		for (auto player_object = playerMap->begin(); player_object != playerMap->end(); player_object++) {
			//collision happens between player and the bullet
			if (object::isintersect(player_object->second->getSprite(), bullet_object->second->getSprite())) {
				//add the bullet's id and player's id to the map
				player_object->second->reducePlayerHp(bullet_object->second->getDamageValue());

				points -= bullet_object->second->getDamageValue();
				if (player_object->second->getPlayerHp() <= 0) {
					player::deleteObject(player_object->first);
				}
				bullet::deleteObject(bullet_object->first);
				break;
			}
		}
	}
	return points;
}