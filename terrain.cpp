#include "terrain.h"

#include "globals.h"
#include "GameObject.h"

void updateTerrain(double dt) {

	//zshft+=shftstep*(space?2:1)/4;
	zshft-=thePlayerShip->zvel*dt/noiseScale;
	zshft=(zshft>grid)?0:zshft;
}
