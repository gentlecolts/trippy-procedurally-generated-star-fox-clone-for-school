//
//  ObjectFactory.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/3/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "ObjectFactory.h"
#include "../Model.h"

#include "RegisterEnemies.h"

//TODO: add scaling difficulty on objects - range?

vector<ObjectType *>* objects, *weapons, *attachments, *enemies, *bombs;

/**
 void registerObjectType(ObjectType *objType)
 Takes an object type and puts it in the appropriate vectors. objects stores everything but ships, and everything is also filed into the individual categories. Bombs isn't used, but will be later since the rocket launchers are set up to fire whatever ammo is attached to them as a child object
 */
void registerObjectType(ObjectType *objType) {
	ObjectCategory type=objType->type;

	if(type!=ENEMY)
		objects->push_back(objType);

	switch (type) {
		case WEAPON:
			weapons->push_back(objType);
			break;
		case ATTACHMENT:
			attachments->push_back(objType);
			break;
		case ENEMY:
			enemies->push_back(objType);
			break;
		case BOMB:
			bombs->push_back(objType);
			break;
		default:
			break;
	}
}

/**
 GameObject *expandTree(GameObject *parent, ObjectTypeTree *tree)
 Turns an ObjectTypeTree (essentially a recipe for a tree of GameObjects) into an actual gameObject. This is used so that things such as symmetry or parts having specific types of children always added can be done easily. It takes a parent because objects need to know their parent in order to compute their position and angle.
 */
GameObject *expandTree(GameObject *parent, ObjectTypeTree *tree) {
	GameObject *obj=tree->type->gameObject(parent, tree->seed);

	for(int i=0;i<tree->numChildren;i++) {
		if(tree->filled[i]) {
			GameObject* childObj=expandTree(obj, tree->children[i]);
			obj->addChild(childObj, i);		//doesn't take into account rotations... Hm...
		}
	}
	
	return obj;
}

/**
 ObjectTypeTree* getTree(double diff, double size)
 Returns a ObjectTypeTree of a random enemy with difficulty diff and size size
 */
ObjectTypeTree* getTree(double diff, double size) {
	ObjectType *enemy=getRandomObject(enemies, diff, size);

	return treeFun(enemy, diff, size);
}

/**
 ObjectType *getRandomObject(vector<ObjectType *> *v, double diff, double size)
 Selects a random object from v weighted by the estimated difficulty and size as compared to the target
 */
ObjectType *getRandomObject(vector<ObjectType *> *v, double diff, double size) {
	double probabilities[v->size()];
	double total=0;

	for(int i=0;i<v->size();i++) {
		probabilities[i]=abs(1/((maxSize(v->at(i), diff, size)-size)+(difficulty(v->at(i), diff, size)-diff)));
		total+=probabilities[i];
	}
	
	double randnum=(double)(rand())/RAND_MAX*total;

	for(int i=0;i<v->size();i++) {
		if(randnum>probabilities[i]) {
			randnum-=probabilities[i];
		} else {
			return v->at(i);
		}
	}
	
	
	return v->at(0);
}

/**
 ObjectType *typeForName(string name)
 Gets the object with name name. This is purely for convenience and is inefficient, but it decreases coding time.
 */
ObjectType *typeForName(string name) {
	for (int i=0; i<enemies->size(); i++) {
		if(name==enemies->at(i)->title)
			return enemies->at(i);
	}

	for (int i=0; i<objects->size(); i++) {
		if(name==objects->at(i)->title)
			return objects->at(i);
	}

	return NULL;
}

/**
 ObjectTypeTree* treeFun(ObjectType *type, double diff, double size)
 Gets an ObjectTypeTree recursively with target difficulty diff and target size size
 */
ObjectTypeTree* treeFun(ObjectType *type, double diff, double size) {
	ObjectTypeTree *tree=new ObjectTypeTree;

	unsigned int randomNum=rand();
	srand(randomNum);

	size-=type->minSize;


	Model *mod=type->model();

	diff-=type->diff;

	tree->numChildren=mod->numAttachPoints;
	tree->seed=randomNum;
	tree->type=type;

	tree->filled=new bool[mod->numAttachPoints];
	tree->children=new ObjectTypeTree*[mod->numAttachPoints];

	int childrenCt=type->maxChildren/2;
	if(type->maxChildren==-1)
		childrenCt=mod->numAttachPoints/2;

	//Need to get the objects for each attach point from the thingy

	for(int i=0;i<childrenCt;i++) {		//add random models later

		double subSize=((double)rand())/RAND_MAX*size;

		if(size>0.1 && diff>0.1) {
			double subDiff=((double)rand())/RAND_MAX*diff;
			if(i==childrenCt-1)
				subDiff=diff;

			vector<ObjectType *>* cand=type->candidateChildren();

			ObjectType *obj=getRandomObject(cand, subDiff, subSize);
			
			obj=getRandomObject(cand, subDiff, subSize);
		
			diff-=subDiff;
			size-=subSize;
			tree->children[i]=treeFun(obj,subDiff,subSize);
			tree->filled[i]=true;

			tree->children[mod->numAttachPoints-i-1]=tree->children[i];
			tree->filled[mod->numAttachPoints-i-1]=true;
		} else {
			tree->filled[i]=false;
			tree->filled[mod->numAttachPoints-i-1]=false;
		}
	}

	tree->diff=diff+type->diff;
	tree->size=size+type->minSize;

	return tree;
}

/**
 double difficulty(ObjectType *type, double diff, double size)
 Estimates the maximum difficulty this object and its children could add with maximum difficulty diff and maximum size size
 */
double difficulty(ObjectType *type, double diff, double size) {
	if(type->numAttachPointsEst>0) {
		size-=type->minSize;
		diff-=type->diff;

		double accum=0;
		int ct=0;

		vector<ObjectType *>* children=type->candidateChildren();

		for(int i=0;i<children->size();i++) {
			if(children->at(i)->minSize<=size/type->maxChildren && children->at(i)->diff<=diff/type->maxChildren) {
				accum+=difficulty(children->at(i), diff/type->maxChildren,size/type->maxChildren);
				ct++;
			}
		}

		if(accum!=0)
			return accum/ct*type->maxChildren+type->diff;
		return type->diff;
	}
	return type->diff;
}

/**
 double maxSize(ObjectType *type, double diff, double size)
 Estimates the maximum size of an object could be with target difficulty diff and target size size
 */
double maxSize(ObjectType *type, double diff, double size) {
	if(type->numAttachPointsEst>0) {
		size-=type->minSize;
		diff-=type->diff;

		double accum=0;
		int ct=0;

		vector<ObjectType *>* children=type->candidateChildren();

		for(int i=0;i<children->size();i++) {
			if(children->at(i)->minSize<=size/type->maxChildren && children->at(i)->diff<=diff/type->maxChildren) {
				accum+=maxSize(children->at(i), diff/type->maxChildren,size/type->maxChildren);
				ct++;
			}
		}

		if(accum!=0)
			return accum/ct*type->maxChildren+type->minSize;
		return type->minSize;
	}
	return type->minSize;
}
