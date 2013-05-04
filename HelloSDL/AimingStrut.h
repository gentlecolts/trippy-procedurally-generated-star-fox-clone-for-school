//
//  AimingStrut.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/3/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__AimingStrut__
#define __HelloSDL__AimingStrut__

#include <iostream>
#include "BasicStrut.h"

class AimingStrut : public BasicStrut {
public:
	AimingStrut(GameObject *p, double speed, Model *m);
	void afterSetup();
	void update(double dt);
	
	double speed;
};

#endif /* defined(__HelloSDL__AimingStrut__) */