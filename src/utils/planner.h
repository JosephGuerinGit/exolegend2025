#ifndef PLANNER_H
#define PLANNER_H

#include "gladiator.h"
#include "chained_list.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <algorithm>

using namespace std;

// Node structure used for pathfinding
struct Nodes {
    MazeSquare* node;
    int g, h, f;
    bool in_closed_list;
    Nodes* parent;

    Nodes(MazeSquare *node, int g, int h, Nodes* parent = nullptr) 
        : node(node), g(g), h(h), f(g + h), parent(parent), in_closed_list(false) {}
};

// CompareNodes for sorting in the priority queue
struct CompareNodes {
    bool operator()(Nodes* a, Nodes* b) {
        return a->f > b->f; // Higher f value comes last (priority queue sorts in descending order)
    }
};

// Heuristic function (Manhattan distance)
int heuristic(int x1, int y1, int x2, int y2);

// Pathfinding function to find a path between start and goal
LinkedList defineNewPath(MazeSquare* start, MazeSquare* goal);



// Function to calculate the center position of a MazeSquare
Position* getNewPosition(MazeSquare* mazesquare, float squareSize);

#endif  // PLANNER_H
