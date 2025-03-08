#include "Combat.h"
#include "gladiator.h"
#include <vector>
#include <cmath>
#include "../Asservissement/Asservissement.h"

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

std::vector<Position> locateOpponents(Gladiator* gladiator) {
    std::vector<Position> opponentPositions;

    // Récupérer la liste des IDs des robots en jeu
    RobotList playingRobots = gladiator->game->getPlayingRobotsId();

    // Parcourir chaque robot et récupérer ses données
    for (int i = 0; i < 4; ++i) { // 4 est le nombre max de robots dans l'arène
        if (playingRobots.ids[i] != 0 && playingRobots.ids[i] != gladiator->robot->getData().id) {
            // Récupérer les données du robot adverse
            RobotData opponentData = gladiator->game->getOtherRobotData(playingRobots.ids[i]);

            // Ajouter sa position à la liste si le robot est toujours en jeu
            if (opponentData.lifes > 0) {
                opponentPositions.push_back(opponentData.position);
            }
        }
    }

    return opponentPositions;
}


//Dans la fonction suivante, engagingThreshold est la distance à partir lequel le robot engage le combat avec un robot adverse
std::pair<bool, std::vector<Position>> engageCombat(Gladiator* gladiator, double engagingThreshold) { 
    std::vector<Position> enemiesInRange;
    
    // Récupérer la position actuelle du robot
    Position myPosition = gladiator->robot->getData().position;

    // Obtenir la liste des adversaires
    std::vector<Position> opponents = locateOpponents(gladiator);

    // Vérifier quels adversaires sont dans la portée du combat
    for (const auto& opponentPos : opponents) {
        double distance = std::sqrt(std::pow(opponentPos.x - myPosition.x, 2) +
                                    std::pow(opponentPos.y - myPosition.y, 2));

        if (distance <= engagingThreshold) {
            enemiesInRange.push_back(opponentPos);
        }
    }

    // Retourne vrai si au moins un adversaire est à portée, sinon faux
    return { !enemiesInRange.empty(), enemiesInRange };
}


void handleCombat(Gladiator* gladiator, Asservissement* asserv, double engagingThreshold, float attackSpeed, int attackDuration) {
    // Récupérer les adversaires proches
    auto [isEnemyNear, enemyPositions] = engageCombat(gladiator, engagingThreshold);

    if (!isEnemyNear) {
        gladiator->log("No enemy in range.");
        return;
    }

    // Choisir le premier ennemi détecté
    Position targetEnemy = enemyPositions[0];

    // Envoyer la cible à l'asservissement pour s'orienter vers l'ennemi
    asserv->setTargetPos(targetEnemy);

    gladiator->log("Aligning with enemy...");

    // Attendre que l'asservissement ait fini de s'aligner
    while (!asserv->available()) {
        delay(10);
    }

    gladiator->log("Aligned with enemy. Engaging!");

    // Dash vers l’ennemi
    dash(attackSpeed, attackDuration);
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

