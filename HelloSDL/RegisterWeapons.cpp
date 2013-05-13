//
//  RegisterWeapons.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/13/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "RegisterWeapons.h"
#include "ModelConstants.h"
#include "BasicGun.h"

void registerBasicGunType() {
	ObjectType basicGunType;
	
	basicGunType.type=ATTACHMENT;
	basicGunType.candidateChildren=basicGunCandidateChildren;
	basicGunType.diff=5;
	basicGunType.gameObject=basicGunGetGameObject;
	basicGunType.minSize=0.3;
	basicGunType.model=basicGunGetModel;
	basicGunType.numAttachPointsEst=0;		//CHANGE THIS WHEN MORE MODELS ADDED
	basicGunType.title="basicGun";
	
	registerObjectType(basicGunType);
}

vector<ObjectType>* basicGunCandidateChildren() {
	return objects;
}

Model *basicGunGetModel() {
	return basicGunModel;
}

GameObject* basicGunGetGameObject(GameObject *parent, int seed) {
	srand(seed);
	
	BasicGun *gun=new BasicGun(parent);
	
	return gun;
	//create a random object
}
