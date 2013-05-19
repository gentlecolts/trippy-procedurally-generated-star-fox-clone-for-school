//
//  BossWave.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__BossWave__
#define __HelloSDL__BossWave__

#include <iostream>
#include "../enemyWave.h"

class EnemyShip;

class BossWave : public EnemyWave {
public:
    void init();
    void tick();
    bool isDone();
    bool childrenDone();
    void remove(GameObject *obj);

    BossWave(double diff);
	~BossWave();
private:
	double difficulty;
    EnemyShip *ship;
    bool done;
protected:
};

#endif /* defined(__HelloSDL__BossWave__) */
