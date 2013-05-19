#include "imports.h"
using namespace std;

#include "constants.h"
#include "IO.h"
#include "gameController.h"
#include "camera.h"
#include "HelloSDL/menu.h"
#include "GLHelper.h"

int main(int argc,char** argv){
    initSDL();

	#define rotspeed 4

	launchMenu();

//	doTests();

	while(true){
		chkCloseEvent();

		if(inGame) {

			movecam();

			updateObjects();

			render();
			SDL_GL_SwapBuffers();
		} else {
			picture::updateAll(&e);

			SDL_Flip(screen);

			if(inGame) {
				if(!didGameSetup)
					setupGame();

				if(screen!=NULL) {
					SDL_FreeSurface(screen);
				}
				
				screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_OPENGL);
				//crashes here sometimes
				glInit();

				glMatrixMode(GL_MODELVIEW);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
		}
	}
	return 0;
}
