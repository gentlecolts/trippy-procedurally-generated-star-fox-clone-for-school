#import "globals.h"

class GameObject;

/**************** NOISE ********************/
perlin3d perlin(theseed);
pixel vals[xmax*ymax];
double noise[res3];


/**************** MATH  *********************/


/**************** CAMERA ********************/
double camx=0,camy=0;
double velX=0, velY=0;

point3d face[4];
GLfloat light1[4];

double zshft;
double anm8=0;
double d=d1;

/**************** GAME  *********************/
GameObject* gameObjects[numGameObjects];
std::vector<Laser> lasers;

/**************** IO    *********************/
bool leftmov,rightmov,upmov,downmov,space;
SDL_Event e;

SDL_Surface* screen=NULL;
