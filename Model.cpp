//
//  Model.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/10/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "Model.h"

#include "Vec3f.h"

/**
 Model::Model(int l)
 Set length, initialize variables
 */
Model::Model(int l) {
    length=l;
    
    lastAddedC=0;
    lastAddedV=0;
    lastAddedN=0;
    
    hasColors=false;
    hasNormals=false;
    hasVertices=false;
	
	
	numAttachPoints=0;
	lastAddedAP=0;
	lastAddedAPN=0;
	
	hasAP=false;
	hasAPN=false;
	
	type=GL_TRIANGLES;
}

int Model::faces() {
	switch(type) {
		case GL_TRIANGLES:
		case GL_QUADS:
			return length/verticesPerFace();
			
		default:
			return 0;
	}
}

int Model::verticesPerFace() {
	switch (type) {
		case GL_TRIANGLES:
			return 3;
		case GL_QUADS:
			return 4;
		default:
			return 3;
	}
}

/**
 void Model::addColor(Vec3f c)
 Add a color to the color vector (create it if needed), increment the last added color
 */
void Model::addColor(Vec3f c) {
    if(!hasColors) {
        colors=new Vec3f[length];
        hasColors=true;
    }
    
    colors[lastAddedC]=c;
	lastAddedC++;
}

/**
 void Model::addVertex(Vec3f v)
 Add a vertex to the vertex vector (create it if needed), increment the last added vertex
 */
void Model::addVertex(Vec3f v) {
    if(!hasVertices) {
        vertices=new Vec3f[length];
        hasVertices=true;
    }
    
    vertices[lastAddedV]=v;
	lastAddedV++;
}

/**
 void Model::addNormal(Vec3f n)
 Add a normal to the normal vector (pun unintended) (create it if needed), increment the last added normal
 (useful for messing up lighting intentionally...)
 */
void Model::addNormal(Vec3f n) {
    if(!hasNormals) {
        normals=new Vec3f[length/3];
        hasNormals=true;
    }
    
    normals[lastAddedN]=n;
	lastAddedN++;
}

void Model::addAttachPoint(Vec3f ap) {
    if(!hasAP) {
        attachPoints=new Vec3f[numAttachPoints];
        hasAP=true;
    }
    
    attachPoints[lastAddedAP]=ap;
	lastAddedAP++;
}

void Model::addAttachPointAngle(Vec3f apn) {
    if(!hasAPN) {
        attachPointAngles=new Vec3f[numAttachPoints];
        hasAPN=true;
    }
    
    attachPointAngles[lastAddedAPN]=apn;
	lastAddedAPN++;
}

/**
 void Model::computeNormals()
 Create the normal array if it doesn't exist, calculate all remaining normals
 */
void Model::computeNormals() {
    if(!hasNormals) {
        normals=new Vec3f[length/verticesPerFace()];
        hasNormals=true;
    }
    
    for(int i=lastAddedN*verticesPerFace();i<lastAddedV;i+=verticesPerFace()) {
        Vec3f v1=vertices[i]-vertices[i+1];
        Vec3f v2=vertices[i]-vertices[i+2];
        
		Vec3f norm=v1.cross(v2).normalize();
		
		Vec3f checkFlip=vertices[i];
		for (int j=1; j<verticesPerFace(); j++) {
			checkFlip+=vertices[i+j];
		}
		checkFlip/=verticesPerFace();
		
		if(checkFlip[0]*norm[0]<=0 &&
		   checkFlip[1]*norm[1]<=0 &&
		   checkFlip[2]*norm[2]) {
			norm*=-1;
		}
		
        normals[i/verticesPerFace()]=norm;
    }	
	lastAddedN=length/verticesPerFace();
}

/**
 Model::~Model()
 Delete colors, vertices, normals
 */
Model::~Model() {
    if(hasColors) {
        delete[] colors;
    }
    
    if(hasVertices) {
        delete[] vertices;
    }
    
    if(hasNormals) {
        delete[] normals;
    }
	
	if(hasAP) {
		delete[] attachPoints;
	}
	
	if(hasAPN) {
		delete[] attachPointAngles;
	}
}