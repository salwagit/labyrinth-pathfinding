#pragma once
#include "Grid.h"
#include <vector>

class BFS {
public:
    static std::vector<Node*> findPath(Grid& grid, Node* start, Node* end);
};