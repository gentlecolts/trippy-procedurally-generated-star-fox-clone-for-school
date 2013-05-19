//
//  RamShip.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/15/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "RamShip.h"
#include "ModelConstants.h"
#include "Model.h"
#include "constants.h"
#include "HelloSDL/BasicGun.h"
#include "HelloSDL/FanStrutThing.h"

/**
 RamShip::RamShip(Model *m)
 Creates a RamShip with a given model
 */
RamShip::RamShip(Model *m) : EnemyShip() {
	model=m;
    modelSize=m->length;
}

/**
 RamShip::RamShip(double x, double y)
 Just calls init and super and sets the model
 */
RamShip::RamShip(Model *m, double x, double y) : EnemyShip(x, y) {
	init(x,y, -50, 4);

	model=m;
    modelSize=m->length;
}


/**
 void RamShip::init(double x, double y, int startPos, int time)
 Calculates pos[0] and pos[1] as the points around the edge of the game in line with the target position and sets vel[0], vel[1], and vel[2] so that it will intersect the plane at -playerOffset at (x,y) after time seconds
 */
void RamShip::init(double x, double y, int startPos, int time) {
	if(x==0) {
		x=0.001;
	} else if(y==0) {
		y=0.001;
	}

	if(abs(x)>abs(y)) {
		pos[0]=frameSize;
		pos[1]=abs(y/x*frameSize);
	} else {
		pos[1]=frameSize;
		pos[0]=abs(x/y*frameSize);
	}

	pos[0]*=signum(x);
	pos[1]*=signum(y);

    pos[2]=startPos-playerOffset;

    vel[0]=-(pos[0]-x)/time;
    vel[1]=(pos[1]-y)/time;
    vel[2]=(pos[2]+playerOffset-thePlayerShip->vel[2]*time)/time;

	rot=invGetVector(pos-Vec3d(x,y,playerOffset));
}

/**
 bool RamShip::isDone()
 Returns whether it's behind the camera; it starts off the screen to the side, and isn't done, so the superclass version doesn't work in this case
 */
bool RamShip::isDone() {
	return pos[2]>=cameraOffset || abs(pos[0])>frameSize*1.5 || abs(pos[1])>frameSize*1.5;
}

/**
 void RamShip::update(double dt)
 Calls the superclass version, and fires the weapons
 */
void RamShip::update(double dt) {
	EnemyShip::update(dt);
	
	fireWeapon();
}
