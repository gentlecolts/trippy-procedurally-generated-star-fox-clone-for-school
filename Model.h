//
//  Model.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/10/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__Model__
#define __HelloSDL__Model__

#include <iostream>

class Vec3d;
#include "structs.h"
#include "imports.h"

class Model {
public:
    Vec3d* vertices;
    Vec3d* colors;
    Vec3d* normals;
    int length;
	GLenum type;
	
	Vec3d *attachPoints;
	Vec3d *attachPointAngles;
	int numAttachPoints;
	
    Model(int l);
    void addVertex(Vec3d v);
    void addColor(Vec3d c);
    void addNormal(Vec3d n);
	void addAttachPoint(Vec3d ap);
	void addAttachPointAngle(Vec3d apn);
    int faces();
	int verticesPerFace();
	
	void addRectPrism(Vec3d start, Vec3d end);
	void addTriangle(Vec3d v1,Vec3d v2,Vec3d v3);
	void addRect(Vec3d v1, Vec3d v2, Vec3d v3);
	void addRect(Vec3d v1, Vec3d v2);
	void addPolygon(Vec3d center, double sideLength, int vertices, Vec3d norm);
	
    void computeNormals();
    
    ~Model();
protected:
private:
    int lastAddedC, lastAddedV, lastAddedN, lastAddedAP, lastAddedAPN;
    bool hasNormals, hasVertices, hasColors, hasAP, hasAPN;
};

#endif /* defined(__HelloSDL__Model__) */
