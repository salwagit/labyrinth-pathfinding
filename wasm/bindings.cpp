#include <emscripten/bind.h>
#include "../core-cpp/Grid.h"
#include "../core-cpp/Dijkstra.h"
#include "../core-cpp/BFS.h"
#include <vector>

using namespace emscripten;

// Petite structure JS-friendly pour Node
struct JSNode {
    int x, y;
    JSNode() : x(0), y(0) {}
    JSNode(int x_, int y_) : x(x_), y(y_) {}
};

// Wrapper pour transformer std::vector<Node*> en std::vector<JSNode>
std::vector<JSNode> dijkstraPath(int width, int height, std::vector<int> walls, int startX, int startY, int endX, int endY) {

    Grid grid(width, height);
    for (size_t i = 0; i < walls.size(); i += 2) {
        int x = walls[i], y = walls[i + 1];
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid.getNode(x, y)->walkable = false;
        }
    }

    Node* start = grid.getNode(startX, startY);
    Node* end = grid.getNode(endX, endY);

    auto path = Dijkstra::findPath(grid, start, end);
    std::vector<JSNode> jsPath;
    for (auto n : path) jsPath.emplace_back(n->x, n->y);
    return jsPath;
}

std::vector<JSNode> bfsPath(int width, int height, std::vector<int> walls, int startX, int startY, int endX, int endY) {

    Grid grid(width, height);
    for (size_t i = 0; i < walls.size(); i += 2) {
        int x = walls[i], y = walls[i + 1];
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid.getNode(x, y)->walkable = false;
        }
    }

    Node* start = grid.getNode(startX, startY);
    Node* end = grid.getNode(endX, endY);

    auto path = BFS::findPath(grid, start, end);
    std::vector<JSNode> jsPath;
    for (auto n : path) jsPath.emplace_back(n->x, n->y);
    return jsPath;
}

// Binding
EMSCRIPTEN_BINDINGS(my_module) {
    value_object<JSNode>("Node")
        .field("x", &JSNode::x)
        .field("y", &JSNode::y);

    register_vector<JSNode>("NodeVector");

    register_vector<int>("VectorInt");

    function("dijkstraPath", &dijkstraPath);
    function("bfsPath", &bfsPath);
}