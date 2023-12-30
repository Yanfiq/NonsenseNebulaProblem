#include "QuadtreeNode.h"

QuadtreeNode* QuadtreeNode::root = nullptr;
sf::Clock QuadtreeNode::timer;
sf::Time QuadtreeNode::cleanTime = sf::seconds(60);

QuadtreeNode::QuadtreeNode(double _x, double _y, double _width, double _height, sf::RenderWindow& _window) : x(_x), y(_y), width(_width), height(_height), window(_window) {
    if (root == nullptr) {
        root = this;
        this->depth = 0;
    }
    children.resize(4, nullptr);
}

QuadtreeNode::~QuadtreeNode() {
    for (int i = 0; i < children.size(); i++) {
        if (children[i] != nullptr) delete children[i];
    }
}

void QuadtreeNode::insert(int id, object* Object) {
    if (Object == nullptr) return;
    if (!hasChild || depth == MAX_DEPTH) objects[id] = Object;
    if ((objects.size() <= MAX_OBJECT_PER_NODE && !hasChild) || depth == MAX_DEPTH) return;

    if (!hasChild && depth < MAX_DEPTH) {
        children[0] = new QuadtreeNode(x, y, width / 2, height / 2, window);
        children[1] = new QuadtreeNode(x + width / 2, y, width / 2, height / 2, window);
        children[2] = new QuadtreeNode(x, y + height / 2, width / 2, height / 2, window);
        children[3] = new QuadtreeNode(x + width / 2, y + height / 2, width / 2, height / 2, window);

        for (int i = 0; i < children.size(); i++) {
            children[i]->parent = this;
            children[i]->depth = depth + 1;
        }

        hasChild = true;

        //redistribute object to child node
        for (auto object = objects.begin(); object != objects.end();) {
            for (int i = 0; i < children.size(); ++i) {
                if (object->second->getSprite()->getGlobalBounds().intersects(sf::FloatRect(children[i]->x, children[i]->y, children[i]->width, children[i]->height))) {
                    children[i]->insert(object->first, object->second);
                }
            }
            object = objects.erase(object);
        }
        return;
    }

    sf::RectangleShape* sprite = Object->getSprite();
    for (int i = 0; i < 4; ++i) {
        if (sprite->getGlobalBounds().intersects(sf::FloatRect(children[i]->x, children[i]->y, children[i]->width, children[i]->height))) {
            children[i]->insert(id, Object);
        }
    }
}

void QuadtreeNode::erase(int id, object* Object) {
    if (Object == nullptr) return;
    if (!hasChild) {
        objects.erase(id);
        return;
    }

    sf::RectangleShape* sprite = Object->getSprite();
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == nullptr) return;
        if (sprite->getGlobalBounds().intersects(sf::FloatRect(this->children[i]->x, this->children[i]->y, this->children[i]->width, this->children[i]->height))) {
            children[i]->erase(id, Object);
        }
    }

    if (getObjects().size() <= MAX_OBJECT_PER_NODE) {
        objects = getObjects();
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
        children.clear();
        children.resize(4, nullptr);
        hasChild = false;
    }
    //root->normalize();
}

void QuadtreeNode::erase(int id, sf::FloatRect Object) {
    if (!hasChild) {
        objects.erase(id);
        return;
    }

    for (int i = 0; i < children.size(); i++) {
        if (children[i] == nullptr) return;
        if (Object.intersects(sf::FloatRect(this->children[i]->x, this->children[i]->y, this->children[i]->width, this->children[i]->height))) {
            children[i]->erase(id, Object);
        }
    }

    if (getObjects().size() <= MAX_OBJECT_PER_NODE) {
        objects = getObjects();
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
        children.clear();
        children.resize(4, nullptr);
        hasChild = false;
    }
    //root->normalize();
}

void QuadtreeNode::normalize() {
    if (!hasChild) {
        return;
    }

    if (getObjects().size() <= MAX_OBJECT_PER_NODE) {
        objects = getObjects();
        for (int i = 0; i < children.size(); i++) {
            children[i]->hasChild = false;
            delete children[i];
        }
        children.clear();
        children.resize(4, nullptr);
        hasChild = false;
    }
    else {
        for (int i = 0; i < children.size(); i++) {
            children[i]->normalize();
        }
    }
}

std::map<int, object*> QuadtreeNode::getObjects() {
    if (!hasChild) {
        return objects;
    }

    std::map<int, object*> items;
    for (int i = 0; i < children.size(); i++) {
        auto it = children[i];
        std::map<int, object*> box = it->getObjects();
        if (box.empty()) continue;
        for (auto item = box.begin(); item != box.end(); item++) {
            items[item->first] = item->second;
        }
    }
    return items;
}

void QuadtreeNode::cleanTreeThroughly(sf::RenderWindow& window) {
    if (timer.getElapsedTime() > cleanTime) {
        timer.restart();
        reset(window);
    }
}

void QuadtreeNode::clean() {
    if (!hasChild) {
        for (auto it = objects.begin(); it != objects.end();) {
            if (it->second == nullptr) {
                it = objects.erase(it);
            }
            else {
                it++;
            }
        }
        return;
    }
    for (int i = 0; i < children.size(); i++) {
        children[i]->clean();
    }
    
    if (getObjects().size() <= MAX_OBJECT_PER_NODE) {
        objects = getObjects();
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
        children.clear();
        children.resize(4, nullptr);
        hasChild = false;
    }
}

int QuadtreeNode::checkCollision() {
    if (this == nullptr) return 0;
    int score = 0;
    if (hasChild) {
        for (int i = 0; i < children.size(); i++) {
            auto it = children[i];
            if (it != nullptr) score += it->checkCollision();
        }
        return score;
    }

    if (!objects.empty()) {
        //collision check
        for (auto i = objects.begin(); i != std::prev(objects.end()); i++) {
            for (auto j = std::next(i); j != objects.end(); j++) {
                if (i->second == nullptr || j->second == nullptr) {
                    parent->clean();
                    return 0;
                }

                int id1 = i->first; int obj1 = object::getObjectType(id1);
                int id2 = j->first; int obj2 = object::getObjectType(id2);

                if (obj1 == 1 && obj2 == 4) {
                    //player & enemy's bullet
                    player* Player = static_cast<player*>(i->second);
                    bullet* Bullet = static_cast<bullet*>(j->second);
                    if (Player == nullptr || Bullet == nullptr) return 0;

                    if (object::isintersect(Player->getSprite(), Bullet->getSprite())) {
                        if(Bullet != nullptr) Player->reducePlayerHp(Bullet->getDamageValue());
                        bullet::deleteObject(id2);

                        if (Player->getPlayerHp() <= 0) {
                            player::deleteObject(id1);
                        }
                        return score;
                    }
                }

                if (obj1 == 2 && obj2 == 3) {
                    //player's bullet & enemy
                    bullet* Bullet = static_cast<bullet*>(i->second);
                    enemy* Enemy = static_cast<enemy*>(j->second);
                    if (Enemy == nullptr || Bullet == nullptr) return 0;

                    if (object::isintersect(Enemy->getSprite(), Bullet->getSprite())) {
                        if (Bullet != nullptr) Enemy->reduceHp(Bullet->getDamageValue());
                        bullet::deleteObject(id1);

                        if (Enemy->getHp() <= 0) {
                            score += Enemy->getMaxHp();
                            enemy::deleteObject(id2);
                        }
                        return score;
                    }
                }

                //if (obj1 == 3 && obj2 == 3) {
                //    enemy* enemy1 = static_cast<enemy*>(i->second);
                //    enemy* enemy2 = static_cast<enemy*>(j->second);

                //    if (object::isintersect(enemy1->getSprite(), enemy2->getSprite())) {
                //        enemy1->setVelocity(enemy1->getVelocity().x * -1, enemy1->getVelocity().y * -1);
                //        enemy2->setVelocity(enemy2->getVelocity().x * -1, enemy2->getVelocity().y * -1);
                //        continue;
                //    }
                //}
            }
        }
    }
    return score;
}

void QuadtreeNode::displayQuadtreeVisual() {
    if (!hasChild) {
        sf::RectangleShape region(sf::Vector2f(width, height));
        region.setPosition(x, y);
        region.setOutlineColor(sf::Color::Red);
        region.setOutlineThickness(0.5);
        region.setFillColor(sf::Color::Transparent);

        window.draw(region);
        return;
    }
    for (int i = 0; i < children.size(); i++) {
        children[i]->displayQuadtreeVisual();
    }
}

void QuadtreeNode::reset(sf::RenderWindow& _window) {
    //for (auto it = player::getPlayerMap()->begin(); it != player::getPlayerMap()->end(); it++) {
    //    root->erase(it->first, static_cast<object*>(it->second));
    //}
    //for (auto it = bullet::getBulletMap(object::Type::playerBullet_obj)->begin(); it != bullet::getBulletMap(object::Type::playerBullet_obj)->end(); it++) {
    //    root->erase(it->first, static_cast<object*>(it->second));
    //}
    //for (auto it = enemy::getEnemyMap()->begin(); it != enemy::getEnemyMap()->end(); it++) {
    //    root->erase(it->first, static_cast<object*>(it->second));
    //}
    //for (auto it = bullet::getBulletMap(object::Type::enemyBullet_obj)->begin(); it != bullet::getBulletMap(object::Type::enemyBullet_obj)->end(); it++) {
    //    root->erase(it->first, static_cast<object*>(it->second));
    //}

    delete root;
    root = nullptr;
    QuadtreeNode* quadtree = new QuadtreeNode(0, 0, _window.getSize().x, _window.getSize().y, _window);

    for (auto it = player::getPlayerMap()->begin(); it != player::getPlayerMap()->end(); it++) {
        quadtree->insert(it->first, static_cast<object*>(it->second));
    }
    for (auto it = bullet::getBulletMap(object::Type::playerBullet_obj)->begin(); it != bullet::getBulletMap(object::Type::playerBullet_obj)->end(); it++) {
        quadtree->insert(it->first, static_cast<object*>(it->second));
    }
    for (auto it = enemy::getEnemyMap()->begin(); it != enemy::getEnemyMap()->end(); it++) {
        quadtree->insert(it->first, static_cast<object*>(it->second));
    }
    for (auto it = bullet::getBulletMap(object::Type::enemyBullet_obj)->begin(); it != bullet::getBulletMap(object::Type::enemyBullet_obj)->end(); it++) {
        quadtree->insert(it->first, static_cast<object*>(it->second));
    }
}