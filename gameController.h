#ifndef GAMECONTROLLER_H_INCLUDED
#define GAMECONTROLLER_H_INCLUDED

#include "laser.h"

void setupGame();
void updateObjects();
void renderObjects();
void addLaser(Laser las);
void unloadGame();

#endif // GAMECONTROLLER_H_INCLUDED
