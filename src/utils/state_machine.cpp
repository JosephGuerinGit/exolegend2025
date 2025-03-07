#include "utils/strategy.h"
#include "utils/planner.h"
#include "utils/mobile_base.h"
#include "gladiator.h"

// Gladiator *gladiator;
bool is_moving = false;

void reset_state_machine(){
    // reset state machine
    is_moving = false;
}

bool isMoving() {
    return true;
}

void run(Gladiator *gladiator) {
    
    Position goal{2.1, 1.8, 0};
    
    update_strategy(gladiator);
    
    while (true) {
        Position myPosition = gladiator->robot->getData().position;
        goTo(goal, myPosition, gladiator);
    }
}