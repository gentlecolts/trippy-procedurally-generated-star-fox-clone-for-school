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

vector<ObjectType>* objects, *weapons, *attachments, *enemies, *bombs;

ObjectType registerObjectType(ObjectType objType) {
	ObjectCategory type=objType.type;
	
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
	
	return objType;
}

GameObject *expandTree(GameObject *parent, ObjectTypeTree *tree) {
	
	GameObject *obj=tree->type.gameObject(parent, tree->seed);
	
	cout<<"type: "<<tree->type.title<<endl;
	cout<<"model size: "<<obj->model->length<<endl;
	cout<<"attach points: "<<obj->model->numAttachPoints<<endl;
	cout<<"object: "<<obj<<endl;
	cout<<"num children: "<<tree->numChildren<<endl;
//	cout<<"obj: "<<obj<<endl;
	
	for(int i=0;i<tree->numChildren;i++) {
		if(tree->filled[i]) {
			GameObject* childObj=expandTree(obj, &tree->children[i]);
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
	ObjectType enemy=getRandomObject(enemies, diff, size);
	
//	cout<<"enemy: "<<enemy.diff<<endl;
	
	return treeFun(enemy, diff, size);
}


ObjectType getRandomObject(vector<ObjectType> *v, double diff, double size) {
	double probabilities[enemies->size()];
	double total=0;
	
	for(int i=0;i<v->size();i++) {
		probabilities[i]=abs(1/(v->at(i).diff-diff));
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
	
	cout<<"????"<<endl;
	
	return v->at(0);
}

ObjectTypeTree* treeFun(ObjectType type, double diff, double size) {
	ObjectTypeTree *tree=new ObjectTypeTree;
	
	unsigned int randomNum=rand();
	srand(randomNum);
	
	size-=type.minSize;
	
	
	Model *mod=type.model();
	
	diff-=type.diff;
	
	tree->numChildren=mod->numAttachPoints;
	tree->seed=randomNum;
	tree->type=type;
	
	tree->filled=new bool[mod->numAttachPoints];
	tree->children=new ObjectTypeTree[mod->numAttachPoints];
	
	//Need to get the objects for each attach point from the thingy
	
	for(int i=0;i<mod->numAttachPoints/2;i++) {		//add random models later
		
		double subSize=((double)rand())/RAND_MAX*size;
		
		if(size-subSize>0) {
			double subDiff=((double)rand())/RAND_MAX*diff;
			if(i==mod->numAttachPoints/2-1)
				subDiff=diff;
			
			vector<ObjectType>* cand=type.candidateChildren();
			
			ObjectType obj=getRandomObject(cand, subDiff, subSize);
			int j = 0;
			while(j<10 && abs(subDiff-difficulty(obj,subSize))<10) {
				obj=getRandomObject(cand, subDiff, subSize);
				j++;
			}
			
			if(j<10) {			//fix this somehow
				diff-=subDiff;
				size-=subSize;
				tree->children[i]=*treeFun(obj,subDiff,subSize);
				tree->filled[i]=true;
				
				tree->children[mod->numAttachPoints-i-1]=*treeFun(obj,subDiff, subSize);
				tree->filled[mod->numAttachPoints-i-1]=true;
			} else {
				cout<<"Nothing small enough!"<<endl;
			}
		}
	}
	
	return tree;
}

double difficulty(ObjectType type, double size) {
	size-=type.minSize;
	
	/*cout<<"size: "<<size<<endl;
	cout<<"minSize: "<<type.minSize<<endl;
	cout<<"num...est: "<<type.numAttachPointsEst<<endl;*/
	
	double accum=0;
	int ct=0;
	
	for(int i=0;i<objects->size();i++) {
		if(objects->at(i).minSize<=size/type.numAttachPointsEst) {
			accum+=difficulty(objects->at(i),size/type.numAttachPointsEst);
			ct++;
		}
	}
	
	return accum/ct*type.numAttachPointsEst+type.diff;
}


















