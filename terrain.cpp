#include "terrain.h"

#include "globals.h"
#include "gameShip.h"

void updateTerrain(double dt) {

	//zshft+=shftstep*(space?2:1)/4;
	zshft-=thePlayerShip->vel[2]*dt/frameSize;
	zshft=(zshft>grid)?0:zshft;
}
