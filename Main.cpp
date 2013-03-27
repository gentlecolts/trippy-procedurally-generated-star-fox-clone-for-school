#include <SDL/SDL.h>
#include <iostream>

using namespace std;

#include "constants.h"
#include "IO.h"
#include "terrain.h"
#include "gameController.h"
#include "camera.h"

int main(int argc,char** argv){
    initSDL();

	#define rotspeed 4

    setupGame();

	while(true){
		chkCloseEvent();
		movecam();
		updateTerrain();

		render();
		updateObjects();

		#if doGL
		SDL_GL_SwapBuffers();
		#else
		SDL_Flip(screen);
		#endif
	}
	return 0;
}
