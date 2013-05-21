//
//  BasicStrut.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/29/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "BasicStrut.h"
#include "../Model.h"
#include "../math.h"
#include "../ModelConstants.h"
#include "BasicGun.h"

/**
 BasicStrut::BasicStrut()
 Sets the health
 */
BasicStrut::BasicStrut() : GameObject() {
	health=2;
}

/**
 BasicStrut::BasicStrut(GameObject *p, Model *m)
 Sets the health
 */
BasicStrut::BasicStrut(GameObject *p, Model *m) : GameObject() {
	init(p,m);
	health=2;
}

/**
 void BasicStrut::init(GameObject *p, Model *m)
 Sets the model and generates attach points
 */
void BasicStrut::init(GameObject *p, Model *m) {
	model=m;
	modelSize=m->length;
	initAttachPoints();

	parent=p;
}

/**
 void BasicStrut::initAttachPoints()
 Takes a model and calculates points to attach children. This was so we could generate other models for the basic struts such as polygonal pyramids (for creating shotgun-esque spreads)
 */
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

