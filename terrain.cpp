#include "terrain.h"

#include "globals.h"

void updateTerrain() {

		zshft+=shftstep*(space?2:1)/4;
		zshft=(zshft>grid)?0:zshft;
}
