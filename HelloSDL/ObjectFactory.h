//
//  ObjectFactory.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/3/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__ObjectFactory__
#define __HelloSDL__ObjectFactory__

#include <iostream>
#include <cmath>
#include "GameObject.h"

typedef enum {
	WEAPON=0,
	ATTACHMENT=1,
	ENEMY=2,
	BOMB=3
} ObjectCategory;

struct ObjectTypeTree;

struct ObjectType {
	ObjectCategory type;
	double minSize;
	double diff;			//have maxdiff too, check (1/(1+dist)) for prob
	int numAttachPointsEst;
	int maxChildren;
	
	string title;
	
//	GameObject *(*gameObject)(GameObject *parent, int seed, double diff, double size);
	GameObject *(*gameObject)(GameObject *parent, int seed);
	Model *(*model)();
	vector<ObjectType *>* (*candidateChildren)();
};

struct ObjectTypeTree {
	ObjectType *type;
	
	int seed;
	double diff;
	double size;
	
	ObjectTypeTree** children;
	bool *filled;
	int numChildren=0;
};

extern vector<ObjectType *> *objects, *weapons, *attachments, *enemies, *bombs;

ObjectType *typeForName(string name);
void registerObjectType(ObjectType *objType);
GameObject *expandTree(GameObject *parent, ObjectTypeTree* tree);
ObjectTypeTree *getTree(double diff, double size);
ObjectType *getRandomObject(vector<ObjectType *>* v, double diff, double size);
ObjectTypeTree* treeFun(ObjectType *type, double diff, double size);
double difficulty(ObjectType *type, double size);


#endif /* defined(__HelloSDL__ObjectFactory__) */
