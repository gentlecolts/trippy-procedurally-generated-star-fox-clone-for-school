//
//  ObjectFactory.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/3/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "ObjectFactory.h"
#include "Model.h"

#include "RegisterEnemies.h"

//TODO: add scaling difficulty on objects - range?

vector<ObjectType *>* objects, *weapons, *attachments, *enemies, *bombs;

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

GameObject *expandTree(GameObject *parent, ObjectTypeTree *tree) {
	
//	GameObject *obj=tree->type->gameObject(parent, tree->seed, tree->diff, tree->size);
	GameObject *obj=tree->type->gameObject(parent, tree->seed);
	
	cout<<"type: "<<tree->type->title<<endl;
	cout<<"model size: "<<obj->model->length<<endl;
	cout<<"attach points: "<<obj->model->numAttachPoints<<endl;
	cout<<"object: "<<obj<<endl;
	cout<<"num children: "<<tree->numChildren<<endl;
//	cout<<"obj: "<<obj<<endl;
	
	for(int i=0;i<tree->numChildren;i++) {
		if(tree->filled[i]) {
			GameObject* childObj=expandTree(obj, tree->children[i]);
			cout<<"o: "<<obj<<endl;
			cout<<"i: "<<i<<endl;
			obj->addChild(childObj, i);		//doesn't take into account rotations... Hm...
		}
	}
	
	cout<<"obj: "<<obj<<endl;
	cout<<"real num children: "<<obj->numChildren<<endl;
	
	return obj;
}

ObjectTypeTree* getTree(double diff, double size) {		//maybe take enemy? vector of possible types?
	ObjectType *enemy=getRandomObject(enemies, diff, size);
	
//	cout<<"enemy: "<<enemy.diff<<endl;
	
	return treeFun(enemy, diff, size);
}


ObjectType *getRandomObject(vector<ObjectType *> *v, double diff, double size) {
	double probabilities[v->size()];
	double total=0;
	
	for(int i=0;i<v->size();i++) {
		probabilities[i]=abs(1/(difficulty(v->at(i), diff, size)-diff)+.001);
		total+=probabilities[i];
	}
	
	cout<<"difficulty: "<<diff<<" size: "<<size<<endl;
	for(int i=0;i<v->size();i++) {
		cout<<"\tobject: "<<v->at(i)->title<<" p="<<probabilities[i]<<" diff="<<difficulty(v->at(i), diff, size)<<endl;
	}
	
	cout<<"total: "<<total<<endl;
	
	double randnum=(double)(rand())/RAND_MAX*total;
	
	cout<<"randnum: "<<randnum<<endl;
	
	for(int i=0;i<v->size();i++) {
		if(randnum>probabilities[i]) {
			randnum-=probabilities[i];
		} else {
			cout<<"returned "<<v->at(i)->title<<endl;
			return v->at(i);
		}
	}
	
	cout<<"????"<<endl;
	
	return v->at(0);
}

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

int ct=0;

ObjectTypeTree* treeFun(ObjectType *type, double diff, double size) {
	ct++;
	cout<<"ct: "<<ct<<endl;
	
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
			//int j = 0;
//			while(j<10 && abs(subDiff-difficulty(obj,subSize))<0.1) {
//				cout<<"NOPE"<<endl;
				obj=getRandomObject(cand, subDiff, subSize);
//				j++;
//			}
			
//			if(j<10) {			//fix this somehow
				diff-=subDiff;
				size-=subSize;
				tree->children[i]=treeFun(obj,subDiff,subSize);
				tree->filled[i]=true;
				
				tree->children[mod->numAttachPoints-i-1]=tree->children[i];
				cout<<"set children["<<(mod->numAttachPoints-i-1)<<"] to: "<<tree->children[mod->numAttachPoints-i-1]<<endl;
				cout<<"should be ["<<i<<"]: "<<tree->children[i]<<endl;
				tree->filled[mod->numAttachPoints-i-1]=true;
			/*} else {
				cout<<"Nothing small enough! ["<<i<<"]"<<endl;
				cout<<"should be paired with ["<<mod->numAttachPoints-i-1<<"]"<<endl;
				tree->filled[i]=false;
				tree->filled[mod->numAttachPoints-i-1]=false;
			}*/
		} else {
			cout<<"=( ["<<i<<"]"<<endl;
			tree->filled[i]=false;
			tree->filled[mod->numAttachPoints-i-1]=false;
		}
	}
	
	tree->diff=diff+type->diff;
	tree->size=size+type->minSize;
	
	return tree;
}

double difficulty(ObjectType *type, double diff, double size) {
	if(type->numAttachPointsEst>0) {
		size-=type->minSize;
		
		/*cout<<"size: "<<size<<endl;
		cout<<"minSize: "<<type.minSize<<endl;
		cout<<"num...est: "<<type.numAttachPointsEst<<endl;*/
		
		double accum=0;
		int ct=0;
		
		vector<ObjectType *>* children=type->candidateChildren();
		
//		cout<<"size: "<<children->size()<<endl;
		
		for(int i=0;i<children->size();i++) {
			if(children->at(i)->minSize<=size/type->maxChildren && children->at(i)->diff<=diff/type->maxChildren) {
				accum+=difficulty(children->at(i), diff/type->maxChildren,size/type->maxChildren);
				ct++;
			} else {
//				cout<<"minsize: "<<children->at(i)->minSize<<endl;
			}
		}
		
		if(accum!=0)
			return accum/ct*type->maxChildren+type->diff;
		return type->diff;
	}
	return type->diff;
}


















