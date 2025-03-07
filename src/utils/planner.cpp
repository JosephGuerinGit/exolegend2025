#include "gladiator.h"
#include "chained_list.h"
#include "planner.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <algorithm>

using namespace std;

int heuristic(int x1, int y1, int x2, int y2) {   //distance de Manhattan
    return abs(x1 - x2) + abs(y1 - y2);
}

LinkedList defineNewPath(MazeSquare* start ,MazeSquare*goal) {
    int rows = 12, cols = 12;
    priority_queue<Nodes*, vector<Nodes*>, CompareNodes> openList;    //openlist
    Nodes* allNodes[rows][cols] = {nullptr};  // All elements initially are not created
    
    Nodes* startNode = new Nodes(start, 0, heuristic(start->j, start->i, goal->j, goal->i));
    openList.push(startNode);
    allNodes[start->j-'0'][start->i-'0'] = startNode;
    
    
    while (!openList.empty()) {
        Nodes* current = openList.top();
        openList.pop();
        MazeSquare *Current = current->node;
        
        //check if new pointer

        if (Current->j == goal->j && Current->i == goal->i) {  //if we reached the goal
            LinkedList path;            
            while (Current) {
                path.push_back(Current);
                Current = current->parent->node;
            }
            path.reverseList(); // to take care of
            return path;
        }
        
        current->in_closed_list = true;
        
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

            if (x >= 0 && x < rows && y >= 0 && y < cols && neighbor!=nullptr && !current->in_closed_list) {
                int newG = current->g + 1;
                if (!allNodes[x][y] || newG < allNodes[x][y]->g) {
                    Nodes* Neighbor = new Nodes(neighbor, newG, heuristic(x, y, goal->j, goal->i), current);
                    openList.push(Neighbor);       //on donne un MazeSquare alors qu'on veut 
                    allNodes[x][y] = Neighbor;  
                }
            }
        }
    }
    return {};
}


MazeSquare* getNewSquare(){
    MazeSquare* Node_try;
    

    Node_try->i=0+'0';Node_try->j=0+'0';
    return(Node_try);
}


Position* getNewPosition(float squareSize){
    MazeSquare* mazesquare = getNewSquare();
    // calculons les coordonnées du centre de cette case
    Position centerCoor;
    // pour calculer les coordonnées x et y il faut récupérer les index i et j de la case
    centerCoor.x = (mazesquare->i + 0.5) * squareSize;
    centerCoor.y = (mazesquare->j + 0.5) * squareSize;
}

/*
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
        cout << "No path found."" << endl;
    }
    delete Start_Node;
    delete Goal_Node;
    return 0;
}*/
