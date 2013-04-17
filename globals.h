#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "imports.h"
#include <vector>

#include "constants.h"
#include "structs.h"
#include "perlin3d.h"
#include "laser.h"

class GameObject;
class EnemyWave;

/**************** NOISE ********************/
extern perlin3d perlin;
extern pixel vals[xmax*ymax];
extern double noise[res3];


/**************** MATH  *********************/


/**************** CAMERA ********************/
extern double camx,camy, camvx, camvy;
extern int camPrevSgn;

extern point3d face[4];
extern GLfloat light1[4];

extern double zshft;
extern double anm8;
extern double d;

/**************** GAME  *********************/
extern vector<GameObject*> gameObjects;
#define thePlayerShip gameObjects.at(0)		//slightly hacky, oh well
extern std::vector<Laser*> lasers;
extern long curTime, startTime, prevTime, lastWaveTime;
extern EnemyWave* currentWave;
extern bool readyForNextWave;

/**************** IO    *********************/
extern bool leftmov,rightmov,upmov,downmov,space;
extern SDL_Event e;

extern SDL_Surface* screen;


#endif // GLOBALS_H_INCLUDED
