#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <cmath>
#include "math.h"

/**************** NOISE ********************/
#define theseed 0xdeadbeeb

#define grid 8
const double grid2=grid/2;

#define divs 4
const double delta=1.0/divs;
const double delt2=delta/2;

#define shftstep (1.0/10)

#define precompdivs 8//should be at least divs times 2
const double precompdelta=1.0/precompdivs;

/**important values for drawmethod
 * 4 -> trace
 * 6 -> best non-gl squares (may be broken)
 * 9 -> opengl
 * 11-> opencl trace, needs to be finished
 */
#define drawmethod 9

#if drawmethod>4
#define doGL 1
#else
#define doGL 0
#endif

#define shadenorm 0

#define outline 1

#define doSDL 1

#define tolerance 0.4


/**************** MATH  *********************/

const double rt2=1/sqrt(2);
#define pi 3.141592653589793238462643383279502884197169l

/**************** CAMERA ********************/
#define objScale 0.3			//the scale factor applied to models for in-game objects

#define xmax 1280				//the resolution of the game window
#define ymax 720

#define viewangle 60
const double sinviewangle=sin(radians(viewangle));
#define playerOffset 1			//the z position of the plane the player moves in (actually the negative of that because -z is forward)
#define cameraOffset 1			//the z position of the camera
#define noiseScale 10           //the scale factor of the terrain, or the half size of the game area in x and y


const double cameraWidth=sinviewangle*playerOffset*3;
const double cameraHeight=(double)xmax/(double)ymax*cameraWidth;

const double d1=2*tan(radians(viewangle/2.0))/grid;
const double d2=d1/2;//2*tan(viewangle/4.0)/grid;
const double anm8step=0.1;
const double raise=-0.1;//0.1;

#define res (grid*precompdivs)
#define res3 (res*res*res)

#ifdef __APPLE__
#define resDirectory "~/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/res"
#else
#define resDirectory "res"
#endif

/**************** GAME  *********************/

#define maxV 20					//the player's velocity
#define accel 90				//the player's angular acceleration per second
#define angleCap 70.0			//the maximum angle in each axis the player can rotate to

#define waveTime 3000	//the time between waves of enemies; will later be replaced with better enemy spawning
#define invinceLength 0.3*CLOCKS_PER_SEC	//the amount of time the player is invisible after being hit

#define invertControls 1		//to easily toggle which key is up and which down

#endif // CONSTANTS_H_INCLUDED
