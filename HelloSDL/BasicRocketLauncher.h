//
//  BasicRocketLauncher.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__BasicRocketLauncher__
#define __HelloSDL__BasicRocketLauncher__

#include <iostream>
#include "BasicGun.h"

class Grenade;

class BasicRocketLauncher : public BasicGun {
public:
	BasicRocketLauncher(GameObject *p);
	void init();
	void doDoFire();
	void fireRocket(Grenade *g);
};

void fireCallback(GameObject *me, GameObject *o);

#endif /* defined(__HelloSDL__BasicRocketLauncher__) */
