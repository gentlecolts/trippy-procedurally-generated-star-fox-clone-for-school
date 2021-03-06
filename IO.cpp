
#include "IO.h"
#include <SDL/SDL.h>
#include "imports.h"
#include "globals.h"
#include "gameController.h"
#include "gameShip.h"
#include "glhelper.h"
#include "guilib/guiobj.h"

#include "HelloSDL/menu.h"

/**
 void initSDL()
 Initializes the window
 */
void initSDL() {
    putenv("SDL_VIDEO_WINDOW_POS=center");
	putenv("SDL_VIDEO_CENTERED=1");

	//SDL_Delay(1000);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EnableKeyRepeat(0,0);

    #if doGL
	glPreInit();
	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_HWPALETTE | SDL_HWACCEL | SDL_DOUBLEBUF | SDL_SRCALPHA | SDL_ASYNCBLIT);
//	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_OPENGL);
	#else
	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_DOUBLEBUF);// | SDL_FULLSCREEN);
	#endif

	if(screen==NULL){
		cout<<"screen is null";
		exit(0xdeadbeef);
	}

	#if doGL
//	glInit();
	#endif

	picture::target=screen;

	chkCloseEvent();

	SDL_WM_SetCaption("done",NULL);
}

/**
 void quit(button *b)
 Quits the game
 */
void quit(button *b) {
	unloadGame();
	SDL_Quit();
	exit(0);
}


/**
 void chkCloseEvent()
 Handles keyboard input (the name doesn't make much sense), and closes the game if necessrily
 */
void chkCloseEvent(){
	if(needToUnload) {
		inGame=false;
		screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_HWPALETTE | SDL_HWACCEL | SDL_DOUBLEBUF | SDL_SRCALPHA | SDL_ASYNCBLIT);

		unloadGame();
		didGameSetup=false;
		needToUnload=false;
		cout<<"score: "<<playerScore<<endl;
	}

	if(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			quit(NULL);
			break;
		case SDL_KEYDOWN:
			{
			int key=e.key.keysym.sym;
			if(key==27){
				inGame=false;
				screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_HWPALETTE | SDL_HWACCEL | SDL_DOUBLEBUF | SDL_SRCALPHA | SDL_ASYNCBLIT);
			}

			if(key==SDLK_p){
				play(NULL);
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
			if(key==SDLK_RETURN){
				fire=true;
			}
			if(key==SDLK_QUOTE) {
				fireRockets=true;
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
                fire=false;
			}
			if(key==SDLK_QUOTE) {
				fireRockets=false;
			}
			//cout<<key<<endl;
			break;
			}
		}
	}
}
