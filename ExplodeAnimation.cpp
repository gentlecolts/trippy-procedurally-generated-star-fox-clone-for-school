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

#include <ctime>

void ExplodeAnimation::doTriangleTransform(int index) {

	double mult=16*t;
	//cout<<mult<<endl;

	//cout<<"x "<<model->normals[index/3][0]*mult;

	glTranslatef(model->normals[index/3][0]*mult, model->normals[index/3][1]*mult, model->normals[index/3][2]*mult);

	//rotate shit
}

void ExplodeAnimation::update(double dt) {
	if(t>16) {
		//if(object!=NULL) {
			destroy(object);
		//}
	}
}

ExplodeAnimation::ExplodeAnimation(Model *m, GameObject *o) : Animation(m, o) {

}
