#ifndef GAMECONTROLLER_H_INCLUDED
#define GAMECONTROLLER_H_INCLUDED

#include "laser.h"

void setupGame();
void updateObjects();
void renderObjects();
void addLaser(Laser* las, bool player);
void unloadGame();
void nextWave();

#endif // GAMECONTROLLER_H_INCLUDED
