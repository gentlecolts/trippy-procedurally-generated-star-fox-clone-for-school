//
//  TrackingShip.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/13/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "TrackingShip.h"

#include "../ModelConstants.h"
#include "../Model.h"
#include "../constants.h"
#include "BasicGun.h"
#include "FanStrutThing.h"
#include "AimingStrut.h"

/**
 TrackingShip::TrackingShip(double x, double y, int n)
 Just calls init and super and sets the model
 */
TrackingShip::TrackingShip(Model *m, double x, double y) : EnemyShip(x, y) {
	model=ramShipModel;
    modelSize=model->length;

	init(x,y,-5,8);
}

/**
 TrackingShip::TrackingShip(Model *m)
 Sets the model
 */
TrackingShip::TrackingShip(Model *m) : EnemyShip() {
	model=ramShipModel;
    modelSize=model->length;
}

/**
 void TrackingShip::init(double x, double y, int startPos, int t)
 Calculates pos[0] and pos[1] as the points around the edge of the game in line with the target position and sets vel[0], vel[1], and vel[2] so that it will intersect the plane at -playerOffset at (x,y) after t if it didn't pause
 */
void TrackingShip::init(double x, double y, int startPos, int t) {
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


	pauseTime=8;

    pos[2]=startPos-playerOffset;

    vel[0]=-(pos[0]-x)/(time/2);
    vel[1]=(pos[1]-y)/(time/2);
    vel[2]=(pos[2]+playerOffset-thePlayerShip->vel[2]*time)/time;

	time=t;
	oldVel=vel;
}

/**
 bool TrackingShip::isDone()
 Returns whether it's behind the camera; it starts off the screen to the side, and isn't done, so the superclass version doesn't work in this case
 */
bool TrackingShip::isDone() {
	return pos[2]>=cameraOffset || abs(pos[0])>frameSize*1.5 || abs(pos[1])>frameSize*1.5;
}

/**
 void TrackingShip::update(double dt)
 First moves it, then has it follow the player, then has it continue its motion, firing its weapon when it hovers.
 */
void TrackingShip::update(double dt) {
	EnemyShip::update(dt);

	if(t>time/2+pauseTime || t<time/2) {
		if(vel[0]!=oldVel[0] ||
		   vel[1]!=oldVel[1] ||
		   vel[2]!=oldVel[2] )
			vel=oldVel;
	} else {
		vel=Vec3d(thePlayerShip->vel[0],-thePlayerShip->vel[1],-thePlayerShip->vel[2]);
		
		fireWeapon();
	}
}
