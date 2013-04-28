//
//  ModelConstants.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/15/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "ModelConstants.h"
#include "Model.h"
#include "vec3f.h"
#include "imageloader.h"
#include "constants.h"

Model *ramShipModel=new Model(24);
Model *playerShipModel=new Model(18);
Model *basicGunModel=new Model(20);

GLuint laserTexture;


/**
 void initModels()
 Set up the constant models
 */
void initModels() {
	ramShipModel->addVertex(Vec3f(1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3f(1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, -1.0f, 0.0f));
	ramShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3f(1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 0.0f, -1.0f));
	ramShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3f(1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, -1.0f, 0.0f));
	ramShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 0.0f, -1.0f));
	ramShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3f(-1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3f(-1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, -1.0f, 0.0f));
	ramShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3f(-1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 0.0f, -1.0f));
	ramShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	ramShipModel->addVertex(Vec3f(-1.0f, 0.0f, 0.0f));
	ramShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, -1.0f, 0.0f));
	ramShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	ramShipModel->addVertex(Vec3f(0.0f, 0.0f, -1.0f));
	ramShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	
	ramShipModel->computeNormals();
	
	ramShipModel->numAttachPoints=16;
	
	for(int i=-1;i<=1;i+=2) {
		for(int j=-1;j<=1;j+=2) {
			for(int k=-1;k<=1;k+=2) {
				ramShipModel->addAttachPoint(Vec3f(i*1.0/3,j*1.0/3,k*1.0/3));
				
				ramShipModel->addAttachPointAngle(Vec3f(-j*k*45,-i*(k+2)*45,0));
			}
		}
	}
	
	playerShipModel->addVertex(Vec3f(0.0f, 0.0f, -2.0f));
	playerShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.5f, 0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.0f, -2.0f));
	playerShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	playerShipModel->addVertex(Vec3f(0.0f, -0.3f, -0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.0f, -2.0f));
	playerShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.5f, -0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(-1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.0f, -2.0f));
	playerShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	playerShipModel->addVertex(Vec3f(0.0f, -0.3f, -0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(-1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.5f, -0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(0.0f, -0.3f, -0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(-1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.5f, 0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(0.0f, -0.3f, 0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	
	playerShipModel->computeNormals();
	
	playerShipModel->numAttachPoints=2;
	
	playerShipModel->addAttachPoint(Vec3f(0.5,0.0,0.0));
	playerShipModel->addAttachPoint(Vec3f(-0.5,0.0,0.0));
	
	//playerShipModel->addAttachPointAngle(Vec3f(0,-15,0.0));
	//playerShipModel->addAttachPointAngle(Vec3f(0,15,0.0));
	playerShipModel->addAttachPointAngle(Vec3f(0,0,0.0));
	playerShipModel->addAttachPointAngle(Vec3f(0,0,0.0));
	
	
	basicGunModel->type=GL_QUADS;
	/*basicGunModel->addVertex(Vec3f(-0.1f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.3f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.3f,0.0f,1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.0f,1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.3f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.3f,0.2f,1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.2f,1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.2f,1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.0f,1.0f));
	basicGunModel->addVertex(Vec3f(-0.3f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.3f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.3f,0.2f,1.0f));
	basicGunModel->addVertex(Vec3f(-0.3f,0.0f,1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.3f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.3f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(0.3f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(0.5f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(0.5f,0.0f,1.0f));
	basicGunModel->addVertex(Vec3f(0.3f,0.0f,1.0f));
	basicGunModel->addVertex(Vec3f(0.3f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(0.5f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(0.5f,0.2f,1.0f));
	basicGunModel->addVertex(Vec3f(0.3f,0.2f,1.0f));
	basicGunModel->addVertex(Vec3f(0.3f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(0.3f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(0.3f,0.2f,1.0f));
	basicGunModel->addVertex(Vec3f(0.3f,0.0f,1.0f));
	basicGunModel->addVertex(Vec3f(0.5f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(0.5f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(0.5f,0.2f,1.0f));
	basicGunModel->addVertex(Vec3f(0.5f,0.0f,1.0f));
	basicGunModel->addVertex(Vec3f(0.3f,0.0f,0.0f));
	basicGunModel->addVertex(Vec3f(0.5f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(0.3f,0.2f,0.0f));
	basicGunModel->addVertex(Vec3f(0.5f,0.0f,0.0f));*/
	
	basicGunModel->addVertex(Vec3f(-0.1f,-0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(0.1f,-0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(0.1f,-0.1f,-1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,-0.1f,-1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(0.1f,0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(0.1f,0.1f,-1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.1f,-1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,-0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.1f,-1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,-0.1f,-1.0f));
	basicGunModel->addVertex(Vec3f(0.1f,-0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(0.1f,0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(0.1f,0.1f,-1.0f));
	basicGunModel->addVertex(Vec3f(0.1f,-0.1f,-1.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,-0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(0.1f,0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(-0.1f,0.1f,0.0f));
	basicGunModel->addVertex(Vec3f(0.1f,-0.1f,0.0f));
	
	for(int i=0;i<20;i++) {
		if(basicGunModel->vertices[i][2]>0)
			basicGunModel->addColor(Vec3f(0.0,1.0,1.0));
		else
			basicGunModel->addColor(Vec3f(0.0,0.0,1.0));
	}
	
	basicGunModel->computeNormals();
	
	//Laser texture
	glGenTextures( 1, &laserTexture);
	glBindTexture( GL_TEXTURE_2D, laserTexture );
	/*glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	// when texture area is large, bilinear filter the original
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	// the texture wraps over at the edges (repeat)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );*/
	
	Image *image=loadBMP("~/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/res/laser.bmp");
	
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 64, 64,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				 //as unsigned numbers
                 image->pixels);               //The actual pixel data
	
	delete image;
	
	
}


/**
 void unloadModels()
 Delete the constant models
 */
void unloadModels() {
	delete ramShipModel;
	delete playerShipModel;
}