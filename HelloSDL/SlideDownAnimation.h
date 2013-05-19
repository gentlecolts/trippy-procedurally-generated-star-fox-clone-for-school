//
//  SlideDownAnimation.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__SlideDownAnimation__
#define __HelloSDL__SlideDownAnimation__

#include <iostream>
#include "../Animation.h"

class SlideDownAnimation : public Animation {
protected:
	double dist, speed;
	void (*callback)(GameObject *callbackObj, GameObject *obj);
	GameObject *callbackObj;
public:
	SlideDownAnimation(GameObject *o, GameObject *cbo, double d, double s, void (*c)(GameObject *callbackObj, GameObject *obj));
	void doModelTransform();
	void update(double dt);
};

#endif /* defined(__HelloSDL__SlideDownAnimation__) */
