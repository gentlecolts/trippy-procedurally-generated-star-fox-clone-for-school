//
//  enemyWave.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/8/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "enemyWave.h"
#include "imports.h"
using namespace std;

class GameObject;

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