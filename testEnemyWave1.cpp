
//
//  testEnemyWave1.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/8/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

//jesus dick

#include "RamShip.h"
#include "testEnemyWave1.h"

void TestEnemyWave1::init(){
    //double x=rand()%(2*noiseScale)-noiseScale;
    //double y=rand()%(2*noiseScale)-noiseScale;
	
	double x=thePlayerShip->xpos;
	double y=thePlayerShip->ypos;

	int s=gameObjects.size();
	
    ship1=new RamShip(-x+.5,-y+.5,s);
    ship2=new RamShip(-x+.5,-y,s+1);
    ship3=new RamShip(-x,-y+.5,s+2);

    ship1->parentWave=this;
    ship2->parentWave=this;
    ship3->parentWave=this;

    gameObjects.push_back(ship1);
    gameObjects.push_back(ship2);
    gameObjects.push_back(ship3);

    retain();
    retain();
    retain();
}

void TestEnemyWave1::tick(){

}

void TestEnemyWave1::remove(GameObject *obj) {
    if(ship1==obj) {
        ship1=NULL;
    }
    if(ship2==obj) {
        ship2=NULL;
    }
    if(ship3==obj) {
        ship3=NULL;
    }

}

bool TestEnemyWave1::isDone(){
    if(done)
        return true;
    else {
        done=childrenDone();
        return done;
    }
}

bool TestEnemyWave1::childrenDone(){
    return (ship1==NULL || ship1->isDone()) && (ship2==NULL || ship2->isDone()) && (ship3==NULL || ship3->isDone());
}

TestEnemyWave1::~TestEnemyWave1() {
    if(ship1!=NULL)
        ship1->parentWave=NULL;
    if(ship2!=NULL)
        ship2->parentWave=NULL;
    if(ship3!=NULL)
        ship3->parentWave=NULL;
}
