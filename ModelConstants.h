//
//  ModelConstants.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/15/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__ModelConstants__
#define __HelloSDL__ModelConstants__

#include <iostream>
#include "imports.h"

class Model;

extern Model *playerShipModel;
extern Model *ramShipModel;
extern Model *basicGunModel;
extern Model *basicStrutModel;
extern Model *longStrutModel;
extern Model *laserModel;
extern GLuint laserTexture;

void initModels();
void unloadModels();

#endif /* defined(__HelloSDL__ModelConstants__) */
