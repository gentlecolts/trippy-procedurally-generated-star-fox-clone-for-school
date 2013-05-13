//
//  RamShip.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/15/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__RamShip__
#define __HelloSDL__RamShip__

#include <iostream>

#include "EnemyShip.h"

class RamShip : public EnemyShip {
private:
protected:
public:
	RamShip(Model *m);
	RamShip(Model *m, double x, double y, int n);
	void init(double x, double y);
	void update(double dt);
	bool isDone();
	void afterSetup();
};

#endif /* defined(__HelloSDL__RamShip__) */
