//
//  enemyWave.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/8/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__enemyWave__
#define __HelloSDL__enemyWave__

#include <iostream>

class GameObject;

class EnemyWave {
public:
    virtual void init();
    virtual void tick();
    virtual bool isDone();
    virtual bool childrenDone();
    virtual void remove(GameObject* obj);

    EnemyWave():references(0){};
    virtual ~EnemyWave();

    void retain();
    void release();
private:
protected:
    //int references=0;     //FIIINE
    int references;     //FIIINE
};

#endif /* defined(__HelloSDL__enemyWave__) */
