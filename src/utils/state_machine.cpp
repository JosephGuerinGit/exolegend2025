#include "utils/strategy.h"
#include "utils/planner.h"
#include "utils/mobile_base.h"
#include "gladiator.h"

// Gladiator *gladiator;
bool is_moving = false;
bool has_strategy = false;

void reset_state_machine(){
    // reset state machine
    is_moving = false;
}

void run(Gladiator *gladiator) {
    
    while (true) {                              // Demander le prochain point à atteindre
        update_strategy(gladiator);             // ICI problème, il faut pas actualiser toute la stratégie à chaque fois
        Position goal = getNewPosition();

        while (is_moving) {                     // Redemander le prochain point à atteindre
            Position myPosition = gladiator->robot->getData().position;
            is_moving = !goTo(goal, myPosition, gladiator);
        }
    }
}