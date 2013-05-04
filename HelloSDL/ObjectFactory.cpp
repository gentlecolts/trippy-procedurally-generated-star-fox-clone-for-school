//
//  ObjectFactory.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/3/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "ObjectFactory.h"

vector<ObjectType> objects, weapons, attachments, enemies, bombs;

void registerObjectType(ObjectCategory type, ObjectTypeTree *(*treeFun)(double, double), double (*difficulty)(double), GameObject *(*gameObject)(int seed)) {
	ObjectType objType;
	objType.difficulty=difficulty;
	objType.treeFun=treeFun;
	objType.type=type;
	
	objects.push_back(objType);
	
	switch (type) {
		case WEAPON:
			weapons.push_back(objType);
			break;
		case ATTACHMENT:
			attachments.push_back(objType);
			break;
		case ENEMY:
			enemies.push_back(objType);
			break;
		case BOMB:
			bombs.push_back(objType);
			break;
		default:
			break;
	}
}

GameObject *expandTree(ObjectTypeTree tree) {
	GameObject *obj=objects[tree.type].gameObject(tree.seed);
	
	for(int i=0;i<tree.numChildren;i++) {
		if(tree.filled[i]) {
			obj->addChild(expandTree(tree.children[i]), -1);		//doesn't take into account rotations... Hm...
		}
	}
	return obj;
}

ObjectTypeTree *getTree(double diff, double size) {
	ObjectType enemy=getRandomObject(enemies, diff, size);
	
	return enemy.treeFun(diff, size);
}

ObjectType getRandomObject(vector<ObjectType> v, double diff, double size) {
	double probabilities[enemies.size()];
	double total=0;
	
	for(int i=0;i<v.size();i++) {
		probabilities[i]=1/((v[i].difficulty)(size)-diff);
		total+=probabilities[i];
	}
	
	double randnum=(double)(rand())/RAND_MAX*total;
	
	for(int i=0;i<v.size();i++) {
		if(randnum>probabilities[i]) {
			randnum-=probabilities[i];
		} else {
			return v[i];
		}
	}
	
	cout<<"????"<<endl;
	
	return v[0];
}






















