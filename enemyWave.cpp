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

void EnemyWave::init(){}
void EnemyWave::tick(){}
bool EnemyWave::isDone(){return false;}
bool EnemyWave::childrenDone(){return false;}
void EnemyWave::remove(GameObject* obj){}

EnemyWave::~EnemyWave(){}

void EnemyWave::retain() {
    references++;
}

void EnemyWave::release() {
    references--;

    if(references<=0) {
        delete this;
    }
}
