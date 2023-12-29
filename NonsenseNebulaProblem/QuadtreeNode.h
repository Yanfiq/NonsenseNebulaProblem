#pragma once
#include <map>
#include <vector>
#include <set>
#include "objects.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

#define MAX_OBJECT_PER_NODE 2
#define MAX_DEPTH 5

class QuadtreeNode {
public:
    double x, y, width, height;
    int depth;
    bool hasChild = false;
    static QuadtreeNode* root;
    int entityCount = 0;
    std::map<int, object*> objects;
    std::vector<QuadtreeNode*> children;
    sf::RenderWindow& window;

    QuadtreeNode(double _x, double _y, double _width, double _height, sf::RenderWindow& _window);
    ~QuadtreeNode();
    void insert(int id, object* Object);
    void normalize();
    void erase(int id, object* Object);
    int checkCollision();
    std::map<int, object*> getObjects();
    void displayQuadtreeVisual();
    static void reset(sf::RenderWindow& _window);
};