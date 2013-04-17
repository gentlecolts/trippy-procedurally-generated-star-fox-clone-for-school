//
//  Animation.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/10/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "Animation.h"
#include "GameObject.h"

void Animation::doModelTransform() {}
void Animation::doTriangleTransform(int index) {}
void Animation::update(double dt){}

Animation::Animation(Model *m, GameObject *o) {
	t=clock()/CLOCKS_PER_SEC;
	model=m;
	object=o;
}

Animation::~Animation() {
	
}

void Animation::tick(double dt) {
	t+=dt;
	
	update(dt);
}