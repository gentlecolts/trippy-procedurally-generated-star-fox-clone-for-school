//
//  FanStrutThing.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/30/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "FanStrutThing.h"
#include "../Model.h"
#include "BasicGun.h"
#include "../ModelConstants.h"
#include "RotateStrut.h"

//This was for testing that everything worked mathematically, and isn't actually in the game

/**
 void FanStrut::afterSetup()
 Creates a FanStrutThing and its wings, creates another one with 1 less parameter as its child to create the wing shape
 */
void FanStrut::afterSetup() {
	BasicStrut::afterSetup();

	for(int num=0;num<=1;num++) {
		GameObject *child=this;
		for(int i=0;i<level;i++) {
			BasicStrut *spar=new RotateStrut(child,longStrutModel, Vec3d(30,0,0),Vec3d(-30,0,0), 0.5);
			if(i>0)
				child->addChild(spar, 1);
			else
				child->addChild(spar, num+4, Vec3d(0, 0, num ? 180 : 0));
			GameObject *next=new BasicStrut(spar, basicStrutModel);
			spar->addChild(next, 1);

			next->addChild(new BasicGun(next), 5-num);
			child=next;


		}
	}

	if(level>0) {
		BasicStrut *childBasicStrut=new RotateStrut(this, longStrutModel, Vec3d(0,-30,0),Vec3d(0,30,0),1.0);
		addChild(childBasicStrut, 3);

		FanStrut *childFanStrut=new FanStrut(childBasicStrut, level-1, model);
		childBasicStrut->addChild(childFanStrut, 1, Vec3d(0,90,0));
		BasicGun *gun=new BasicGun(childFanStrut);
		childFanStrut->addChild(gun, 1);

	}
}

/**
 FanStrut::FanStrut(GameObject *p, int l, Model *m)
 Sets level
 */
FanStrut::FanStrut(GameObject *p, int l, Model *m) : BasicStrut(p, m) {
	level=l;
}
