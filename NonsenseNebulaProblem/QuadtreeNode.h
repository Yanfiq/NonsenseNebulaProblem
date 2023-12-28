#pragma once
#include <unordered_map>
#include <vector>
#include <set>
#include "objects.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

#define MAX_OBJECT_PER_NODE 3

class QuadtreeNode {
public:
    double x, y, width, height;
    bool hasChild = false;
    static QuadtreeNode* root;
    int entityCount = 0;
    std::unordered_map<int, object*> objects;
    std::vector<QuadtreeNode*> children;
    sf::RenderWindow& window;

    QuadtreeNode(double _x, double _y, double _width, double _height, sf::RenderWindow& _window);
    void insert(int id, object* Object);
    void erase(int id, object* Object);
    void checkCollision();
    std::unordered_map<int, object*> getObjects();
    void displayQuadtreeVisual();
};