//
//  BasicStrut.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/29/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__BasicStrut__
#define __HelloSDL__BasicStrut__

#include <iostream>
#include "GameObject.h"
#include "ObjectFactory.h"

class BasicStrut : public GameObject {
	
public:
	BasicStrut();
	BasicStrut(GameObject *p, Model *m);
	void init(GameObject *p, Model *m);
	virtual void initAttachPoints();
	virtual void afterSetup();
};

extern ObjectType basicStrutType;
ObjectTypeTree* basicStrutTreeFun(double diff, double size);
GameObject *basicStrutGetGameObject(int seed);
double basicStrutDifficulty(double size);

#endif /* defined(__HelloSDL__BasicStrut__) */
