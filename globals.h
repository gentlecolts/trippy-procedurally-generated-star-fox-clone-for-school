#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "imports.h"
#include <vector>

#include "constants.h"
#include "structs.h"
#include "perlin3d.h"

class Laser;
class GameShip;
class EnemyWave;


/**************** CAMERA ********************/
extern double camx,camy, camvx, camvy;	//camera position and velocity
extern int camPrevSgn;				//currently not used

extern point3d face[4];
extern GLfloat light1[4];			//the position of the second light

extern double zshft;				//the distance the player has traveled, or the amount to offset the z coordinate by when doing noise lookups
extern double anm8;					//needs a more descriptive name
extern double d;					//^
extern uint16_t xmax, ymax;			//the size of the window
extern double cameraHeight;			//the height of the camera's fov


/**************** NOISE ********************/
extern perlin3d perlin;				//the perlin noise generator
extern double noise[res3];			//the precomputed noise values


/**************** MATH  *********************/

/**************** GAME  *********************/
extern GameShip* thePlayerShip, *lasers, *enemyLasers;		//the player's ship
//extern std::vector<Laser*> lasers, enemyLasers;			//the projectiles in play
extern long curTime, startTime, lastWaveTime;				//for keeping track of the time between frames, total time running, and last time enemies spawned
extern EnemyWave* currentWave;								//the current wave of enemies
extern bool readyForNextWave;								//whether more enemies can spawn
extern long waveTime;										//the time until the next wave spawns
extern bool didGameSetup, needToUnload;						//whether the game has been initialized, whether the player has quit/died
extern int playerScore;										//the player's score
extern double noiseScale;									//the scale factor on the perlin noise; as this decreases the noise becomes harder to dodge

/**************** IO    *********************/
extern bool leftmov,rightmov,upmov,downmov,space, fire, fireRockets;	//whether each key used for input is currently pressed
extern SDL_Event e;											//the event SDL uses to pass in information on input
extern bool inGame;											//whether the player has starte the game

extern SDL_Surface* screen;									//the window to draw to


#endif // GLOBALS_H_INCLUDED
