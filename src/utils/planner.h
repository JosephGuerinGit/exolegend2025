#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "gladiator.h"
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node {
    int x, y;
    int g, h, f;
    Node* parent;
    Node(int x, int y, int g, int h, Node* parent = nullptr) 
         : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {}
};

struct CompareNodes {
    bool operator()(const Node* a, const Node* b) {
        return a->f > b->f;
    }
};

class Pathfinding {
public:
    static int heuristic(int x1, int y1, int x2, int y2);  // Manhattan distance
    static vector<pair<int, int>> findPath(const MazeSquare* start, const MazeSquare* goal);
    static void PrintPath(const vector<pair<int, int>>& path);
};



Position getNewPosition();

void defineNewPath(MazeSquare *start_node, MazeSquare *goal_node);

#endif // PATHFINDING_H