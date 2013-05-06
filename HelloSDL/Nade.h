//
//  Nade.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/5/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__Nade__
#define __HelloSDL__Nade__

#include <iostream>
#include "Nade.h"
#include "gameShip.h"

class Grenade : public GameShip {
public:
	
	Grenade(Vec3d p, Vec3d v, Vec3d a, double r);
	
	void init(Vec3d p, Vec3d v, Vec3d a, double r);
	void update(double dt);
	
	double radius;
	Vec3d accell;
};

#endif /* defined(__HelloSDL__Nade__) */
