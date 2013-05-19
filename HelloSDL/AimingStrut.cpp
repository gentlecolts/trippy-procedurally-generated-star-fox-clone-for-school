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

AimingStrut::AimingStrut() : BasicStrut() {
}

AimingStrut::AimingStrut(GameObject *p, double s, Model *m) : BasicStrut() {
	init(p, s, m);
}

void AimingStrut::init(GameObject *p, double s, Model *m) {
	BasicStrut::init(p, m);

	speed=s;
}

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

//	dist=Vec3d(0,1,0);
	//cout<<"dist: "<<dist<<endl;
	//dist[2]*=-1;


	//dist[2]=-dist[2];

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

void AimingStrut::afterSetup() {

}
