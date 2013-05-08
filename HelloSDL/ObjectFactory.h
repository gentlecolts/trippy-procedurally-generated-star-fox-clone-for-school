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
	
	ObjectTypeTree *(*treeFun)(double, double);
	GameObject *(*gameObject)(int seed);
	double (*difficulty)(double);
};

struct ObjectTypeTree {
	ObjectType type;
	
	int seed;
	
	ObjectTypeTree* children;
	bool *filled;
	int numChildren;
};

extern vector<ObjectType> objects, weapons, attachments, enemies, bombs;

ObjectType registerObjectType(ObjectCategory type, ObjectTypeTree *(*treeFun)(double, double), double (*difficulty)(double), GameObject *(*gameObject)(int seed), double minSize);
GameObject *expandTree(ObjectTypeTree tree);
ObjectTypeTree *getTree(double diff, double size);
ObjectType getRandomObject(vector<ObjectType> v, double diff, double size);


#endif /* defined(__HelloSDL__ObjectFactory__) */
