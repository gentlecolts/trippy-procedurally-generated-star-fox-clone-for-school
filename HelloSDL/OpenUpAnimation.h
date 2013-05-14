//
//  OpenUpAnimation.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__OpenUpAnimation__
#define __HelloSDL__OpenUpAnimation__

#include <iostream>
#include "Animation.h"

class OpenUpAnimation : public Animation {
protected:
	double time;
	int face;
public:
	OpenUpAnimation(GameObject *obj, Model *m, double t, int f);
	void update(double dt);
	void doTriangleTransform(int n);
};

#endif /* defined(__HelloSDL__OpenUpAnimation__) */
