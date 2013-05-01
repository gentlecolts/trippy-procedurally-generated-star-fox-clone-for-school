//
//  FanStrutThing.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/30/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__FanStrutThing__
#define __HelloSDL__FanStrutThing__

#include <iostream>
#include "BasicStrut.h"

class FanStrut : public BasicStrut {
public:
	FanStrut(GameObject *p, int l, Model *m);
	int level;
	void afterSetup();
};

#endif /* defined(__HelloSDL__FanStrutThing__) */
