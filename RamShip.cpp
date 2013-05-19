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

RamShip::RamShip(Model *m) : EnemyShip(0) {
	model=m;
    modelSize=m->length;
}

/**
 RamShip::RamShip(double x, double y, int n)
 Just calls init and super
 */
RamShip::RamShip(Model *m, double x, double y, int n) : EnemyShip(x, y, n) {
	init(x,y, -50, 4);

	model=m;
    modelSize=m->length;
}


/**
 void RamShip::init(double x, double y)
 Sets the model to the constant ramShipModel, then calculates pos[0] and pos[1] as the points around the edge of the game in line with the target position and sets vel[0], vel[1], and vel[2] so that it will intersect the plane at -playerOffset at (x,y)
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

void RamShip::afterSetup() {

	/*addChild(new BasicGun(this),-1);
	addChild(new BasicGun(this),-1);
	addChild(new BasicGun(this),-1);
	addChild(new BasicGun(this),-1);
	addChild(new BasicGun(this),-1);
	addChild(new BasicGun(this),-1);
	addChild(new BasicGun(this),-1);
	addChild(new BasicGun(this),-1);*/


	/*addChild(new FanStrut(this, 5, basicStrutModel), -1);
	addChild(new FanStrut(this, 5, basicStrutModel), -1);
	addChild(new FanStrut(this, 5, basicStrutModel), -1);
	addChild(new FanStrut(this, 5, basicStrutModel), -1);
	addChild(new FanStrut(this, 5, basicStrutModel), -1);
	addChild(new FanStrut(this, 5, basicStrutModel), -1);
	addChild(new FanStrut(this, 5, basicStrutModel), -1);
	addChild(new FanStrut(this, 5, basicStrutModel), -1);*/


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
 Calls the superclass version, sets vel[2] so that it curves parabolically into its target point at (x, y, -playerOffset), then rotates slightly
 */
void RamShip::update(double dt) {
	double oldT=t;
	EnemyShip::update(dt);

	//rot[1]+=45*dt;

	double fireRate=0.01;

	//if(fmod(t,fireRate)<=fireRate/2 && fmod(oldT,fireRate)>=fireRate/2) {
		fireWeapon();
	//}
}
