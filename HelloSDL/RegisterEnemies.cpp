//
//  RegisterEnemies.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/11/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "RegisterEnemies.h"
#include "HoverShip.h"
#include "ModelConstants.h"
#include "Model.h"
#include "RamShip.h"

void registerHoverShipType() {
	ObjectType hoverShipType;
	
	hoverShipType.type=ENEMY;
	hoverShipType.candidateChildren=hoverShipCandidateChildren;
	hoverShipType.diff=10;
	hoverShipType.gameObject=hoverShipGetGameObject;
	hoverShipType.minSize=1;
	hoverShipType.model=hoverShipGetModel;
	hoverShipType.numAttachPointsEst=playerShipModel->numAttachPoints;
	cout<<"numAttach..: "<<playerShipModel->numAttachPoints<<endl;
	
	registerObjectType(hoverShipType);
}

vector<ObjectType> hoverShipCandidateChildren() {
	return objects;
}

Model *hoverShipGetModel() {
	return playerShipModel;
}

GameObject* hoverShipGetGameObject(GameObject *parent, int seed) {
	//srand(seed);
	
	HoverShip *ship=new HoverShip();
	
	return ship;
	//create a random object
}


void registerRamShipType() {
	ObjectType ramShipType;
	
	ramShipType.type=ENEMY;
	ramShipType.candidateChildren=ramShipCandidateChildren;
	ramShipType.diff=5;
	ramShipType.gameObject=ramShipGetGameObject;
	ramShipType.minSize=1;
	ramShipType.model=ramShipGetModel;
	ramShipType.numAttachPointsEst=ramShipModel->numAttachPoints;
	
	registerObjectType(ramShipType);
}

vector<ObjectType> ramShipCandidateChildren() {
	return objects;
}

Model *ramShipGetModel() {
	return ramShipModel;
}

GameObject* ramShipGetGameObject(GameObject *parent, int seed) {
	//srand(seed);
	
	RamShip *ship=new RamShip();
	
	return ship;
	//create a random object
}