//
//  RegisterEnemies->cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/11/13->
//  Copyright (c) 2013 Student-> All rights reserved->
//

#include "RegisterEnemies.h"
#include "HoverShip.h"
#include "../ModelConstants.h"
#include "../Model.h"
#include "../RamShip.h"
#include "TrackingShip.h"

/**
 void registerHoverShipType()
 Registers HoverShip with the factory
 */
void registerHoverShipType() {
	ObjectType* hoverShipType = new ObjectType;

	hoverShipType->type=ENEMY;
	hoverShipType->candidateChildren=hoverShipCandidateChildren;
	hoverShipType->diff=10;
	hoverShipType->gameObject=hoverShipGetGameObject;
	hoverShipType->minSize=1;
	hoverShipType->model=hoverShipGetModel;
	hoverShipType->numAttachPointsEst=ramShipModel->numAttachPoints;
	hoverShipType->maxChildren=-1;
	hoverShipType->title="hoverShip";
//	cout<<"numAttach->->: "<<playerShipModel->numAttachPoints<<endl;
	registerObjectType(hoverShipType);
}

/**
 vector<ObjectType *>* hoverShipCandidateChildren()
 Gets the objects that could be children of a hoverShip; this is passed in a as a function pointer.
 */
vector<ObjectType *>* hoverShipCandidateChildren() {
	return objects;
}

/**
 Model *hoverShipGetModel()
 Gets a hoverShip's model
 */
Model *hoverShipGetModel() {
	return ramShipModel;
}

//gets a HoverShip object
GameObject* hoverShipGetGameObject(GameObject *parent, int seed) {

	HoverShip *ship=new HoverShip(hoverShipGetModel());

	return ship;
	//create a random object
}

//registers RamShip with the factory
void registerRamShipType() {
	ObjectType* ramShipType = new ObjectType;

	ramShipType->type=ENEMY;
	ramShipType->candidateChildren=ramShipCandidateChildren;
	ramShipType->diff=5;
	ramShipType->gameObject=ramShipGetGameObject;
	ramShipType->minSize=1;
	ramShipType->model=ramShipGetModel;
	ramShipType->numAttachPointsEst=playerShipModel->numAttachPoints;
	ramShipType->maxChildren=-1;
	ramShipType->title="ramShip";

	registerObjectType(ramShipType);
}

//and so forth
vector<ObjectType *>* ramShipCandidateChildren() {
	return objects;
}

Model *ramShipGetModel() {
	return playerShipModel;
}

GameObject* ramShipGetGameObject(GameObject *parent, int seed) {
	//srand(seed);

	RamShip *ship=new RamShip(ramShipGetModel());

	return ship;
	//create a random object
}



void registerTrackingShipType() {
	ObjectType* trackingShipType= new ObjectType;

	trackingShipType->type=ENEMY;
	trackingShipType->candidateChildren=trackingShipCandidateChildren;
	trackingShipType->diff=7;
	trackingShipType->gameObject=trackingShipGetGameObject;
	trackingShipType->minSize=1;
	trackingShipType->model=trackingShipGetModel;
	trackingShipType->numAttachPointsEst=playerShipModel->numAttachPoints;
	trackingShipType->maxChildren=-1;
	trackingShipType->title="trackingShip";

	registerObjectType(trackingShipType);
}

vector<ObjectType *>* trackingShipCandidateChildren() {
	return objects;
}

Model *trackingShipGetModel() {
//	cout<<"trackingShipShtegMoel?!"<<endl;
	return playerShipModel;
}

GameObject* trackingShipGetGameObject(GameObject *parent, int seed) {
	//srand(seed);

	TrackingShip *ship=new TrackingShip(trackingShipGetModel());

	return ship;
	//create a random object
}
