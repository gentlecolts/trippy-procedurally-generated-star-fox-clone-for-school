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
#include "Vec3d.h"

void BasicGun::init() {
	model=basicGunModel;
    modelSize=model->length;
}

BasicGun::BasicGun(GameObject *p) : GameObject() {
	init();
	
	lastFired=0;
	fireRate=1;
	parent=p;
	lastFired=0;
}

void BasicGun::doFire() {
	if((int)((t-lastFired)*fireRate)>0) {
		lastFired=t;
		doDoFire();
	}
}

void BasicGun::doDoFire() {
	Vec3d pos=absolutePosition();
	Vec3d ang=absoluteAngle();
	//cout<<"rot: "<<rot<<endl;
	//cout<<"ang: "<<ang<<endl;
	addLaser(new Laser(pos[0], pos[1], pos[2], ang[0], ang[1], ang[2]), player);
	//addLaser(new Laser(pos[0], pos[1], pos[2], ang[0], 0, ang[2]), player);
}

void BasicGun::update(double dt) {
}