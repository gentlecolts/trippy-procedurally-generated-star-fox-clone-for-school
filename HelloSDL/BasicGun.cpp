//
//  BasicGun.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/25/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "BasicGun.h"
#include "ModelConstants.h"
#include "Model.h"

void BasicGun::init() {
	model=basicGunModel;
    modelSize=model->length;
}

BasicGun::BasicGun(GameObject *p) : GameObject() {
	init();
	
	parent=p;
}

void BasicGun::fireWeapon() {
	
}

void BasicGun::update(double dt) {
}