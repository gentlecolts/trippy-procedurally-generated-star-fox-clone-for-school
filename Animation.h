//
//  Animation.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/10/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__Animation__
#define __HelloSDL__Animation__

#include <iostream>

class Vec3d;
class Model;
class GameObject;

class Animation {
private:
protected:
	double t;
public:
	virtual void doTriangleTransform(int index);
	virtual void doModelTransform();
	virtual void update(double dt);
	
	void tick(double dt);
	
	Animation(Model *m, GameObject *o);
	virtual ~Animation();
	
	Model *model;
	GameObject *object;
};

#endif /* defined(__HelloSDL__Animation__) */
