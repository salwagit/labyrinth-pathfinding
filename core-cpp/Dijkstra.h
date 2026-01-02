#pragma once
#include "Grid.h"
#include <vector>

class Dijkstra {
public:
    static std::vector<Node*> findPath(Grid& grid, Node* start, Node* end);
};