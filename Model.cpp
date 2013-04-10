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
}

void Model::addVertex(Vec3f v) {
    if(!hasVertices) {
        vertices=new Vec3f[length];
        hasVertices=true;
    }
    
    vertices[lastAddedV]=v;
}

void Model::addNormal(Vec3f n) {
    if(!hasNormals) {
        normals=new Vec3f[length/3];
        hasNormals=true;
    }
    
    normals[lastAddedN]=n;
}

void Model::computeNormals() {
    if(!hasNormals) {
        normals=new Vec3f[length/3];
        hasNormals=true;
    }
    
    for(int i=lastAddedN;i<length;i+=3) {
        Vec3f v1=vertices[i]-vertices[i+1];
        Vec3f v2=vertices[i]-vertices[i+2];
        
        normals[i/3]=v1.cross(v2).normalize();
    }
}

Model::~Model() {
    if(hasColors) {
       /* for(int i=0;i<length;i++) {
            delete colors[i];
        }*/
        
        delete colors;
    }
    
    if(hasVertices) {
        /* for(int i=0;i<length;i++) {
         delete colors[i];
         }*/
        
        delete vertices;
    }
    
    if(hasNormals) {
        /* for(int i=0;i<length;i++) {
         delete colors[i];
         }*/
        
        delete normals;
    }
}