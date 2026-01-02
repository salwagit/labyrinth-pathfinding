#include "Grid.h"

Grid::Grid(int w, int h) : width(w), height(h) {
    nodes.resize(height, std::vector<Node>(width, Node(0,0)));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            nodes[y][x] = Node(x, y);
        }
    }
}

Node* Grid::getNode(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
    return &nodes[y][x];
}

std::vector<Node*> Grid::getNeighbors(Node* node) {
    std::vector<Node*> neighbors;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++) {
        Node* n = getNode(node->x + dx[i], node->y + dy[i]);
        if (n && n->walkable) neighbors.push_back(n);
    }
    return neighbors;
}