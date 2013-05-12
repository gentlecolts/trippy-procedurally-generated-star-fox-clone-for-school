//
//  RegisterEnemies.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/11/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__RegisterEnemies__
#define __HelloSDL__RegisterEnemies__

#include <iostream>
#include "ObjectFactoryRegister.h"

class GameObject;

void registerHoverShipType();
GameObject *hoverShipGetGameObject(GameObject *parent, int seed);
vector<ObjectType> hoverShipCandidateChildren();
Model *hoverShipGetModel();

void registerRamShipType();
GameObject *ramShipGetGameObject(GameObject *parent, int seed);
vector<ObjectType> ramShipCandidateChildren();
Model *ramShipGetModel();

#endif /* defined(__HelloSDL__RegisterEnemies__) */
