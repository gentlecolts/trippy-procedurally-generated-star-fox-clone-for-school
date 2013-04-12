//
//  Model.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/10/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "Model.h"

#include "Vec3f.h"

Model::Model(int l) {
    length=l;
    
    lastAddedC=0;
    lastAddedV=0;
    lastAddedN=0;
    
    hasColors=false;
    hasNormals=false;
    hasVertices=false;
}

void Model::addColor(Vec3f c) {
    if(!hasColors) {
        colors=new Vec3f[length];
        hasColors=true;
    }
    
    colors[lastAddedC]=c;
	lastAddedC++;
}

void Model::addVertex(Vec3f v) {
    if(!hasVertices) {
        vertices=new Vec3f[length];
        hasVertices=true;
    }
    
    vertices[lastAddedV]=v;
	lastAddedV++;
}

void Model::addNormal(Vec3f n) {
    if(!hasNormals) {
        normals=new Vec3f[length/3];
        hasNormals=true;
    }
    
    normals[lastAddedN]=n;
	lastAddedN++;
}

void Model::computeNormals() {
    if(!hasNormals) {
        normals=new Vec3f[length/3];
        hasNormals=true;
    }
    
    for(int i=lastAddedN*3;i<length;i+=3) {
        Vec3f v1=vertices[i]-vertices[i+1];
        Vec3f v2=vertices[i]-vertices[i+2];
        
		Vec3f norm=v1.cross(v2).normalize();
		
		if((vertices[i][0]+vertices[i+1][0]+vertices[i+2][0])/3*norm[0]<=0 &&
		   (vertices[i][1]+vertices[i+1][1]+vertices[i+2][1])/3*norm[1]<=0 &&
		   (vertices[i][2]+vertices[i+1][2]+vertices[i+2][2])/3*norm[2]<=0) {
			norm*=-1;
		}
		
        normals[i/3]=norm;
    }	
	lastAddedN=length/3;
}

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
}