#ifndef COMBAT_H
#define COMBAT_H

#include "gladiator.h"

// Déclaration externe pour éviter la redéfinition multiple
extern Gladiator *gladiator;

// Fonctions de combat
void setup_combat();
void reset_combat();
void dash(float speed, int duration);
void swingRight(float speed, int duration);
void swingLeft(float speed, int duration);
void dashAndBack(float dashSpeed, int dashDuration, float backSpeed, int backDuration);

#endif // COMBAT_H
