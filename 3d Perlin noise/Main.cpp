#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <cmath>
//#include <string>
//#include <sstream>
//#include <fstream>
//#include <iostream>
#include <climits>
#include <xmmintrin.h>//-mfpmath=sse -msse -DHAVE_STDINT_H -m32
using namespace std;

struct pixel{
	double dist;
	uint32_t color;

	void init(uint32_t col,double distance){
		dist=distance;
		color=col;
	}
	pixel(){
		init(0,-1);
	}
	pixel(uint32_t col,double distance){
		init(col,distance);
	}
};

const int divs=8;
double delta=1.0/divs;
//#define delta 0.1
const double delt2=delta/2;
//const int deep=8;//did i have some plan to use this? i can only assume for oct/quadtrees
const int grid=8;
const double grid2=grid/2;

#define shftstep (delta/5)

#define docamdemo 0
double camx=grid2,camy=grid2;

#define fullscreen 0///TODO make this work

#if quad==0
#define drawmethod 6
#else
#define drawmethod -1
#endif

#define outline 0
#define test2d 0

#if drawmethod>=6
#define res (grid*divs)
#define res3 (res*res*res)
pixel noise[res3];

int precompindx(double x,double y,double z){
	x*=divs;
	y*=divs;
	z*=divs;

	int
	i=((int)x)%res,
	j=((int)y)%res,
	k=((int)z)%res;

	if(i<0){i+=res;}
	if(j<0){j+=res;}
	if(k<0){k+=res;}

	//cout<<"("<<x<<", "<<y<<", "<<z<<") -> "<<(int)(i+res*(j+res*k))<<endl;
	return (int)(i+res*(j+res*k));
}

double smoothxy(double x,double y,double z){
	double
		sx=x-int(x),
		sy=y-int(y);

	#define g(x,y,z) (precompindx(x,y,z))
	#define n(x,y,z) noise[g(x,y,z)].dist
	return
		(1-sy)*((1-sx)*n(x,y,z)+sx*n(x+1,y,z))+
		sy*((1-sx)*n(x,y+1,z)+sx*n(x+1,y+1,z));
	#undef g
	#undef n
}
#endif

#define doSDL 1
#define quad 0
#define tolerance 0.2

#if fullscreen
int xmax,ymax;
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
#define viewangle 60*pi/180

///Look into sse sqrt, see:
///http://assemblyrequired.crashworks.org/2009/10/16/timing-square-root/
///http://www.programmingforums.org/thread29168.html
///http://supercomputingblog.com/optimization/getting-started-with-sse-programming/

//*
double invsqrt(double x) {
    double xhalf = x/2;
    long long i =*(long long*)&x;
    i = 0x5fe6eb50c7b537a9l - (i>>1);
    x = *(double*)&i;
    x = x*(1.5 - xhalf*x*x);
	//x = x*(1.5 - xhalf*x*x);
    return x;
}/*/
float invsqrt (float x){
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f375a86 - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return x;
}
//*/

//*
#include "noise.h"/*/
#include "noise2.h"
//*/

#if doSDL==1
#include <SDL/SDL.h>
#else

#endif
bool leftmov,rightmov,upmov,downmov;
SDL_Event e;
#define dcamera 0.2
void chkCloseEvent(){
	if(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			{
			int key=e.key.keysym.sym;
			if(key==27){
				exit(0);
			}

			if(key==SDLK_DOWN || key==SDLK_s){//DOWN
				downmov=true;
			}
			if(key==SDLK_UP || key==SDLK_w){//UP
				upmov=true;
			}
			if(key==SDLK_RIGHT || key==SDLK_d){//RIGHT
				rightmov=true;
			}
			if(key==SDLK_LEFT || key==SDLK_a){//LEFT
				leftmov=true;
			}
			//cout<<key<<endl;
			break;
			}
		case SDL_KEYUP:
			{
			int key=e.key.keysym.sym;
			if(key==SDLK_DOWN || key==SDLK_s){//DOWN
				downmov=false;
			}
			if(key==SDLK_UP || key==SDLK_w){//UP
				upmov=false;
			}
			if(key==SDLK_RIGHT || key==SDLK_d){//RIGHT
				rightmov=false;
			}
			if(key==SDLK_LEFT || key==SDLK_a){//LEFT
				leftmov=false;
			}
			//cout<<key<<endl;
			break;
			}
		}
	}
}

const double rt2=1/sqrt(2);
void movecam(){
	if(leftmov){
		if(upmov!=downmov){//aka xor operator, deal w/ it
			camx-=dcamera*rt2;
		}else{
			camx-=dcamera;
		}
	}
	if(rightmov){
		if(upmov!=downmov){
			camx+=dcamera*rt2;
		}else{
			camx+=dcamera;
		}
	}
	if(upmov){
		if(leftmov!=rightmov){
			camy-=dcamera*rt2;
		}else{
			camy-=dcamera;
		}
	}
	if(downmov){
		if(leftmov!=rightmov){
			camy+=dcamera*rt2;
		}else{
			camy+=dcamera;
		}
	}

	camx=max(min(camx,(double)grid),0.0);
	camy=max(min(camy,(double)grid),0.0);

	/*
	if(!(rightmov||leftmov)){camx=(camx+grid2)/2;}
	if(!(upmov||downmov)){camy=(camy+grid2)/2;}
	//*/
}

//vWind wind(xmax,ymax,SDL_HWSURFACE | SDL_ASYNCBLIT | SDL_RLEACCEL | SDL_DOUBLEBUF | SDL_ANYFORMAT);
#define theseed \
/*0xdeadbeeb//*/\
0xdeadbeeb//*/

perlin3d perlin(theseed);
#undef theseed
pixel vals[xmax*ymax];
//double vals[xmax*ymax];
const double raise=-0.1;//0.1;
double zshft=0;

const double d=2*tan(viewangle/2.0)/grid;
SDL_Surface* screen=NULL;

//#define distanceNotDepth 1

#include "render.h"

//#define SDL_STDIO_REDIRECT
int main(int argc,char** argv){
	putenv("SDL_VIDEO_WINDOW_POS=center");
	putenv("SDL_VIDEO_CENTERED=1");

	//SDL_Delay(1000);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EnableKeyRepeat(0,0);

	#if fullscreen
	xmax=SDL_GetVideoInfo().current_w;
	#endif

	//ofstream ctt("CON");
	//FILE * ctt = fopen("CON", "w" );
	//freopen("CON","w",stdout);
	//freopen( "CON", "w", stderr );

	cout<<"test"<<endl;

	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_DOUBLEBUF);// | SDL_FULLSCREEN);
	cout<<"test2"<<endl;
	if(screen==NULL){
		cout<<"screen is null";
		exit(0xdeadbeef);
	}

	/*
	const int grid=perlin3d::grid;
	for(int i=0;i<grid*grid*grid;i++){
		cout<<perlin.vals[i]<<",";
	}//*/


	chkCloseEvent();
	cout<<"test3"<<endl;
	//SDL_Delay(1000);
	render();
	SDL_WM_SetCaption("done",NULL);
	cout<<"success";

	/*
	while(true){chkCloseEvent();zshft+=delta/5;render();SDL_Flip(screen);}/*/
	#define rotspeed 4
	while(true){
		chkCloseEvent();
		movecam();
		zshft+=shftstep;
		zshft=(zshft>grid)?0:zshft;
		#if docamdemo
		camx=grid/4*cos(rotspeed*2*pi*zshft/grid)+grid2;
		camy=grid/4*sin(rotspeed*2*pi*zshft/grid)+grid2;
		#endif
		render();
		SDL_Flip(screen);
	}//*/
	return 0;
}
