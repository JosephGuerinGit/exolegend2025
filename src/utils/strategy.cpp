#include "utils/planner.h"
#include "gladiator.h"

// define a list of x,y positions that I can initialize
int x_positions[] = {1, 2, 3, 4, 5};
int y_positions[] = {6, 7, 8, 9, 10};


void update_strategy(Gladiator *gladiator) {
    // Retrieve the nearest square (const pointer)
    const MazeSquare *nearestSquare = gladiator->maze->getNearestSquare();
    const MazeSquare *eastSquare = gladiator->maze->getNearestSquare()->eastSquare;
    // const MazeSquare *eastSquare = *nearestSquare->eastSquare;

    // Create a modifiable copy
    MazeSquare mySquare = *nearestSquare;
    MazeSquare myEastSquare = *eastSquare;

    // Pass pointers to defineNewPath
    defineNewPath(&mySquare, &myEastSquare);
}