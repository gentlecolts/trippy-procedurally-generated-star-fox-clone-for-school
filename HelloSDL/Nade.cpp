//
//  Nade.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/5/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "Nade.h"

Grenade::Grenade(Vec3d p, Vec3d v, Vec3d a, double r) : GameShip(0) {
	init(p, v, a, r);
}

void Grenade::init(Vec3d p, Vec3d v, Vec3d a, double r) {
	pos=p;
	vel=v;
	accell=a;
	radius=r;
}

void Grenade::update(double dt) {
	pos+=vel;
	vel+=accell;
}