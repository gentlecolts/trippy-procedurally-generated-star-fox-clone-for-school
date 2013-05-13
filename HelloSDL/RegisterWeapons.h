//
//  RegisterWeapons.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/13/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__RegisterWeapons__
#define __HelloSDL__RegisterWeapons__

#include <iostream>
#include "ObjectFactoryRegister.h"

void registerBasicGunType();
GameObject *basicGunGetGameObject(GameObject *parent, int seed);
vector<ObjectType *>* basicGunCandidateChildren();
Model *basicGunGetModel();

#endif /* defined(__HelloSDL__RegisterWeapons__) */
