#pragma once
#include <vector>

struct Node {
    int x, y;                    // position dans la grille
    bool walkable = true;         // si le noeud est franchissable
    int distance = -1;            // pour Dijkstra / BFS
    Node* parent = nullptr;       // pour reconstruire le chemin
    Node(int x_, int y_) : x(x_), y(y_) {}
};