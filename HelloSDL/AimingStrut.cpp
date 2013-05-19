//
//  AimingStrut.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/3/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "AimingStrut.h"
#include "../globals.h"
#include "../gameShip.h"

/**
 AimingStrut::AimingStrut()
 Doesn't do much
 */
AimingStrut::AimingStrut() : BasicStrut() {
}

/**
 AimingStrut::AimingStrut(GameObject *p, double s, Model *m)
 Initializes parent, speed, and sets model
 */
AimingStrut::AimingStrut(GameObject *p, double s, Model *m) : BasicStrut() {
	init(p, s, m);
}

/**
 void AimingStrut::init(GameObject *p, double s, Model *m)
 Does superclass init, sets speed
 */
void AimingStrut::init(GameObject *p, double s, Model *m) {
	BasicStrut::init(p, m);

	speed=s;
}

/**
 void AimingStrut::update(double dt)
 Tries to face the first thing on the opposite side (with opposite value for player), moving at a maximum speed of speed
 */
void AimingStrut::update(double dt) {
	Vec3d targetPoint;
	GameShip *target;
	if(player) {
		target=thePlayerShip->getNext();
		if(target==NULL)
			return;

		while(target->player) {
			target=target->getNext();

			if(target==NULL)
				return;
		}
	} else {
		target=thePlayerShip;
	}

	targetPoint=target->absolutePosition();

	Vec3d dist=-(targetPoint-absolutePosition());

	if(!player)
		dist=-dist;

	Vec3d angles=invGetVector(dist);



	if(parent!=NULL)
		angles-=parent->absoluteAngle();

	Vec3d diff=angles-rot;
	if(diff.magnitude()>speed) {
		diff=speed*diff.normalize();
	}

	rot+=diff*dt;

	//cout<<"rot: "<<rot<<endl;
}
