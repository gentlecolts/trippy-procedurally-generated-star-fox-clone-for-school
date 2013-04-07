#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "imports.h"
#include <vector>

#include "constants.h"
#include "structs.h"
#include "perlin3d.h"
#include "laser.h"

class GameObject;

/**************** NOISE ********************/
extern perlin3d perlin;
extern pixel vals[xmax*ymax];
extern double noise[res3];


/**************** MATH  *********************/


/**************** CAMERA ********************/
extern double camx,camy, velX, velY;

extern point3d face[4];
extern GLfloat light1[4];

extern double zshft;
extern double anm8;
extern double d;

/**************** GAME  *********************/
extern GameObject* gameObjects[numGameObjects];
extern std::vector<Laser> lasers;

/**************** IO    *********************/
extern bool leftmov,rightmov,upmov,downmov,space;
extern SDL_Event e;

extern SDL_Surface* screen;


#endif // GLOBALS_H_INCLUDED
