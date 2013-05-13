//
//  RegisterStruts.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/11/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "RegisterStruts.h"
#include "BasicStrut.h"
#include "ModelConstants.h"
#include "Model.h"
#include "AimingStrut.h"
#include "RotateStrut.h"

void registerBasicStrutType() {
	ObjectType basicStrutType;
	
	basicStrutType.type=ATTACHMENT;
	basicStrutType.candidateChildren=basicStrutCandidateChildren;
	basicStrutType.diff=0;
	basicStrutType.gameObject=basicStrutGetGameObject;
	basicStrutType.minSize=0.3;
	basicStrutType.model=basicStrutGetModel;
	basicStrutType.numAttachPointsEst=6;		//CHANGE THIS WHEN MORE MODELS ADDED
	basicStrutType.title="basicStrut";
	
	registerObjectType(basicStrutType);
}

vector<ObjectType>* basicStrutCandidateChildren() {
	return objects;
}

Model *basicStrutGetModel() {
	if(rand()%2==0)
		return basicStrutModel;
	return longStrutModel;
}

GameObject* basicStrutGetGameObject(GameObject *parent, int seed) {
	srand(seed);
	
	BasicStrut *ship=new BasicStrut();
	
	ship->init(parent, basicStrutGetModel());
	
	return ship;
	//create a random object
}


#define aimingStrutDiff 4

void registerAimingStrutType() {
	ObjectType aimingStrutType;
	
	aimingStrutType.type=ATTACHMENT;
	aimingStrutType.candidateChildren=aimingStrutCandidateChildren;
	aimingStrutType.diff=aimingStrutDiff;
	aimingStrutType.gameObject=aimingStrutGetGameObject;
	aimingStrutType.minSize=0.3;
	aimingStrutType.model=aimingStrutGetModel;
	aimingStrutType.numAttachPointsEst=6;
	aimingStrutType.title="aimingStrut";
	
	registerObjectType(aimingStrutType);
}

vector<ObjectType>* aimingStrutCandidateChildren() {
	return objects;
}

Model *aimingStrutGetModel() {
	if(rand()%2==0)
		return basicStrutModel;
	return longStrutModel;
}

GameObject* aimingStrutGetGameObject(GameObject *parent, int seed) {
	//srand(seed);
	
	AimingStrut *ship=new AimingStrut();
	//need to get a difficulty from somewhere
	
	Model *m=aimingStrutGetModel();
	
	ship->init(parent, rand()%90, m);
	
	return ship;
	//create a random object
}



void registerRotateStrutType() {
	ObjectType rotateStrutType;
	
	rotateStrutType.type=ATTACHMENT;
	rotateStrutType.candidateChildren=rotateStrutCandidateChildren;
	rotateStrutType.diff=1;
	rotateStrutType.gameObject=rotateStrutGetGameObject;
	rotateStrutType.minSize=0.3;
	rotateStrutType.model=rotateStrutGetModel;
	rotateStrutType.numAttachPointsEst=6;
	rotateStrutType.title="rotateStrut";
	
	registerObjectType(rotateStrutType);
}

vector<ObjectType>* rotateStrutCandidateChildren() {
	return objects;
}

Model *rotateStrutGetModel() {
	if(rand()%2==0)
		return basicStrutModel;
	return longStrutModel;
}

GameObject* rotateStrutGetGameObject(GameObject *parent, int seed) {
	//srand(seed);
	
	RotateStrut *ship=new RotateStrut();
	
	Model *m=rotateStrutGetModel();
	
	Vec3d s=Vec3d(rand()%90-45,rand()%90-45,rand()%90-45);
	
	ship->init(parent, m, s, -s, ((double)rand())/RAND_MAX*5);
	
	return ship;
	//create a random object
}