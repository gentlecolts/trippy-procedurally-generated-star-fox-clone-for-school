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

class Model {
public:
    Vec3f* vertices;
    Vec3f* colors;
    Vec3f* normals;
    
    Model(int l);
    void addVertex(Vec3f v);
    void addColor(Vec3f c);
    void addNormal(Vec3f n);
    
    void computeNormals();
    
    ~Model();
protected:
private:
    int length;
    int lastAddedC, lastAddedV, lastAddedN;
    bool hasNormals, hasVertices, hasColors;
};

#endif /* defined(__HelloSDL__Model__) */
