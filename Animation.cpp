//
//  Animation.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/10/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "Animation.h"
#include "GameObject.h"

void Animation::doModelTransform() {}				//Do transforms that apply to the whole model
void Animation::doTriangleTransform(int index) {}	//Do transforms for each individual triangle
void Animation::update(double dt){}					//Do any updating of the animation's state

/**
 Animation::Animation(Model *m, GameObject *o)
 Set t to 0, model, and object
 */
Animation::Animation(Model *m, GameObject *o) {
	t=0;
	model=m;
	object=o;
}

Animation::~Animation() {
	
}

/**
 void Animation::tick(double dt)
 Increment t by dt, call update
 */
void Animation::tick(double dt) {
	t+=dt;
	
	update(dt);
}