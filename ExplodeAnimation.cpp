//
//  ExplodeAnimation.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/11/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "ExplodeAnimation.h"
#include "imports.h"
#include "Model.h"
#include "vec3f.h"
#include "gameController.h"

void ExplodeAnimation::doTriangleTransform(int index) {
	
	double mult=((double)16*t)/(CLOCKS_PER_SEC);
	//cout<<mult<<endl;
	
	//cout<<"x "<<model->normals[index/3][0]*mult;
	
	glTranslatef(model->normals[index/3][0]*mult, model->normals[index/3][1]*mult, model->normals[index/3][2]*mult);
	
	//rotate shit
}

void ExplodeAnimation::update() {
	if(((double)16*t)/(CLOCKS_PER_SEC)) {
		destroy(object);
	}
}

ExplodeAnimation::ExplodeAnimation(Model *m, GameObject *o) : Animation(m, o) {
	
}