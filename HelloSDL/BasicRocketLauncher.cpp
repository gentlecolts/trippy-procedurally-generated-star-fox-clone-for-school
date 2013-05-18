//
//  BasicRocketLauncher.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "BasicRocketLauncher.h"
#include "Nade.h"
#include "gameController.h"
#include "ModelConstants.h"
#include "Model.h"
#include "SlideDownAnimation.h"

BasicRocketLauncher::BasicRocketLauncher(GameObject *obj) : BasicGun(obj){
	init();
	bigGun=true;
	health=3;
}

void BasicRocketLauncher::init() {
	model=rocketLauncherModel;
	modelSize=rocketLauncherModel->length;
	
	fireRate=1;
	
	addChild(new Grenade(), 0);
//	cout<<"launcher player: "<<player<<" ammo: "<<children[0]->player<<endl;
	children[0]->parent=this;
	addChild(new Grenade(), 1);
	children[1]->parent=this;
	addChild(new Grenade(), 2);
	children[2]->parent=this;
	addChild(new Grenade(), 3);
	children[3]->parent=this;
}

void BasicRocketLauncher::doDoFire() {
	if(numChildren>0) {
		for(int i=0;i<model->numAttachPoints;i++) {
			if(attachPointsFilled[i]) {
				children[i]->setAnimation(new SlideDownAnimation(children[i], this, 0.3, 0.2, fireCallback));
				return;
			}
		}
	}
}


void BasicRocketLauncher::fireRocket(Grenade *g) {
	Vec3d pos=absolutePosition();
	
	Vec3d ang=absoluteAngle();
	
	g->init(pos, ang, Vec3d(0,0,0), 5, 5);
	g->parent=NULL;
	g->activate();
	g->setAnimation(NULL);
	
	for(int i=0;i<model->numAttachPoints;i++) {
//		cout<<"children: "<<children[i]<<"g: "<<g<<endl;
//		cout<<"equal: "<<(children[i]==g)<<endl;
		if(children[i]==g) {
			children[i]=NULL;
			attachPointsFilled[i]=false;
			numChildren--;
		}
	}
	
	addLaser(g, player);
}

void fireCallback(GameObject *me, GameObject *o) {
//	cout<<"callback!"<<endl;
	((BasicRocketLauncher *)me)->fireRocket((Grenade *)o);
}