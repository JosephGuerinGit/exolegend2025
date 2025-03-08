#include "Combat.h"

// On utilise la déclaration `extern` de Combat.h
void setup_combat()
{
    // Pas besoin de recréer un nouvel objet Gladiator ici, il existe déjà dans main.cpp
    gladiator->game->onReset(&reset_combat);
    gladiator->game->enableFreeMode(RemoteMode::OFF);
}


void reset_combat()
{
    // fonction de reset:
    // initialisation de toutes vos variables avant le début d'un match
    gladiator->log("Call of reset function"); // GFA 4.5.1
}


void dash(float speed, int duration) //speed : vitesse du dash; duration : durée du dash
{
    gladiator->control->setWheelSpeed(WheelAxis::LEFT,speed);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, speed);

    delay(duration); //maintenir le dash pour une durée définie

    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT,0);
}

void swingRight(float speed, int duration)
{
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, speed);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, -speed);

    delay(duration);

    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0);    
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0);
}

void swingLeft(float speed, int duration)
{
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, -speed);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, speed);

    delay(duration);

    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0);    
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0);
}

void dashAndBack(float dashSpeed, int dashDuration, float backSpeed, int backDuration)
{
    dash(dashSpeed, dashDuration);
    dash(-backSpeed, backDuration);
}


void loop_combat()
{
    if (gladiator->game->isStarted())
    {
        // Exécuter un dash à pleine vitesse pendant 500ms
        dash(1.0, 500);
    }
    delay(300);
}

