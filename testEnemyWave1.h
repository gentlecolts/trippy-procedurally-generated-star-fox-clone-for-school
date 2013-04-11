//
//  testEnemyWave1.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/8/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

//applebloom

#ifndef __HelloSDL__testEnemyWave1__
#define __HelloSDL__testEnemyWave1__

//also, that underscoring seems excissive...see the ones on .h files made in codeblocs
//huh...that makes sense now...apple just has a fetish for way more characters than necessary
//oh yeah baby, gimmy ur chars

#include "enemyWave.h"
#include <iostream>

class TestEnemyWave1 : public EnemyWave {
public:
    void init();
    void tick();
    bool isDone();
    bool childrenDone();
    void remove(GameObject *obj);

    TestEnemyWave1():done(false){}
    ~TestEnemyWave1();
private:
    EnemyShip *ship1,*ship2,*ship3;
    bool done;
protected:
};

#endif /* defined(__HelloSDL__testEnemyWave1__) */
