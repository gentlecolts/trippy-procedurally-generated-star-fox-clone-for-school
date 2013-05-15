//
//  SwarmWave.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__SwarmWave__
#define __HelloSDL__SwarmWave__

#include "enemyWave.h"
#include <iostream>

class EnemyShip;

class SwarmWave : public EnemyWave {
public:
    void init();
    void tick();
    bool isDone();
    bool childrenDone();
    void remove(GameObject *obj);
	
    SwarmWave(double diff);
    ~SwarmWave();
private:
	double difficulty;
	int numShips;
    EnemyShip **ships;
    bool done;
protected:
};

#endif /* defined(__HelloSDL__SwarmWave__) */
