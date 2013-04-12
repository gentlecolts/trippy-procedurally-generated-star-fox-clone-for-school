//
//  ExplodeAnimation.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/11/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__ExplodeAnimation__
#define __HelloSDL__ExplodeAnimation__

#include <iostream>
#include "Animation.h"

class ExplodeAnimation : public Animation {
public:
	void doTriangleTransform(int index);
	void update();
	
	ExplodeAnimation(Model *m, GameObject *o);
};

#endif /* defined(__HelloSDL__ExplodeAnimation__) */
