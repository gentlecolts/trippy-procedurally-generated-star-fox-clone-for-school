//
//  BossWave.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "BossWave.h"
#include "HoverShip.h"
#include "../RamShip.h"
#include "ObjectFactory.h"

BossWave::BossWave(double diff) {
	difficulty=diff;
}

/**
 void BossWave::init()
 Creates 3 RamShips and puts them in play
 */
void BossWave::init(){
	double x=thePlayerShip->pos[0];
	double y=thePlayerShip->pos[1];

	ObjectType *type=typeForName("hoverShip");
	 
	ship=(EnemyShip *)expandTree(NULL, treeFun(type, 3+difficulty/4, 50+difficulty/10));
	cout<<"diff: "<<difficulty<<endl;
	
	ship->init(x, y,-5,8);

    ship->parentWave=this;

	thePlayerShip->appendObject(ship);

	ship->score=100+difficulty*1.5;

    retain();
}

/**
 void BossWave::tick()
 This wave does nothing after being created, just spawns some enemies at the beginnings
 */
void BossWave::tick(){

}

/**
 void BossWave::remove(GameObject *obj)
 Remove a destroyed ship
 */
void BossWave::remove(GameObject *obj) {
    if(ship==obj) {
        ship=NULL;
    }

}

/**
 bool BossWave::isDone()
 Return true if all of its children are done
 */
bool BossWave::isDone(){
    if(done)
        return true;
    else {
		done=childrenDone();
        return done;
    }
}

/**
 bool BossWave::childrenDone()
 Return true if all of its children are done or NULL
 */
bool BossWave::childrenDone(){
    return (ship==NULL || ship->isDone());
}

/**
 BossWave::~BossWave()
 Set the parent wave of all children to NULL
 */
BossWave::~BossWave() {
    if(ship!=NULL)
        ship->parentWave=NULL;
}
