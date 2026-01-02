#include "Grid.h"
#include "Dijkstra.h"
#include "BFS.h"
#include <iostream>

int main() {
    Grid grid(5, 5);

    // Bloquer quelques cases
    grid.getNode(1,1)->walkable = false;
    grid.getNode(1,2)->walkable = false;
    grid.getNode(1,3)->walkable = false;

    Node* start = grid.getNode(0,0);
    Node* end = grid.getNode(4,4);

    auto path = Dijkstra::findPath(grid, start, end);
    std::cout << "Dijkstra path:\n";
    for (auto n : path) std::cout << "(" << n->x << "," << n->y << ") ";
    std::cout << "\n";

    auto path2 = BFS::findPath(grid, start, end);
    std::cout << "BFS path:\n";
    for (auto n : path2) std::cout << "(" << n->x << "," << n->y << ") ";
    std::cout << "\n";

    return 0;
}