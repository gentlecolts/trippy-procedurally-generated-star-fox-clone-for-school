//
//  RotateStrut.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/2/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "RotateStrut.h"

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

void RotateStrut::afterSetup() {
	rot+=startAngle;
}

RotateStrut::RotateStrut(GameObject *p, Model *m, Vec3d s, Vec3d e, double t) : BasicStrut(p, m) {
	startAngle=s;
	endAngle=e;
	time=t;
	
	if(time!=0)
		velAngle=(endAngle-startAngle)/time;
	else
		velAngle=endAngle-startAngle;		//endAngle is where it ends up after 1 second
}