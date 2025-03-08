#ifndef PLANNER_H
#define PLANNER_H

#include "gladiator.h"
#include <queue>
#include <stack>

// Node structure for the A* search
struct Nodes {
    MazeSquare* node;  // Pointer to the MazeSquare
    int g;  // Cost from the start node
    int h;  // Heuristic cost to the goal
    bool in_closed_list;  // Flag to mark if the node is in the closed list
    Nodes* parent;  // Pointer to the parent node

    // Constructor for the node
    Nodes(MazeSquare* n, int gCost, int hCost, Nodes* p = nullptr)
        : node(n), g(gCost), h(hCost), in_closed_list(false), parent(p) {}
};

// Comparator for the priority queue
struct CompareNodes {
    bool operator()(Nodes* a, Nodes* b) {
        return (a->g + a->h) > (b->g + b->h);  // Min-heap based on f = g + h
    }
};

// Function to calculate the heuristic (Manhattan distance)
int heuristic(int x1, int y1, int x2, int y2);

// A* search function that returns the path as a stack
void defineNewPath(MazeSquare* start, MazeSquare* goal);

// Function to get a new MazeSquare (dummy example)
MazeSquare* getNewSquare();

// Function to calculate the position based on the square size
Position getNewPosition(float squareSize);

#endif  // PLANNER_H
