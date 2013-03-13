#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "GameObject.h"

float playerModel[][6]={
        {0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f},
        {0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f},
        {0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f},
        {0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f},
        {0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    };

class PlayerShip : GameObject
{
public:
	PlayerShip(){
		model=playerModel;
		modelSize=18;
	}

	void update() {
        xpos=camx;
        ypos=camy;

        xvel=velX;  //camera acceleration; this is kind of backwards but oh well
        yvel=velY;
	}
protected:
private:
	int modelSize;
};
#endif // PLAYERSHIP_H
