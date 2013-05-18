//
//  SlideDownAnimation.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "SlideDownAnimation.h"
#include "imports.h"

using namespace std;

SlideDownAnimation::SlideDownAnimation(GameObject *o, GameObject *cbo, double d, double s, void (*c)(GameObject *callbackObj, GameObject *o)) : Animation(NULL, o) {
	dist=d;
	speed=s;
	callback=c;
	callbackObj=cbo;
}

void SlideDownAnimation::doModelTransform() {
	glTranslated(0, 0, -dist*t/speed);
}

void SlideDownAnimation::update(double dt) {
	if(t>speed) {
//		cout<<"calling callback!"<<endl;
		callback(callbackObj, object);
	}
}