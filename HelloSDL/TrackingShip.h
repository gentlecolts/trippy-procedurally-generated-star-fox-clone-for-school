//
//  TrackingShip.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/13/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__TrackingShip__
#define __HelloSDL__TrackingShip__

#include <iostream>

#include "../EnemyShip.h"
#include "ObjectFactory.h"

class TrackingShip : public EnemyShip {
private:
protected:
	Vec3d oldVel;
public:
	double pauseTime, time;
	TrackingShip(Model *m, double x, double y);
	TrackingShip(Model *m);
	void init(double x, double y, int startPos, int time);
	void update(double dt);
	void afterSetup();
	bool isDone();
};

#endif /* defined(__HelloSDL__TrackingShip__) */
