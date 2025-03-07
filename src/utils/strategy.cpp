#include "utils/planner.h"
#include "gladiator.h"

int SIZE = 5;

void update_strategy(Gladiator *gladiator) {
    // Retrieve the nearest square (const pointer)
    const MazeSquare *nearestSquare = gladiator->maze->getNearestSquare();
    const MazeSquare *eastSquare = gladiator->maze->getNearestSquare()->eastSquare;
    // const MazeSquare *eastSquare = *nearestSquare->eastSquare;

    // Create a modifiable copy
    MazeSquare mySquare = *nearestSquare;
    MazeSquare myEastSquare = *eastSquare;

    // Pass pointers to defineNewPath
    // defineNewPath(&mySquare, &myEastSquare);
}

MazeSquare getNearestBomb(MazeSquare *current_square)
{
    float min_dist = 1000;
    MazeSquare *nearest_bomb = nullptr;
    const int searchRadius = 5;  // On ne regarde que dans un carré de 5 cases autour de la position actuelle

    // Définir les bornes de la recherche en fonction des indices du carré courant
    uint8_t i_min = (current_square->i >= searchRadius ? current_square->i - searchRadius : 0);
    uint8_t i_max = (current_square->i + searchRadius < SIZE ? current_square->i + searchRadius : SIZE - 1);
    uint8_t j_min = (current_square->j >= searchRadius ? current_square->j - searchRadius : 0);
    uint8_t j_max = (current_square->j + searchRadius < SIZE ? current_square->j + searchRadius : SIZE - 1);

    for (uint8_t i = i_min; i <= i_max; i++)
    {
        for (uint8_t j = j_min; j <= j_max; j++)
        {
            MazeSquare *square = game->gladiator->maze->getSquare(i, j);
            if (square->coin.value)  // La case contient une bombe (ou coin, selon ta logique)
            {
                float dist = getDistance(current_square, square);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    nearest_bomb = square;
                }
            }
        }
    }

    return nearest_bomb;
}