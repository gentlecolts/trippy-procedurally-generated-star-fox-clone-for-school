//
//  RotateStrut.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/2/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__RotateStrut__
#define __HelloSDL__RotateStrut__

#include <iostream>
#include "BasicStrut.h"

class RotateStrut : public BasicStrut {
public:
	RotateStrut();
	RotateStrut(GameObject *p, Model *m, Vec3d s, Vec3d e, double t);
	void init(GameObject *p, Model *m, Vec3d s, Vec3d e, double t);
	void update(double dt);
	void afterSetup();
	
	Vec3d startAngle,endAngle,velAngle;
	double time;
};

#endif /* defined(__HelloSDL__RotateStrut__) */
