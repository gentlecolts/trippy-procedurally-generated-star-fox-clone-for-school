//
//  RegisterStruts.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/11/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__RegisterStruts__
#define __HelloSDL__RegisterStruts__

#include <iostream>
#include "ObjectFactoryRegister.h"

void registerBasicStrutType();
GameObject *basicStrutGetGameObject(GameObject *parent, int seed);
vector<ObjectType>* basicStrutCandidateChildren();
Model *basicStrutGetModel();

void registerAimingStrutType();
GameObject *aimingStrutGetGameObject(GameObject *parent, int seed);
vector<ObjectType>* aimingStrutCandidateChildren();
Model *aimingStrutGetModel();

void registerRotateStrutType();
GameObject *rotateStrutGetGameObject(GameObject *parent, int seed);
vector<ObjectType>* rotateStrutCandidateChildren();
Model *rotateStrutGetModel();

#endif /* defined(__HelloSDL__RegisterStruts__) */
