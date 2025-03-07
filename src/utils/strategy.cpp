#include "utils/planner.h"
#include "gladiator.h"

// define a list of x,y positions that I can initialize
int x_positions[] = {1, 2, 3, 4, 5};
int y_positions[] = {6, 7, 8, 9, 10};


void update_planner() {
    // Update the planner using the state of the game : position of the robot etc.
    // This function defines the goal the planner should target.
    Position goal = {x_positions[0], y_positions[0]};
    // goal = 
}