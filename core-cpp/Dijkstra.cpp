#include "Dijkstra.h"
#include <queue>
#include <algorithm>
#include <limits>

std::vector<Node*> Dijkstra::findPath(Grid& grid, Node* start, Node* end) {
    auto cmp = [](Node* a, Node* b) { return a->distance > b->distance; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);
    for (auto& row : grid.nodes)
        for (auto& n : row) {
            n.distance = std::numeric_limits<int>::max();
            n.parent = nullptr;
        }

    start->distance = 0;
    pq.push(start);

    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        if (current == end) break;

        for (Node* neighbor : grid.getNeighbors(current)) {
            int newDist = current->distance + 1; // poids uniforme de 1
            if (newDist < neighbor->distance) {
                neighbor->distance = newDist;
                neighbor->parent = current;
                pq.push(neighbor);
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