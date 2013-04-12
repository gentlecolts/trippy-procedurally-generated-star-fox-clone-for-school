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
void Animation::update(){}

Animation::Animation(Model *m, GameObject *o) {
	st=clock();
	model=m;
}

Animation::~Animation() {
	
}

void Animation::tick() {
	t=clock()-st;
}