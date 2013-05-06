//
//  Model.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/10/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "Model.h"

#include "math.h"
#include "Vec3d.h"

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
 void Model::addColor(Vec3d c)
 Add a color to the color vector (create it if needed), increment the last added color
 */
void Model::addColor(Vec4d c) {
    if(!hasColors) {
        colors=new Vec4d[length];
        hasColors=true;
    }
    
    colors[lastAddedC]=c;
	lastAddedC++;
}

/**
 void Model::addVertex(Vec3d v)
 Add a vertex to the vertex vector (create it if needed), increment the last added vertex
 */
void Model::addVertex(Vec3d v) {
    if(!hasVertices) {
        vertices=new Vec3d[length];
        hasVertices=true;
    }
    
    vertices[lastAddedV]=v;
	lastAddedV++;
}

/**
 void Model::addNormal(Vec3d n)
 Add a normal to the normal vector (pun unintended) (create it if needed), increment the last added normal
 (useful for messing up lighting intentionally...)
 */
void Model::addNormal(Vec3d n) {
    if(!hasNormals) {
        normals=new Vec3d[length/3];
        hasNormals=true;
    }
    
    normals[lastAddedN]=n;
	lastAddedN++;
}

void Model::addAttachPoint(Vec3d ap) {
    if(!hasAP) {
        attachPoints=new Vec3d[numAttachPoints];
        hasAP=true;
    }
    
    attachPoints[lastAddedAP]=ap;
	lastAddedAP++;
}

void Model::addAttachPointAngle(Vec3d apn) {
    if(!hasAPN) {
        attachPointAngles=new Vec3d[numAttachPoints];
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
        normals=new Vec3d[length/verticesPerFace()];
        hasNormals=true;
    }
    
    for(int i=lastAddedN*verticesPerFace();i<lastAddedV;i+=verticesPerFace()) {
        Vec3d v1=vertices[i]-vertices[i+1];
        Vec3d v2=vertices[i]-vertices[i+2];
        
		Vec3d norm=v1.cross(v2).normalize();
		
		Vec3d checkFlip=vertices[i];
		for (int j=1; j<verticesPerFace(); j++) {
			checkFlip+=vertices[i+j];
		}
		//checkFlip/=verticesPerFace();
		
		if(checkFlip[0]*norm[0]<=0 &&
		   checkFlip[1]*norm[1]<=0 &&
		   checkFlip[2]*norm[2]<=0) {
			norm*=-1;
		}
		
        normals[i/verticesPerFace()]=norm;
    }	
	lastAddedN=length/verticesPerFace();
}

void Model::addRectPrism(Vec3d start, Vec3d end) {
	/*for(int pos=0;pos<=1;pos++) {
		for(int axis=0;axis<3;axis++) {
			addRect(
					Vec3d(start[axis]*pos+end[axis]*(1-pos), start[(axis+1)%3]*pos+end[(axis+1)%3]*(1-pos), start[(axis+2)%3]*pos+end[(axis+2)%3]*(1-pos)),
					Vec3d(start[axis]*(1-pos)+end[axis]*pos, start[(axis+1)%3]*pos+end[(axis+1)%3]*(1-pos), start[(axis+2)%3]*pos+end[(axis+2)%3]*(1-pos)),
					Vec3d(start[axis]*(1-pos)+end[axis]*pos, start[(axis+1)%3]*(1-pos)+end[(axis+1)%3]*pos, start[(axis+2)%3]*pos+end[(axis+2)%3]*(1-pos))
					);
		}
	}*/
	
	addRect(
			start,
			Vec3d(end[0],start[1],start[2]),
			Vec3d(end[0],end[1],start[2])
			);
	addRect(
			end,
			Vec3d(start[0],end[1],end[2]),
			Vec3d(start[0],start[1],end[2])
			);
	
	addRect(
			start,
			Vec3d(start[0],end[1],start[2]),
			Vec3d(start[0],end[1],end[2])
			);
	addRect(
			end,
			Vec3d(end[0],start[1],end[2]),
			Vec3d(end[0],start[1],start[2])
			);
	
	addRect(
			start,
			Vec3d(start[0],start[1],end[2]),
			Vec3d(end[0],start[1],end[2])
			);
	addRect(
			end,
			Vec3d(end[0],end[1],start[2]),
			Vec3d(start[0],end[1],start[2])
			);
}
void Model::addTriangle(Vec3d v1,Vec3d v2,Vec3d v3) {
	addVertex(v1);
	addVertex(v2);
	addVertex(v3);
	if(type==GL_QUADS) {
		addVertex(v3);
	}
}
void Model::addRect(Vec3d v1, Vec3d v2, Vec3d v3) {
	if(type==GL_QUADS) {
		addVertex(v1);
		addVertex(v2);
		addVertex(v3);
		Vec3d centerPos=(v3-v1)/2+v1;
		Vec3d toCenterVector=v2-centerPos;
		addVertex(centerPos-toCenterVector);
	} else {
		addVertex(v1);
		addVertex(v2);
		addVertex(v3);
		
		
		addVertex(v1);
		Vec3d centerPos=(v3-v1)/2+v1;
		Vec3d toCenterVector=v2-centerPos;
		addVertex(centerPos-toCenterVector);
		addVertex(v3);
	}
}
void Model::addRect(Vec3d v1, Vec3d v2) {
	addRect(v1, v2, Vec3d(v1[0],v1[1],v2[2]));
}
void Model::addPolygon(Vec3d center, double sideLength, int v, Vec3d norm) {
	double degrees=360/v;
	
	Vec3d sideVec=Vec3d(sideLength,0,0);
	Vec3d *vertices=new Vec3d[v];
	
	for(int i=0;i<v;i++) {
		vertices[i]=center+rotate(sideVec,norm,i*degrees);
	}
	
	for(int i=0;i<v;i++) {
		addVertex(vertices[i]);
		addVertex(center);
		if(type==GL_QUADS)
			addVertex(center);
		addVertex(vertices[(i+1)%v]);
	}
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