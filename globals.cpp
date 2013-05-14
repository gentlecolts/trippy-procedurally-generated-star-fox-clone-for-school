//#import "globals.h"
#include "globals.h"
#include <ctime>

class GameShip;
class EnemyWave;


/**************** CAMERA ********************/
double camx=0,camy=0;
double camvx=0, camvy=0;
int camPrevSgn=0;

point3d face[4];
GLfloat light1[4];

double zshft;
double anm8=0;
double d=d1;
uint16_t xmax=1280, ymax=720;
double cameraHeight=cameraHeight=(double)xmax/(double)ymax*cameraWidth;


/**************** NOISE ********************/
perlin3d perlin(theseed);
pixel vals[xmax*ymax];
double noise[res3];


/**************** MATH  *********************/

/**************** GAME  *********************/
GameShip* thePlayerShip, *lasers, *enemyLasers;
int numObjects=0;
//std::vector<Laser*> lasers, enemyLasers;
long curTime=0,startTime=clock(),lastWaveTime=clock();
EnemyWave* currentWave=NULL;
bool readyForNextWave=true;

/**************** IO    *********************/
bool leftmov,rightmov,upmov,downmov,space,fire;
SDL_Event e;

SDL_Surface* screen=NULL;
