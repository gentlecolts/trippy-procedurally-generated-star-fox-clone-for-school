#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <cmath>

/**************** NOISE ********************/
#define theseed 0xdeadbeeb

#define grid 8
const double grid2=grid/2;

#define divs 4
const double delta=1.0/divs;
const double delt2=delta/2;

#define shftstep (1.0/20)

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

#define tolerance 0.3


/**************** MATH  *********************/

const double rt2=1/sqrt(2);
#define pi 3.141592653589793238462643383279502884197169l

/**************** CAMERA ********************/
#define maxV 0.2
#define accel 0.01

#define xmax 640
#define ymax 480

#define viewangle 60

const double d1=2*tan(viewangle/2.0*pi/180)/grid;
const double d2=d1/2;//2*tan(viewangle/4.0)/grid;
const double anm8step=0.1;
const double raise=-0.1;//0.1;

#define res (grid*precompdivs)
#define res3 (res*res*res)

/**************** GAME  *********************/
#define numGameObjects 4

#endif // CONSTANTS_H_INCLUDED
