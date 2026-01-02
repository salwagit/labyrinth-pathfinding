#pragma once
#include "Node.h"
#include <vector>

class Grid {
public:
    int width, height;
    std::vector<std::vector<Node>> nodes;

    Grid(int w, int h);
    Node* getNode(int x, int y);
    std::vector<Node*> getNeighbors(Node* node);
};