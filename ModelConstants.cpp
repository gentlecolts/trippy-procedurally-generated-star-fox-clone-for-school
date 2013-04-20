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

Model *ramShipModel=new Model(24);
Model *playerShipModel=new Model(18);


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
	
	playerShipModel->addVertex(Vec3f(0.0f, 0.0f, -2.0f));
	playerShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.5f, 0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.0f, -2.0f));
	playerShipModel->addColor(Vec3f(1.0f, 0.f, 0.0f));
	playerShipModel->addVertex(Vec3f(0.0f, -0.5f, -0.0f));
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
	playerShipModel->addVertex(Vec3f(0.0f, -0.5f, -0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(-1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.5f, -0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(0.0f, -0.5f, -0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(-1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	playerShipModel->addVertex(Vec3f(0.0f, 0.5f, 0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(0.0f, -0.5f, 0.0f));
	playerShipModel->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	playerShipModel->addVertex(Vec3f(1.0f, 0.0f, 1.0f));
	playerShipModel->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	
	playerShipModel->computeNormals();
	
	
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