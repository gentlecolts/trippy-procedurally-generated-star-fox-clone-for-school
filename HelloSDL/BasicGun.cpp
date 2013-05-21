//
//  BasicGun.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/25/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "BasicGun.h"
#include "../ModelConstants.h"
#include "../Model.h"
#include "../gameController.h"
#include "../Vec3d.h"

/**
 void BasicGun::init()
 Sets the model
 */
void BasicGun::init() {
	model=basicGunModel;
    modelSize=model->length;
}

/**
 BasicGun::BasicGun()
 Does basic setup. Will not be usable as parent needs to be set.
 */
BasicGun::BasicGun() : GameObject() {
	init();

	lastFired=0;
	fireRate=10;
	parent=NULL;
	health=1;
}

/**
 BasicGun::BasicGun(GameObject *p)
 Does basic setup. Parent is set, so it can be used immediately.
 */
BasicGun::BasicGun(GameObject *p) : GameObject() {
	init();

	lastFired=0;
	fireRate=10;
	parent=p;
	lastFired=0;
}

/**
 void BasicGun::doFire()
 Deals with capping the fire rate. doDoFire is another method so this can be subclassed easily.
 */
void BasicGun::doFire() {
	if((int)((t-lastFired)*fireRate)>0) {
		lastFired=t;
		doDoFire();
	}
}

/**
 void BasicGun::doDoFire()
 Creates the actual projectile and fires it.
 */
void BasicGun::doDoFire() {

	Vec3d pos=absolutePosition();
	
	Vec3d ang=absoluteAngle();
	addLaser(new Laser(pos, ang), player);
}
