#include "gladiator.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <algorithm>

using namespace std;

Gladiator *gladiator;


struct Node {   //utiliser ici le struct MazeSquare (et rajouter dans mazesquare )
    int x, y;
    int g, h, f;
    Node* parent;
    Node(int x, int y, int g, int h, Node* parent = nullptr) 
         : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {}
};


struct CompareNodes {     //compare le f_score de a et b (et retourne true si a>b)
    bool operator()(const Node* a, const Node* b) {
        return a->f > b->f;
    }
 };

int heuristic(int x1, int y1, int x2, int y2) {   //distance de Manhattan
    return abs(x1 - x2) + abs(y1 - y2);
}




vector<pair<int, int>> findPath(const MazeSquare* start ,const MazeSquare*goal) {
    int rows = 12, cols = 12;
    priority_queue<Node*, vector<Node*>, CompareNodes> openList;    //openlist
    vector<vector<bool>> closedList(rows, vector<bool>(cols, false));  //closed list
    vector<vector<Node*>> allNodes(rows, vector<Node*>(cols, nullptr));  //vector to avoid having multiple nodes created for 1 cell
    
    Node* startNode = new Node(start->j-'0', start->i-'0', 0, heuristic(start->j, start->i, goal->j, goal->i));
    openList.push(startNode);
    allNodes[start->j-'0'][start->i-'0'] = startNode;
    
    
    
    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();
        unsigned char i = current->y+'0', j = current->x+'0';
        const MazeSquare *Current = gladiator->maze->getSquare(i,j);
        
        //check if new pointer

        if (current->x == goal->j-'0' && current->y == goal->i-'0') {  //if we reached the goal
            vector<pair<int, int>> path;     //initialization of the path vector
            while (current) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            reverse(path.begin(), path.end());    //this will need to be taken care of
            return path;
        }
        
//         closedList[current->x][current->y] = true;
        
        MazeSquare* neighbors[] = {
            Current->northSquare,
            Current->westSquare,
            Current->southSquare,
            Current->eastSquare
        };
        
        for (int i = 0; i < 4; ++i) {            //neighbor est un MazeSquare and Neighbor est une Node
            MazeSquare* neighbor=neighbors[i];
            
            int x= neighbor->j-'0';
            int y= neighbor->i-'0';

            if (x >= 0 && x < rows && y >= 0 && y < cols && neighbor!=nullptr && !closedList[x][y]) {
                int newG = current->g + 1;
                if (!allNodes[x][y] || newG < allNodes[x][y]->g) {
                    Node* Neighbor = new Node(x, y, newG, heuristic(x, y, goal->j, goal->i), current);
                    openList.push(Neighbor);       //on donne un MazeSquare alors qu'on veut 
                    allNodes[x][y] = Neighbor;
                }
            }
        }
    }
    return {};
}


void PrintPath(vector<pair<int, int>> path) {
    for (const auto& p : path) {
        cout << "(" << (int)p.first << ", " << (int)p.second << ")\n";
    }
}



int main() {
    
    MazeSquare* Start_Node;
    MazeSquare* Goal_Node;

    Start_Node->i=0+'0';Start_Node->j=0+'0';
    Start_Node->j=7+'0';Start_Node->j=7+'0';



    vector<pair<int, int>> path = findPath(Start_Node, Goal_Node);
    
    if (!path.empty()) {
         cout << "Path found:\n";
    }
    else {
        cout << "No path found." << endl;
    }
    delete Start_Node;
    delete Goal_Node;
    return 0;
}


