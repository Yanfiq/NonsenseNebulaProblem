#include "QuadtreeNode.h"

QuadtreeNode* QuadtreeNode::root = nullptr;

QuadtreeNode::QuadtreeNode(double _x, double _y, double _width, double _height, sf::RenderWindow& _window) : x(_x), y(_y), width(_width), height(_height), window(_window){
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
    entityCount++;
    if (!hasChild || depth == MAX_DEPTH) objects[id] = Object;
    if ((objects.size() <= MAX_OBJECT_PER_NODE && !hasChild) || depth == MAX_DEPTH) return;

    if(!hasChild && depth < MAX_DEPTH) {
        children[0] = new QuadtreeNode(x, y, width / 2, height / 2, window);
        children[1] = new QuadtreeNode(x + width / 2, y, width / 2, height / 2, window);
        children[2] = new QuadtreeNode(x, y + height / 2, width / 2, height / 2, window);
        children[3] = new QuadtreeNode(x + width / 2, y + height / 2, width / 2, height / 2, window);

        for (int i = 0; i < children.size(); i++) {
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
    entityCount--;
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

    root->normalize();
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

std::unordered_map<int, object*> QuadtreeNode::getObjects() {
    if (!hasChild) {
        return objects;
    }

    std::unordered_map<int, object*> items;
    for (int i = 0; i < children.size(); i++) {
        auto it = children[i];
        std::unordered_map<int, object*> box = it->getObjects();
        if (box.empty()) continue;
        for (auto item = box.begin(); item != box.end(); item++) {
            items[item->first] = item->second;
        }
    }
    return items;
}

void QuadtreeNode::checkCollision() {
    if (this == nullptr) return;
    if(hasChild) {
        for (int i = 0; i < children.size(); i++) {
            auto it = children[i];
           if(it != nullptr) it->checkCollision();
        }
        return;
    }

    for (auto i = objects.begin(); i != objects.end(); i++) {
        for (auto j = objects.begin(); j != objects.end(); j++) {
            if (i->first == j->first) continue;

            int id1 = i->first; int obj1 = object::getObjectType(id1);
            int id2 = j->first; int obj2 = object::getObjectType(id2);

            if (obj1 == 1 && obj2 == 4) {
                //player & enemy's bullet
                player* Player = static_cast<player*>(i->second);
                bullet* Bullet = static_cast<bullet*>(j->second);
                //if (Player == nullptr || Bullet == nullptr) return;

                if (object::isintersect(Player->getSprite(), Bullet->getSprite())) {
                    Player->reducePlayerHp(Bullet->getDamageValue());
                    bullet::deleteObject(id2);

                    if (Player->getPlayerHp() <= 0) {
                        player::deleteObject(id1);
                        return;
                    }
                    return;
                }
            }

            if (obj1 == 3 && obj2 == 2) {
                //player's bullet & enemy
                enemy* Enemy = static_cast<enemy*>(i->second);
                bullet* Bullet = static_cast<bullet*>(j->second);
                //if (Enemy == nullptr || Bullet == nullptr) return;

                if (object::isintersect(Enemy->getSprite(), Bullet->getSprite())) {
                    Enemy->reduceHp(Bullet->getDamageValue());
                    bullet::deleteObject(id2);

                    if (Enemy->getHp() <= 0) {
                        enemy::deleteObject(id1);
                        return;
                    }
                    return;
                }
            }

            if (obj1 == 3 && obj2 == 3) {
                enemy* enemy1 = static_cast<enemy*>(i->second);
                enemy* enemy2 = static_cast<enemy*>(j->second);

                if (object::isintersect(enemy1->getSprite(), enemy2->getSprite())) {
                    enemy1->setVelocity(enemy1->getVelocity().x * -1, enemy1->getVelocity().y * -1);
                    enemy2->setVelocity(enemy2->getVelocity().x * -1, enemy2->getVelocity().y * -1);
                    continue;
                }
            }
        }
    }
}

void QuadtreeNode::displayQuadtreeVisual() {
    sf::RectangleShape region(sf::Vector2f(width, height));
    region.setPosition(x, y);
    region.setOutlineColor(sf::Color::Red);
    region.setOutlineThickness(0.5);
    region.setFillColor(sf::Color::Transparent);

    window.draw(region);
    if (!hasChild) return;
    for (int i = 0; i < children.size(); i++) {
        children[i]->displayQuadtreeVisual();
    }
}