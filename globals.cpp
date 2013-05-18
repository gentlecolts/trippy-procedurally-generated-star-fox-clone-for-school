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
double noise[res3];


/**************** MATH  *********************/

/**************** GAME  *********************/
GameShip* thePlayerShip, *lasers, *enemyLasers;
int numObjects=0;
//std::vector<Laser*> lasers, enemyLasers;
long curTime=0,startTime=clock(),lastWaveTime=clock();
EnemyWave* currentWave=NULL;
bool readyForNextWave=true;
long waveTime=10000;
bool didGameSetup=false, needToUnload=false;
int playerScore=0;
double noiseScale=2;

/**************** IO    *********************/
bool leftmov,rightmov,upmov,downmov,space,fire,fireRockets;
SDL_Event e;
bool inGame=false;

SDL_Surface* screen=NULL;
