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

class BasicStrut : public GameObject {
	
public:
	BasicStrut(GameObject *p, Model *m);
	virtual void initAttachPoints();
	virtual void afterSetup();
};

#endif /* defined(__HelloSDL__BasicStrut__) */
