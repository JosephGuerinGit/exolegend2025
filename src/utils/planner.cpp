#include "gladiator.h"

#include "planner.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <algorithm>

using namespace std;

int heuristic(int x1, int y1, int x2, int y2) {   // Manhattan distance
    return abs(x1 - x2) + abs(y1 - y2);
}

// Replace LinkedList with std::stack
stack<MazeSquare*> defineNewPath(MazeSquare* start ,MazeSquare* goal) {
    int rows = 12, cols = 12;
    priority_queue<Nodes*, vector<Nodes*>, CompareNodes> openList;    // Open list
    Nodes* allNodes[rows][cols] = {nullptr};  // All elements initially are not created
    Nodes* startNode = new Nodes(start, 0, heuristic(start->j, start->i, goal->j, goal->i));
    openList.push(startNode);
    allNodes[start->j - '0'][start->i - '0'] = startNode;
    
    // Use stack to store the path
    stack<MazeSquare*> pathStack;
    
    while (!openList.empty()) {
        Nodes* current = openList.top();
        openList.pop();
        MazeSquare *Current = current->node;
        
        // Check if we reached the goal
        if (Current->j == goal->j && Current->i == goal->i) {  
            // Push the nodes to the stack to track the path
            while (Current) {
                pathStack.push(Current);
                Current = current->parent->node;
            }
            return pathStack;  // Return the stack containing the path
        }
        
        current->in_closed_list = true;
        
        MazeSquare* neighbors[] = {
            Current->northSquare,
            Current->westSquare,
            Current->southSquare,
            Current->eastSquare
        };
        
        for (int i = 0; i < 4; ++i) {  // Check each neighboring square
            MazeSquare* neighbor = neighbors[i];
            
            int x = neighbor->j - '0';
            int y = neighbor->i - '0';

            if (x >= 0 && x < rows && y >= 0 && y < cols && neighbor != nullptr && !current->in_closed_list) {
                int newG = current->g + 1;
                if (!allNodes[x][y] || newG < allNodes[x][y]->g) {
                    Nodes* Neighbor = new Nodes(neighbor, newG, heuristic(x, y, goal->j, goal->i), current);
                    openList.push(Neighbor);  // Push to open list
                    allNodes[x][y] = Neighbor;
                }
            }
        }
    }
    
    return pathStack;  // Return an empty stack if no path found
}

// Function to get a new MazeSquare (Dummy example)
MazeSquare* getNewSquare() {
    MazeSquare* Node_try = new MazeSquare();
    Node_try->i = 0 + '0';
    Node_try->j = 0 + '0';
    return Node_try;
}

// Function to calculate the position based on the square size
Position getNewPosition(float squareSize) {
    MazeSquare* mazesquare = getNewSquare();
    Position centerCoor;
    centerCoor.x = (mazesquare->i + 0.5) * squareSize;
    centerCoor.y = (mazesquare->j + 0.5) * squareSize;
    return centerCoor;
}

/*
int main() {
    MazeSquare* Start_Node;
    MazeSquare* Goal_Node;

    Start_Node->i = 0 + '0';
    Start_Node->j = 0 + '0';
    Goal_Node->i = 7 + '0';
    Goal_Node->j = 7 + '0';

    stack<MazeSquare*> path = defineNewPath(Start_Node, Goal_Node);

    if (!path.empty()) {
        cout << "Path found:\n";
        // Print the path by popping from the stack
        while (!path.empty()) {
            MazeSquare* current = path.top();
            cout << "MazeSquare (" << current->i << ", " << current->j << ")\n";
            path.pop();
        }
    } else {
        cout << "No path found." << endl;
    }
    
    delete Start_Node;
    delete Goal_Node;
    return 0;
}
*/
