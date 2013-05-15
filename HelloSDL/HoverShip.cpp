//
//  HoverShip.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/2/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "HoverShip.h"

#include "ModelConstants.h"
#include "Model.h"
#include "constants.h"
#include "BasicGun.h"
#include "FanStrutThing.h"
#include "AimingStrut.h"

/**
 HoverShip::HoverShip(double x, double y, int n)
 Just calls init and super
 */
HoverShip::HoverShip(Model *m, double x, double y, int n) : EnemyShip(x, y, n) {
	model=ramShipModel;
    modelSize=model->length;
	
	init(x,y,-5,8);
}

HoverShip::HoverShip(Model *m) : EnemyShip(0) {
	model=ramShipModel;
    modelSize=model->length;
}

/**
 void HoverShip::init(double x, double y)
 Sets the model to the constant HoverShipModel, then calculates pos[0] and pos[1] as the points around the edge of the game in line with the target position and sets vel[0], vel[1], and vel[2] so that it will intersect the plane at -playerOffset at (x,y)
 */
void HoverShip::init(double x, double y, int startPos, int t) {
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
	
	pauseTime=8;
	time=t;
	
    pos[2]=startPos-playerOffset;
	
    vel[0]=-(pos[0]-x)/(time/2);
    vel[1]=(pos[1]-y)/(time/2);
    vel[2]=(pos[2]+playerOffset-thePlayerShip->vel[2]*time)/time;
	
	oldVel=vel;
}

bool HoverShip::isDone() {
	return pos[2]>=cameraOffset || abs(pos[0])>noiseScale*1.5 || abs(pos[1])>noiseScale*1.5;
}

void HoverShip::afterSetup() {
	//rot[1]+=180;
	
	//addChild(new FanStrut(this, 5, basicStrutModel), 0);
	//addChild(new FanStrut(this, 5, basicStrutModel), 1);//, Vec3d(0,0,30));
	//addChild(new AimingStrut(this, 9000, longStrutModel), 0);
	//addChild(new AimingStrut(this, 9000, longStrutModel), 0);
	
	/*for(int i=0;i<model->numAttachPoints;i++) {
		addChild(new AimingStrut(this, 9000, basicStrutModel), i);
		children[i]->addChild(new BasicGun(children[i]), 1);
	}*/
	
	lastT=t;
}

/**
 void HoverShip::update(double dt)
 Calls the superclass version, sets vel[2] so that it curves parabolically into its target point at (x, y, -playerOffset), then rotates slightly
 */
void HoverShip::update(double dt) {
	EnemyShip::update(dt);
	
	if(t>time/2+pauseTime || t<time/2) {
		if(vel[0]!=oldVel[0] ||
		   vel[1]!=oldVel[1] ||
		   vel[2]!=oldVel[2] )
			vel=oldVel;
	} else {
		vel=Vec3d(0,0,-thePlayerShip->vel[2]);
	}
	
	//double fireRate=1.0;
	
	//if(fmod(t,fireRate)<=fireRate/2 && fmod(lastT,fireRate)>=fireRate/2) {
		fireWeapon();
	//}
	
	lastT=t;
}
