//#import "globals.h"
#include "globals.h"
#include <ctime>

class GameObject;
class EnemyWave;

/**************** NOISE ********************/
perlin3d perlin(theseed);
pixel vals[xmax*ymax];
double noise[res3];


/**************** MATH  *********************/


/**************** CAMERA ********************/
double camx=0,camy=0;
double camvx=0, camvy=0;
int camPrevSgn=0;

point3d face[4];
GLfloat light1[4];

double zshft;
double anm8=0;
double d=d1;

/**************** GAME  *********************/
std::vector<GameObject*> gameObjects;
std::vector<Laser*> lasers;
long curTime=0,startTime=clock(), prevTime=0,lastWaveTime=clock();
EnemyWave* currentWave=NULL;
bool readyForNextWave=true;

/**************** IO    *********************/
bool leftmov,rightmov,upmov,downmov,space;
SDL_Event e;

SDL_Surface* screen=NULL;
