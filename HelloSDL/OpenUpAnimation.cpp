//
//  OpenUpAnimation.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "OpenUpAnimation.h"
#include "../imports.h"

//not used; was going to have the sides of the rocket launcher slide open to let the ammo slide in

OpenUpAnimation::OpenUpAnimation(GameObject *obj, Model *m, double t, int f) : Animation(m, obj) {
	time=t;
	face=f;
}

void OpenUpAnimation::doTriangleTransform(int n) {
	if(n==face) {
		if(t<time) {
			//get 90º angle to normal, translate along it
		}
	}
}

void OpenUpAnimation::update(double dt) {

}
