//
//  AimingStrut.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/3/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "AimingStrut.h"
#include "globals.h"
#include "gameShip.h"

AimingStrut::AimingStrut(GameObject *p, double s, Model *m) : BasicStrut(p, m) {
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
	
	targetPoint=target->pos;
	
	Vec3d dist=pos-targetPoint;
	
	Vec3d angles=invGetVector(dist);
	angles-=absoluteAngle();
	
	//cout<<"dist: "<<dist<<endl;
	//cout<<"angles: "<<angles<<endl;
	
	/*angles[0]=min(angles[0],speed)*dt;
	angles[1]=min(angles[1],speed)*dt;
	angles[2]=min(angles[2],speed)*dt;
	
	cout<<"angles: "<<angles<<endl;*/
	
	rot=angles;
	
	//cout<<"rot: "<<rot<<endl;
}

void AimingStrut::afterSetup() {
	
}