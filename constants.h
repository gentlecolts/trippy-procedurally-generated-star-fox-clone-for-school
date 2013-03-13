#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

	//const int
	#define divs 4
	const double delta=1.0/divs;
	//const int
	//#define isnoisebase2 true//requires that precompdivs*grid is a power of 2
	#define precompdivs 32//should be at least divs times 2
	const double precompdelta=1.0/precompdivs;
	//#define delta 0.1
	const double delt2=delta/2;
	//const int deep=8;//did i have some plan to use this? i can only assume for oct/quadtrees
	//const int grid=8;
	#define grid 8
	const double grid2=grid/2;

	//#define shftstep (delta/5)
	#define shftstep (1.0/20)

	#define docamdemo 0
	double camx=0,camy=0;
	double velX=0, velY=0;
	#define maxV 0.5
	#define accel 0.005

	#define fullscreen 0

	/**important values for drawmethod
	 * 4 -> trace
	 * 6 -> best non-gl squares
	 * 9 -> opengl
	 * 11-> opencl trace, needs to be finished
	 */
	#define drawmethod 9
	#define shadenorm 0

	#define outline 1
	//#define line_thick 2

	#define test2d 0

	#define doSDL 1
	#if drawmethod>7
		#define doGL 1
	#else
		#define doGL 0
	#endif

	#define tolerance 0.3

	#if doSDL
	#include <SDL/SDL.h>
	#else
	///TODO learn 2 sfml
	#endif

	#if doGL

	/*
	#include <SDL/SDL_opengl.h>
	/*/
	#include <GL/gl.h>
	#include <GL/glu.h>
	//*/
	#endif

	#if drawmethod==11
	#include <CL/cl.hpp>
	#endif

	//here because glu.h has something called quad
	#if drawmethod<0 || drawmethod==10
		#define quad 1
	#else
		#define quad 0
	#endif

	#if fullscreen
		/*first doesnt work, it happens before sdl init is called
		const int
		xmax=SDL_GetVideoInfo()->current_w,
		ymax=SDL_GetVideoInfo()->current_h;
		/*/
		#define xmax (SDL_GetVideoInfo()->current_w)
		#define ymax (SDL_GetVideoInfo()->current_h)
		//*/
	#else
		/*
		#define xmax 1280
		#define ymax 720
		/*/
		#define xmax 640
		#define ymax 480
		//*/
	#endif

	#define pi 3.141592653589793238462643383279502884197169l
	#define viewangle 60
	const double d1=2*tan(viewangle/2.0*pi/180)/grid;
	const double d2=d1/2;//2*tan(viewangle/4.0)/grid;
	const double anm8step=0.1;
	double anm8=0;
	double d=d1;

#endif // CONSTANTS_H_INCLUDED
