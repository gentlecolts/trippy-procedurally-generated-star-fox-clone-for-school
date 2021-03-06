//
//  BasicGun.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/25/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__BasicGun__
#define __HelloSDL__BasicGun__

#include <iostream>
#include "../GameObject.h"

class BasicGun : public GameObject {
public:
	virtual void init();
	virtual void doFire();
	virtual void doDoFire();

	BasicGun(GameObject *p);
	BasicGun();

	double fireRate, lastFired;
};

#endif /* defined(__HelloSDL__BasicGun__) */
