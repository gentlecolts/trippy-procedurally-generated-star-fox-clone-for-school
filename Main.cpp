#include "imports.h"
using namespace std;

#include "constants.h"
#include "IO.h"
#include "gameController.h"
#include "camera.h"
#include "menu.h"

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
				setupGame();
			}
		}
	}
	return 0;
}
