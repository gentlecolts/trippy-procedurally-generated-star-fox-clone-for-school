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
#include "Vec3d.h"
#include "gameController.h"
#include "GameObject.h"

#include <ctime>

/**
 void ExplodeAnimation::doTriangleTransform(int index)
 Translates in the direction of the triangle's normal proportionally to the animation's tie counter
 */
void ExplodeAnimation::doTriangleTransform(int index) {

	double mult=16*t;

	glTranslatef(model->normals[index/3][0]*mult, model->normals[index/3][1]*mult, model->normals[index/3][2]*mult);

	//rotate maybe
}

/**
 void ExplodeAnimation::update(double dt)
 Deletes its parent object after .5 seconds
 */
void ExplodeAnimation::update(double dt) {
	if(t>.5) {
		if(object!=NULL)
			object->destroy();
	}
}

ExplodeAnimation::ExplodeAnimation(Model *m, GameObject *o) : Animation(m, o) {

}
