#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "imports.h"
#include <vector>

#include "constants.h"
#include "structs.h"
#include "perlin3d.h"
#include "laser.h"

class GameShip;
class EnemyWave;

/**************** NOISE ********************/
extern perlin3d perlin;				//not actually used either I think...?
extern pixel vals[xmax*ymax];		//not used?
extern double noise[res3];


/**************** MATH  *********************/


/**************** CAMERA ********************/
extern double camx,camy, camvx, camvy;
extern int camPrevSgn;				//currently not used
	
extern point3d face[4];
extern GLfloat light1[4];

extern double zshft;
extern double anm8;					//needs a more descriptive name
extern double d;					//^

/**************** GAME  *********************/
extern GameShip* thePlayerShip;		//the player's ship
extern int numObjects;
extern std::vector<Laser*> lasers, enemyLasers;			//the projectiles in play
extern long curTime, startTime, lastWaveTime;	//for keeping track of the time between frames, total time running, and last time enemies spawned
extern EnemyWave* currentWave;				//the current wave of enemies
extern bool readyForNextWave;				//whether more enemies can spawn

/**************** IO    *********************/
extern bool leftmov,rightmov,upmov,downmov,space;
extern SDL_Event e;

extern SDL_Surface* screen;


#endif // GLOBALS_H_INCLUDED
