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
#include "gameController.h"
#include "vec3f.h"

void BasicGun::init() {
	model=basicGunModel;
    modelSize=model->length;
}

BasicGun::BasicGun(GameObject *p) : GameObject() {
	init();
	
	parent=p;
}

void BasicGun::fireWeapon() {
	Vec3f pos=absolutePosition();
	Vec3f ang=absoluteAngle();
	addLaser(new Laser(pos[0], pos[1], pos[2], ang[0], ang[1], ang[2]));
	cout<<"pos[0]: "<<pos[0]<<endl;
}

void BasicGun::update(double dt) {
}