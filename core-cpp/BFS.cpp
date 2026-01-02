#include "BFS.h"
#include <queue>
#include <algorithm>

std::vector<Node*> BFS::findPath(Grid& grid, Node* start, Node* end) {
    std::queue<Node*> q;
    for (auto& row : grid.nodes)
        for (auto& n : row) {
            n.distance = -1;
            n.parent = nullptr;
        }

    start->distance = 0;
    q.push(start);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current == end) break;

        for (Node* neighbor : grid.getNeighbors(current)) {
            if (neighbor->distance == -1) { // non visité
                neighbor->distance = current->distance + 1;
                neighbor->parent = current;
                q.push(neighbor);
            }
        }
    }

    // reconstruction du chemin
    std::vector<Node*> path;
    Node* curr = end;
    while (curr) {
        path.push_back(curr);
        curr = curr->parent;
    }
    std::reverse(path.begin(), path.end());
    if (!path.empty() && path.front() == start) return path;
    return {}; // pas de chemin trouvé
}