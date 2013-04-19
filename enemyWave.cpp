//
//  enemyWave.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/8/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

//again with this shit? why? what? fuck? shit...? no.

#include "enemyWave.h"
#include "imports.h"
using namespace std;

//class GameObject;//fuck u just include it
#include "gameobject.h"

void EnemyWave::init(){}						//Initialize the wave
void EnemyWave::tick(){}						//Do any tasks that need to be done each frame
bool EnemyWave::isDone(){return false;}			//Returns true if it's ready to be replaced as the active wave
bool EnemyWave::childrenDone(){return false;}	//Returns true if its child objects are all done
void EnemyWave::remove(GameObject* obj){}		//Removes any pointers to objects destroyed externally (e.g. being shot)

EnemyWave::~EnemyWave(){}

/**
 void EnemyWave::retain()
 Reference counting so that waves can be deleted after the game no longer has them as the active wave but they still are controlling objects. Increment the reference counter.
 */
void EnemyWave::retain() {
    references++;
}

/**
 void EnemyWave::release()
 Reference counting so that waves can be deleted after the game no longer has them as the active wave but they still are controlling objects. Decrement the reference counter. If it's <=0, delete this object.
 */
void EnemyWave::release() {
    references--;

    if(references<=0) {
        delete this;
    }
}
