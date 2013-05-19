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

#include "../EnemyShip.h"
#include "ObjectFactory.h"

class HoverShip : public EnemyShip {
private:
protected:
	Vec3d oldVel;
	double lastT;
public:
	double pauseTime, time;
	HoverShip(Model *m, double x, double y);
	HoverShip(Model *m);
	void init(double x, double y, int startPos, int time);
	void update(double dt);
	bool isDone();
};


#endif /* defined(__HelloSDL__HoverShip__) */
