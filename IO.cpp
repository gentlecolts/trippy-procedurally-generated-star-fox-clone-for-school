#include "IO.h"
#include <SDL/SDL.h>
#include "imports.h"
#include "globals.h"
#include "gameController.h"
#include "gameObject.h"
//#include "glHelfagoot/j"
#include "glhelper.h"

void initSDL() {
    putenv("SDL_VIDEO_WINDOW_POS=center");
	putenv("SDL_VIDEO_CENTERED=1");

	//SDL_Delay(1000);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EnableKeyRepeat(0,0);

    #if doGL
	glPreInit();
	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_OPENGL);
	#else
	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_DOUBLEBUF);// | SDL_FULLSCREEN);
	#endif

	if(screen==NULL){
		cout<<"screen is null";
		exit(0xdeadbeef);
	}

	#if doGL
	glInit();
	#endif

	chkCloseEvent();

	SDL_WM_SetCaption("done",NULL);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void chkCloseEvent(){
	if(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			quitnow:
			    unloadGame();
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
				if(invertControls)
					downmov=true;
				else
					upmov=true;
			}
			if(key==SDLK_UP || key==SDLK_w){//UP
					if(invertControls)
						upmov=true;
					else
						downmov=true;
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
				if(invertControls)
					downmov=false;
				else
					upmov=false;
			}
			if(key==SDLK_UP || key==SDLK_w){//UP
				if(invertControls)
					upmov=false;
				else
					downmov=false;
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
			if(key==SDLK_RETURN){
                gameObjects[0]->fireWeapon();       //HACKY FIX LATER
			}
			//cout<<key<<endl;
			break;
			}
		}
	}
}
