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
#include "Laser.h"

class Grenade : public Laser {
public:
	Grenade();
	Grenade(Vec3d p, Vec3d v, Vec3d a, double r, long mt);
	
	void init(Vec3d p, Vec3d v, Vec3d a, double r, long mt);
	void update(double dt);
	void explode();
	void activate();
	void render();
	bool isDone();
	int getDamage(GameObject *other);
	
	double radius;
	Vec3d accell;
	long explodeTime;
	long maxTime;
	bool going;
};

#endif /* defined(__HelloSDL__Nade__) */
