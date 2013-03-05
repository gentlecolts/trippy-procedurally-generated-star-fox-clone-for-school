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
/*
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
//*/
using namespace std;

#include "constants.h"

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

#if drawmethod>=6 || drawmethod==4
//*
#define res (grid*precompdivs)/*/
#define res precompdivs
const double biznitch=precompdivs/grid;
//*/
#define res3 (res*res*res)
double noise[res3];

int precompindx(double x,double y,double z){
	//*
	x*=precompdivs;
	y*=precompdivs;
	z*=precompdivs;
	/*/
	x*=biznitch;
	y*=biznitch;
	z*=biznitch;
	//*/

	#if isnoisebase2
	int
	i=((int)x)&(res-1),
	j=((int)y)&(res-1),
	k=((int)z)&(res-1);
	#else
	int
	i=((int)x)%res,
	j=((int)y)%res,
	k=((int)z)%res;

	if(i<0){i+=res;}
	if(j<0){j+=res;}
	if(k<0){k+=res;}
	#endif

	//cout<<"("<<x<<", "<<y<<", "<<z<<") -> "<<(int)(i+res*(j+res*k))<<endl;
	return (int)(i+res*(j+res*k));
}

double smoothxy(double x,double y,double z){
	double
		sx=x-int(x),
		sy=y-int(y);

	#define g(x,y,z) (precompindx(x,y,z))
	//#define n(x,y,z) noise[g(x,y,z)].dist
	#define n(x,y,z) noise[g(x,y,z)]
	return
		(1-sy)*((1-sx)*n(x,y,z)+sx*n(x+1,y,z))+
		sy*((1-sx)*n(x,y+1,z)+sx*n(x+1,y+1,z));
	#undef g
	#undef n
}
#endif



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
#include "noise.cpp"/*/
#include "noise2.cpp"
//*/

struct point3d{
	#if doGL
	GLdouble x,y,z;
	#else
	double x,y,z;
	#endif

	point3d(double x0=0,double y0=0,double z0=0){
		x=x0;
		y=y0;
		z=z0;
	}
};

bool leftmov,rightmov,upmov,downmov,space;
SDL_Event e;
#define dcamera 0.2
void chkCloseEvent(){
	if(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			quitnow:
			SDL_Quit();
			exit(0);
			break;
		case SDL_KEYDOWN:
			{
			int key=e.key.keysym.sym;
			if(key==27){
				goto quitnow;
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
			if(key==SDLK_SPACE){
				//d=d2;
				space=true;
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
			if(key==SDLK_SPACE){
				//d=d1;
				space=false;
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

	if(space){
		anm8=min(anm8+anm8step,1.0);
	}else{
		anm8=max(anm8-anm8step,0.0);
	}

	d=(1-anm8)*d1+anm8*d2;

	#if doGL
	//*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective((1-anm8)*viewangle+anm8*viewangle*1.1,1,1,-1);
	//gluPerspective(180/pi*2.0 * atan2(1/2.0, d),1,1,grid+1);
	//gluPerspective(180/pi*2.0 * atan(d/2),1,1,2);
	gluPerspective(viewangle,1,1,1/d+1);
	//gluPerspective((1-anm8)*2*atan(d1)*180/pi+180/pi*anm8*2*atan(d1*grid/2),1,1,-1);//2*atan(d2*grid)*180/pi
	//gluPerspective(179,1,1,-1);
	//glFrustum(-1,1,-1,1,3,10*d);
	//*/
	#else

	#endif

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
#if fullscreen
pixel* vals;
#else
pixel vals[xmax*ymax];
#endif
//double vals[xmax*ymax];
const double raise=-0.1;//0.1;
double zshft=0;

SDL_Surface* screen=NULL;

//#define distanceNotDepth 1

#include "render.cpp"

//#define SDL_STDIO_REDIRECT
int main(int argc,char** argv){
	putenv("SDL_VIDEO_WINDOW_POS=center");
	putenv("SDL_VIDEO_CENTERED=1");

	//SDL_Delay(1000);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EnableKeyRepeat(0,0);

	//ofstream ctt("CON");
	//FILE * ctt = fopen("CON", "w" );
	//freopen("CON","w",stdout);
	//freopen( "CON", "w", stderr );

	#if fullscreen
	vals=new pixel[xmax*ymax];
	#endif

	cout<<"test"<<endl;

	#if doGL
	glPreInit();
	//screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL);// | SDL_FULLSCREEN);

	#if fullscreen
	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_OPENGL | SDL_FULLSCREEN);
	#else
	//screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);
	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_OPENGL);
	#endif
	#else
	#if fullscreen
	screen=SDL_SetVideoMode(xmax,ymax,SDL_GetVideoInfo()->vfmt->BitsPerPixel,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	#else
	//screen=SDL_SetVideoMode(xmax,ymax,SDL_GetVideoInfo()->vfmt->BitsPerPixel,SDL_HWSURFACE | SDL_DOUBLEBUF);// | SDL_FULLSCREEN);
	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_DOUBLEBUF);// | SDL_FULLSCREEN);
	#endif
	#endif

	cout<<"test2"<<endl;
	if(screen==NULL){
		cout<<"screen is null";
		exit(0xdeadbeef);
	}

	#if doGL
	glInit();
	#endif

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

	#if doGL
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	#endif
	while(true){
		#if doGL
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		#endif

		chkCloseEvent();
		movecam();
		zshft+=shftstep*(space?2:1)/4;
		zshft=(zshft>grid)?0:zshft;
		#if docamdemo
		camx=grid/4*cos(rotspeed*2*pi*zshft/grid)+grid2;
		camy=grid/4*sin(rotspeed*2*pi*zshft/grid)+grid2;
		#endif
		//*
		render();
		/*/
		glMatrixMode(GL_MODELVIEW);//dont need to do this each time
		glLoadIdentity( );//do need to do this each time
		glTranslatef( 0.0, 0.0, -1.0 );
		glRotated(360*zshft/grid-180,0,1,0);
		//double co=cos(2*pi*zshft/grid),si=sin(2*pi*zshft/grid);
		glBegin(GL_QUADS);

		glColor3f(0.5f,0.5f,0.5f);glVertex3f(-0.5f,-0.5f,-0.5);
		glColor3f(0.5f,0.5f,0.5f);glVertex3f(-0.5f,-0.5f,0.5);
		glColor3f(0.5f,0.5f,0.5f);glVertex3f(-0.5f,0.5f,0.5f);
		glColor3f(0.5f,0.5f,0.5f);glVertex3f(-0.5f,0.5f,-0.5f);

		glColor3f(0.5f,0.5f,0.5f);glVertex3f(-0.5f,0.5f,0.0f);
		glColor3f(0.5f,0.5f,0.5f);glVertex3f(-0.5f,-0.5f,0.0f);
		glColor3f(0.5f,0.5f,0.5f);glVertex3f(0.5f,-0.5f,0.0f);
		glColor3f(0.5f,0.5f,0.5f);glVertex3f(0.5f,0.5f,0.0f);

		//glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
        //glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
        //glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
        //glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
		glEnd();
		//*/

		SDL_GL_SwapBuffers();
		//SDL_Flip(screen);
	}//*/
	return 0;
}
