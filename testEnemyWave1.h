//
//  testEnemyWave1.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/8/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__testEnemyWave1__
#define __HelloSDL__testEnemyWave1__

#include "enemyWave.h"
#include <iostream>

class TestEnemyWave1 : public EnemyWave {
public:
    void init();
    void tick();
    bool isDone();
    bool childrenDone();
    void remove(GameObject *obj);
    
    ~TestEnemyWave1();
private:
    EnemyShip *ship1,*ship2,*ship3;
    bool done=false;
protected:
};

#endif /* defined(__HelloSDL__testEnemyWave1__) */
