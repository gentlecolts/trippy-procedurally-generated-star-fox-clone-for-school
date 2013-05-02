//
//  HoverShip.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/2/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__HoverShip__
#define __HelloSDL__HoverShip__

#include <iostream>

#include "EnemyShip.h"

class HoverShip : public EnemyShip {
private:
protected:
	Vec3d oldVel;
public:
	double pauseTime, time;
	HoverShip(double x, double y, int n);
	void init(double x, double y);
	void update(double dt);
	void afterSetup();
};

#endif /* defined(__HelloSDL__HoverShip__) */
