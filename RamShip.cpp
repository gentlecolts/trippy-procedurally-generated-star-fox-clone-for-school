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

/**
 RamShip::RamShip(double x, double y, int n)
 Just calls init and super
 */
RamShip::RamShip(double x, double y, int n) : EnemyShip(x, y, n) {
	init(x,y);
}


/**
 void RamShip::init(double x, double y)
 Sets the model to the constant ramShipModel, then calculates xpos and ypos as the points around the edge of the game in line with the target position and sets xvel, yvel, and zvel so that it will intersect the plane at -playerOffset at (x,y)
 */
void RamShip::init(double x, double y) {
	model=ramShipModel;
    modelSize=model->length;
	
	if(x==0) {
		x=0.001;
	} else if(y==0) {
		y=0.001;
	}
	
	double a=atan2(y, x);
	
	if(a>-pi/4 && a<=pi/4) {
		xpos=noiseScale;
		ypos=y/x*noiseScale;
	} else if(a>pi/4 && a<=3*pi/4) {
		ypos=noiseScale;
		xpos=x/y*noiseScale;
	} else if(a>3*pi/4 || a<=-3*pi/4) {
		xpos=-noiseScale;
		ypos=y/x*noiseScale;
	} else if(a>-3*pi/4 && a<=-pi/4) {
		ypos=-noiseScale;
		xpos=x/y*noiseScale;
	}
	
    zpos=-5-playerOffset;
	
    xvel=-(xpos-x)/3;
    yvel=-(ypos-y)/3;
    zvel=0;
	
    xrot=0;
    yrot=0;
    zrot=0;
}


/**
 bool RamShip::isDone()
 Returns whether it's behind the camera; it starts off the screen to the side, and isn't done, so the superclass version doesn't work in this case
 */
bool RamShip::isDone() {
	return zpos>=cameraOffset;
}

/**
 void RamShip::update(double dt)
 Calls the superclass version, sets zvel so that it curves parabolically into its target point at (x, y, -playerOffset), then rotates slightly
 */
void RamShip::update(double dt) {
	EnemyShip::update(dt);
	
	zvel-=1.0/5*t*dt;
	//cout<<zvel<<endl;
	
	yrot+=dt;
}