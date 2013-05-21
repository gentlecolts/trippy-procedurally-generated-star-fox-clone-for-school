//
//  SlideDownAnimation.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "SlideDownAnimation.h"
#include "../imports.h"

using namespace std;

/**
 SlideDownAnimation::SlideDownAnimation(GameObject *o, GameObject *cbo, double d, double s, void (*c)(GameObject *callbackObj, GameObject *o))
	Initializes with target object o, object to recieve the callback cbo, distance to travel d, speed s, and callback method callbackObj
 */
SlideDownAnimation::SlideDownAnimation(GameObject *o, GameObject *cbo, double d, double s, void (*c)(GameObject *callbackObj, GameObject *o)) : Animation(NULL, o) {
	dist=d;
	speed=s;
	callback=c;
	callbackObj=cbo;
}

//Slides the model down
void SlideDownAnimation::doModelTransform() {
	glTranslated(0, 0, -dist*t/speed);
}

//If it's done, calls the callback
void SlideDownAnimation::update(double dt) {
	if(t>speed) {
//		cout<<"calling callback!"<<endl;
		callback(callbackObj, object);
	}
}
