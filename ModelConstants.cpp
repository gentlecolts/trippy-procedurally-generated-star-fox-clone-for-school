//
//  ModelConstants.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/15/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "ModelConstants.h"
#include "Model.h"
#include "Vec3d.h"
#include "imageloader.h"
#include "constants.h"

Model *ramShipModel=new Model(24);
Model *playerShipModel=new Model(18);
Model *basicGunModel=new Model(24);
Model *basicStrutModel=new Model(24);
Model *longStrutModel=new Model(24);

GLuint laserTexture;


/**
 void initModels()
 Set up the constant models
 */
void initModels() {
	ramShipModel->addVertex(Vec3d(1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3d(1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, -1.0f, 0.0f));
	ramShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3d(1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 0.0f, -1.0f));
	ramShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3d(1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, -1.0f, 0.0f));
	ramShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 0.0f, -1.0f));
	ramShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3d(-1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3d(-1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, -1.0f, 0.0f));
	ramShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3d(-1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 0.0f, -1.0f));
	ramShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3d(-1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, -1.0f, 0.0f));
	ramShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3d(0.0f, 0.0f, -1.0f));
	ramShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	
	ramShipModel->computeNormals();
	
	ramShipModel->numAttachPoints=8;
	
	for(int i=-1;i<=1;i+=2) {
		for(int j=-1;j<=1;j+=2) {
			for(int k=-1;k<=1;k+=2) {
				ramShipModel->addAttachPoint(Vec3d(i*1.0/3,j*1.0/3,k*1.0/3));
				
				ramShipModel->addAttachPointAngle(Vec3d(-j*k*45,-i*(k+2)*45,0));
			}
		}
	}
	
	
	
	
	
	playerShipModel->addVertex(Vec3d(0.0f, 0.0f, -2.0f));
	playerShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	playerShipModel->addVertex(Vec3d(0.0f, 0.5f, 0.0f));
	playerShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3d(1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3d(0.0f, 0.0f, -2.0f));
	playerShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	playerShipModel->addVertex(Vec3d(0.0f, -0.3f, -0.0f));
	playerShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3d(1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3d(0.0f, 0.0f, -2.0f));
	playerShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	playerShipModel->addVertex(Vec3d(0.0f, 0.5f, -0.0f));
	playerShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3d(-1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3d(0.0f, 0.0f, -2.0f));
	playerShipModel->addColor(Vec3d(1.0f, 0.f, 0.0f));
	playerShipModel->addVertex(Vec3d(0.0f, -0.3f, -0.0f));
	playerShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3d(-1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3d(0.0f, 0.5f, -0.0f));
	playerShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3d(0.0f, -0.3f, -0.0f));
	playerShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3d(-1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3d(0.0f, 0.5f, 0.0f));
	playerShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3d(0.0f, -0.3f, 0.0f));
	playerShipModel->addColor(Vec3d(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3d(1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3d(0.0f, 0.0f, 1.0f));
	
	playerShipModel->computeNormals();
	
	playerShipModel->numAttachPoints=2;
	
	playerShipModel->addAttachPoint(Vec3d(0.5,0.0,0.0));
	playerShipModel->addAttachPoint(Vec3d(-0.5,0.0,0.0));
	
	playerShipModel->addAttachPointAngle(Vec3d(0,0,0.0));
	playerShipModel->addAttachPointAngle(Vec3d(0,0,180));
	
	
	
	
	
	basicGunModel->type=GL_QUADS;
	
	basicGunModel->addRectPrism(Vec3d(-0.1,-0.1,0.0), Vec3d(0.1,0.1,-1.0));
	
	for(int i=0;i<24;i++) {
		if(basicGunModel->vertices[i][2]>0)
			basicGunModel->addColor(Vec3d(0.0,1.0,1.0));
		else
			basicGunModel->addColor(Vec3d(0.0,0.0,1.0));
	}
	
	basicGunModel->computeNormals();
	
	
	
	
	basicStrutModel->type=GL_QUADS;
	
	basicStrutModel->addRectPrism(Vec3d(-0.2,-0.2,-0.2), Vec3d(0.2,0.2,0.2));
	
	for(int i=0;i<24;i++) {
		basicStrutModel->addColor(Vec3d(1.0,0.8,0.8));
	}
	
	basicStrutModel->computeNormals();
	
	
	
	longStrutModel->type=GL_QUADS;
	longStrutModel->addRectPrism(Vec3d(-0.1,-0.1,0), Vec3d(0.1,0.1,-1));
	for(int i=0;i<24;i++) {
		longStrutModel->addColor(Vec3d(0.7,0.7,0.7));
	}
	longStrutModel->computeNormals();
}


/**
 void unloadModels()
 Delete the constant models
 */
void unloadModels() {
	delete ramShipModel;
	delete playerShipModel;
}