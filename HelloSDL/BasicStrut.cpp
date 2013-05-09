//
//  BasicStrut.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/29/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "BasicStrut.h"
#include "Model.h"
#include "math.h"
#include "ModelConstants.h"
#include "BasicGun.h"

BasicStrut::BasicStrut(GameObject *p, Model *m) : GameObject() {
	model=m;
	modelSize=m->length;
	initAttachPoints();
	
	parent=p;
}

void BasicStrut::afterSetup() {
	GameObject::afterSetup();
	
	cout<<"rot: "<<rot<<endl;
	
	
	//for(int i=0;i<model->numAttachPoints;i++) {
	/*addChild(new BasicGun(this),0);
	//addChild(new BasicGun(this),1);
	addChild(new BasicGun(this),2);
	addChild(new BasicGun(this),3);
	addChild(new BasicGun(this),4);*/
	//}
}

void BasicStrut::initAttachPoints() {
	if(model->numAttachPoints==0) {
		int numAttachPoints=0;
		for(int i=0;i<model->length/model->verticesPerFace();i++) {
			//cout<<"normal: "<<model->normals[i]<<endl;
			/*Vec3d checkFlip=vertices[i];
			 for (int j=1; j<verticesPerFace(); j++) {
			 checkFlip+=vertices[i+j];
			 }*/
			
			// Need to find a good way to decide?
			
			//if(model->normals[i][2]>=0) {
				numAttachPoints++;
			//}
		}
		model->numAttachPoints=numAttachPoints;
		
		Vec3d center;
		for (int i=0; i<model->length/model->verticesPerFace();i++) {
			
			//if(model->normals[i][2]>=0) {
				center=Vec3d(0,0,0);
				for(int j=0;j<model->verticesPerFace();j++) {
					//cout<<"vertex: "<<model->vertices[i*model->verticesPerFace()+j]<<endl;
					center+=model->vertices[i*model->verticesPerFace()+j];
				}
				center/=model->verticesPerFace();
				
				model->addAttachPoint(center);
				model->addAttachPointAngle(invGetVector(model->normals[i]));
			//}
		}
	}
}

ObjectTypeTree* basicStrutTreeFun(double diff, double size) {
	ObjectTypeTree *tree=new ObjectTypeTree;
	
	unsigned int randomNum=rand();
	
	//models store an average distance, subtract it from size
	
	tree->numChildren=playerShipModel->numAttachPoints;
	tree->seed=randomNum;
	tree->type=basicStrutType;
	
	for(int i=0;i<playerShipModel->numAttachPoints/2;i++) {		//add random models later
		
		double subSize=((double)rand())/RAND_MAX*size;
		
		
		
		if(size-subSize>10) {
			double subDiff=((double)rand())/RAND_MAX*diff;
			if(i==playerShipModel->numAttachPoints/2-1)
				subDiff=diff;
			
			ObjectType obj=getRandomObject(objects, subDiff, subSize);
			int j = 0;
			while(j<10 && abs(subDiff-obj.difficulty(subSize))<10) {
				obj=getRandomObject(objects, subDiff, subSize);
				j++;
			}
			
			if(j<10) {
				diff-=subDiff;
				size-=subSize;
				tree->children[i]=*obj.treeFun(subDiff,subSize);
				tree->filled[i]=true;
				
				tree->children[playerShipModel->numAttachPoints-i-1]=*getRandomObject(objects, subDiff, subSize).treeFun(subDiff, subSize);
				tree->filled[playerShipModel->numAttachPoints-i-1]=true;
			} else {
				cout<<"Nothing small enough!"<<endl;
			}
		}
	}
	
	return tree;
}

ObjectType basicStrutType;

GameObject* basicStrutGetGameObject(int seed) {
	srand(seed);
	
	Model *mod=(rand()%2==0) ? basicStrutModel : longStrutModel;
	
	BasicStrut *strut=new BasicStrut(NULL, mod);
	
	return strut;
	//create a random object
}

double basicStrutDifficulty(double size) {
	size-=basicStrutType.minSize;
	
	double accum=0;
	int ct=0;
	
	for(int i=0;i<objects.size();i++) {
		if(objects[i].minSize<=size) {
			accum+=objects[i].difficulty(size/playerShipModel->numAttachPoints);
			ct++;
		}
	}
	
	double attachPoints=(basicStrutModel->numAttachPoints+longStrutModel->numAttachPoints)/2;
	
	return accum/ct*playerShipModel->numAttachPoints;
}
