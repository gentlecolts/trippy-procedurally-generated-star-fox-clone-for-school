#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "GameObject.h"

class PlayerShip : public GameObject
{
public:
	void init(){
		modelSize=18;

		model[0]=vertex(0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f);
		model[1]=vertex(0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f);
		model[2]=vertex(1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		model[3]=vertex(0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f);
		model[4]=vertex(0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f);
		model[5]=vertex(1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		model[6]=vertex(0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f);
		model[7]=vertex(0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f);
		model[8]=vertex(-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		model[9]=vertex(0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f);
		model[10]=vertex(0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f);
		model[11]=vertex(-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		model[12]=vertex(0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f);
		model[13]=vertex(0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f);
		model[14]=vertex(-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		model[15]=vertex(0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f);
		model[16]=vertex(0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f);
		model[17]=vertex(1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	PlayerShip(){init();}

	void update() {
        xpos=camx;
        ypos=-camy;

        xvel=velX;  //camera acceleration; this is kind of backwards but oh well
        yvel=velY;
	}
protected:
private:
	int modelSize;
};
#endif // PLAYERSHIP_H
