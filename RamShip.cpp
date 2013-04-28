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
#include "BasicGun.h"

/**
 RamShip::RamShip(double x, double y, int n)
 Just calls init and super
 */
RamShip::RamShip(double x, double y, int n) : EnemyShip(x, y, n) {
	init(x,y);
}


/**
 void RamShip::init(double x, double y)
 Sets the model to the constant ramShipModel, then calculates pos[0] and pos[1] as the points around the edge of the game in line with the target position and sets vel[0], vel[1], and vel[2] so that it will intersect the plane at -playerOffset at (x,y)
 */
void RamShip::init(double x, double y) {
	cout<<"ENEMY"<<endl;
	
	model=ramShipModel;
    modelSize=model->length;
	
	if(x==0) {
		x=0.001;
	} else if(y==0) {
		y=0.001;
	}
	
	if(abs(x)>abs(y)) {
		pos[0]=noiseScale;
		pos[1]=abs(y/x*noiseScale);
	} else {
		pos[1]=noiseScale;
		pos[0]=abs(x/y*noiseScale);
	}
	
	pos[0]*=signum(x);
	pos[1]*=signum(y);
	
	int startPos=-50,time=8;
	
    pos[2]=startPos-playerOffset;
	
    vel[0]=-(pos[0]-x)/time;
    vel[1]=(pos[1]-y)/time;
    vel[2]=(pos[2]+playerOffset-thePlayerShip->vel[2]*time)/time;
}

void RamShip::afterSetup() {
	
	addChild(new BasicGun(this));
	/*addChild(new BasicGun(this));
	addChild(new BasicGun(this));
	addChild(new BasicGun(this));
	addChild(new BasicGun(this));
	addChild(new BasicGun(this));
	addChild(new BasicGun(this));
	addChild(new BasicGun(this));*/
	
}

/**
 bool RamShip::isDone()
 Returns whether it's behind the camera; it starts off the screen to the side, and isn't done, so the superclass version doesn't work in this case
 */
bool RamShip::isDone() {
	return pos[2]>=cameraOffset;
}

/**
 void RamShip::update(double dt)
 Calls the superclass version, sets vel[2] so that it curves parabolically into its target point at (x, y, -playerOffset), then rotates slightly
 */
void RamShip::update(double dt) {
	EnemyShip::update(dt);
	
	//yrot+=45*dt;
}