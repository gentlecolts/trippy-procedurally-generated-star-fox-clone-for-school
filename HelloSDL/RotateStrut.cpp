//
//  RotateStrut.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/2/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "RotateStrut.h"

/**
 RotateStrut::RotateStrut(GameObject *p, Model *m, Vec3d s, Vec3d e, double t)
 Initializes the rotating strut
 */
RotateStrut::RotateStrut(GameObject *p, Model *m, Vec3d s, Vec3d e, double t) : BasicStrut() {
	init(p, m, s, e, t);
}

/**
 void RotateStrut::init(GameObject *p, Model *m, Vec3d s, Vec3d e, double t)
 Sets the parent and model, and takes takes the start angle, a second angle, and a time. If the time isn't 0, then it rotates periodically between the first and second angle (this was actually used) and otherwise it rotates in a circle such that after 1 second it'll be at the second angle of the second angle (this wasn't)
 */
void RotateStrut::init(GameObject *p, Model *m, Vec3d s, Vec3d e, double t) {
	BasicStrut::init(p, m);
	startAngle=s;
	endAngle=e;
	time=t;
	
	if(time!=0)
		velAngle=(endAngle-startAngle)/time;
	else
		velAngle=endAngle-startAngle;		//endAngle is where it ends up after 1 second
}

/**
 void RotateStrut::update(double dt)
 Rotates the strut
 */
void RotateStrut::update(double dt) {
	/*if(time==0 || (int)(t/time)%2==0) {
		rot+=velAngle*dt;
	} else {
		rot-=velAngle*dt;
	}*/
	
	
	//cout<<"angle: "<<rot<<endl;
	if(time!=0 && (int)(t/time)%2==0)
		rot=startAngle+velAngle*(fmod(t,time));
	else if(time!=0)
		rot=endAngle-velAngle*(fmod(t,time));
	else
		rot=startAngle+velAngle*t;
}

/**
 void RotateStrut::afterSetup()
 Starts its rotation at startAngle
 */
void RotateStrut::afterSetup() {
	rot+=startAngle;
}