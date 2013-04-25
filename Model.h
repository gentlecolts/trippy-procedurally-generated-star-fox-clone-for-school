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

class Vec3f;
#include "structs.h"
#include "imports.h"

class Model {
public:
    Vec3f* vertices;
    Vec3f* colors;
    Vec3f* normals;
    int length;
	GLenum type;
	
	Vec3f *attachPoints;
	Vec3f *attachPointAngles;
	int numAttachPoints;
	
    Model(int l);
    void addVertex(Vec3f v);
    void addColor(Vec3f c);
    void addNormal(Vec3f n);
	void addAttachPoint(Vec3f ap);
	void addAttachPointAngle(Vec3f apn);
    int faces();
	int verticesPerFace();
	
    void computeNormals();
    
    ~Model();
protected:
private:
    int lastAddedC, lastAddedV, lastAddedN, lastAddedAP, lastAddedAPN;
    bool hasNormals, hasVertices, hasColors, hasAP, hasAPN;
};

#endif /* defined(__HelloSDL__Model__) */
