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

struct ObjectTypeTree {
	uint16_t type;
	
	int seed;
	
	ObjectTypeTree* children;
	bool *filled;
	int numChildren;
};

struct ObjectType {
	ObjectCategory type;
	
	ObjectTypeTree *(*treeFun)(double, double);
	GameObject *(*gameObject)(int seed);
	double (*difficulty)(double);
};

extern vector<ObjectType> objects, weapons, attachments, enemies, bombs;

void registerObjectType(ObjectCategory type, ObjectTypeTree *(*treeFun)(double, double), double (*difficulty)(double), GameObject *(*gameObject)(int seed));
GameObject *expandTree(ObjectTypeTree tree);
ObjectTypeTree *getTree(double diff, double size);
ObjectType getRandomObject(vector<ObjectType> v, double diff, double size);


#endif /* defined(__HelloSDL__ObjectFactory__) */
