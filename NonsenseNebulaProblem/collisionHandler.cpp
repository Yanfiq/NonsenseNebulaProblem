#include "collisionHandler.h"

//int collisionHandler::handleCollision(sf::RenderWindow& window) {
//	//collision detection and object removal
//	std::unordered_map<int, bullet*>* bulletPlayerMap = bullet::getBulletMap(object::Type::playerBullet_obj);
//	std::unordered_map<int, bullet*>* bulletEnemyMap = bullet::getBulletMap(object::Type::enemyBullet_obj);
//	std::unordered_map<int, enemy*>* enemyMap = enemy::getEnemyMap();
//	std::unordered_map<int, player*>* playerMap = player::getPlayerMap();
//
//	int points = 0;
//	//bullets from the player
//	for (auto bullet_object = bulletPlayerMap->begin(); bullet_object != bulletPlayerMap->end();) {
//		bool collide = false;
//		bullet* Bullet = bullet_object->second;
//		for (auto enemy_object = enemyMap->begin(); enemy_object != enemyMap->end(); enemy_object++) {
//
//			//collision occurs between the enemy and the player's bullet
//			if (object::isintersect(enemy_object->second->getSprite(), bullet_object->second->getSprite())) {
//
//				//Increase points and reduce enemy's HP
//				enemy_object->second->reduceHp(bullet_object->second->getDamageValue());
//				points += bullet_object->second->getDamageValue();
//
//				//Remove enemiy if HP is below 0
//				if (enemy_object->second->getHp() <= 0) {
//					enemy::deleteObject(enemy_object->first);
//				}
//				
//				//remove the bullet and move the bullet's map iterator
//				delete bullet_object->second;
//				bullet_object = bulletPlayerMap->erase(bullet_object);
//				collide = true;
//				break;
//			}
//		}
//
//		//if there is a collision, don't shift the iterator, 
//		//because it has been shifted inside the innermost for loop
//		if (!collide)
//			++bullet_object;
//	}
//
//	//bullets from the enemy
//	for (auto bullet_object = bulletEnemyMap->begin(); bullet_object != bulletEnemyMap->end();) {
//		bool collide = false;
//		for (auto player_object = playerMap->begin(); player_object != playerMap->end(); player_object++) {
//
//			//collision occurs between the player and the enemy's bullet
//			if (object::isintersect(player_object->second->getSprite(), bullet_object->second->getSprite())) {
//
//				//reduce player's HP
//				player_object->second->reducePlayerHp(bullet_object->second->getDamageValue());
//
//				if (player_object->second->getPlayerHp() <= 0) {
//					player::deleteObject(player_object->first);
//				}
//
//				//remove the bullet and move the bullet's map iterator
//				delete bullet_object->second;
//				bullet_object = bulletEnemyMap->erase(bullet_object);
//				collide = true;
//				break;
//			}
//		}
//
//		//if there is a collision, don't shift the iterator, 
//		//because it has been shifted inside the innermost for loop
//		if(!collide)
//			++bullet_object;	
//	}
//	return points;
//}

//int collisionHandler::handleCollision(sf::RenderWindow& window) {
//	std::unordered_map<int, bullet*>* bulletPlayerMap = bullet::getBulletMap(object::Type::playerBullet_obj);
//	std::unordered_map<int, bullet*>* bulletEnemyMap = bullet::getBulletMap(object::Type::enemyBullet_obj);
//	std::unordered_map<int, enemy*>* enemyMap = enemy::getEnemyMap();
//	std::unordered_map<int, player*>* playerMap = player::getPlayerMap();
//
//	QuadtreeNode quadtree(0, 0, window.getSize().x, window.getSize().y, window);
//
//	for (auto it = bulletPlayerMap->begin(); it != bulletPlayerMap->end(); it++) {
//		quadtree.insert(it->first, static_cast<object*>(it->second));
//	}
//	for (auto it = bulletEnemyMap->begin(); it != bulletEnemyMap->end(); it++) {
//		quadtree.insert(it->first, static_cast<object*>(it->second));
//	}
//	for (auto it = playerMap->begin(); it != playerMap->end(); it++) {
//		quadtree.insert(it->first, static_cast<object*>(it->second));
//	}
//	for (auto it = enemyMap->begin(); it != enemyMap->end(); it++) {
//		quadtree.insert(it->first, static_cast<object*>(it->second));
//	}
//
//	quadtree.displayQuadtreeVisual();
//	quadtree.checkCollision();
//	return 0;
//}

int collisionHandler::handleCollision(sf::RenderWindow& window) {
	QuadtreeNode::root->checkCollision();
	return 0;
}