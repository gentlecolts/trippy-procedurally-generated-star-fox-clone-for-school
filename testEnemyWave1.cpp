
//
//  testEnemyWave1.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/8/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "testEnemyWave1.h"
#include "HoverShip.h"
#include "RamShip.h"
#include "ObjectFactory.h"


/**
 void TestEnemyWave1::init()
 Creates 3 RamShips and puts them in play
 */
void TestEnemyWave1::init(){
	cout<<"wave"<<endl;
	
    //double x=rand()%(2*noiseScale)-noiseScale;
    //double y=rand()%(2*noiseScale)-noiseScale;
	
	double x=thePlayerShip->pos[0];
	double y=thePlayerShip->pos[1];

	int s=numObjects;
	
    /*ship1=new RamShip(x,y,s);
    ship2=new RamShip(x+.5,y,s+1);
    ship3=new RamShip(x,y+.5,s+2);//*/
	
	/*
	ship1=new HoverShip(x,y,s);
    ship2=new HoverShip(x+3,y,s+1);
    ship3=new HoverShip(x,y+3,s+2);
	//*/
	
	ship1=(EnemyShip *)expandTree(NULL, getTree(20, 5));
	ship2=(EnemyShip *)expandTree(NULL, getTree(20, 5));
	ship3=(EnemyShip *)expandTree(NULL, getTree(20, 5));
	
	/*ObjectType *type=typeForName("hoverShip");
	
	ship1=(EnemyShip *)expandTree(NULL, treeFun(type, 20, 2));
	ship2=(EnemyShip *)expandTree(NULL, treeFun(type, 20, 2));
	ship3=(EnemyShip *)expandTree(NULL, treeFun(type, 20, 2));*/
	
	ship1->init(x, y,-5,8);
	ship2->init(x+2, y,-5,8);
	ship3->init(x, y+2,-5,8);
	
    ship1->parentWave=this;
    ship2->parentWave=this;
    ship3->parentWave=this;

	thePlayerShip->appendObject(ship1);
	thePlayerShip->appendObject(ship2);
	thePlayerShip->appendObject(ship3);

    retain();
    retain();
    retain();
}

/**
 void TestEnemyWave1::tick()
 This wave does nothing after being created, just spawns some enemies at the beginnings
 */
void TestEnemyWave1::tick(){

}

/**
 void TestEnemyWave1::remove(GameObject *obj)
 Remove a destroyed ship
 */
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

/**
 bool TestEnemyWave1::isDone()
 Return true if all of its children are done
 */
bool TestEnemyWave1::isDone(){
    if(done)
        return true;
    else {
		done=childrenDone();
        return done;
    }
}

/**
 bool TestEnemyWave1::childrenDone()
 Return true if all of its children are done or NULL
 */
bool TestEnemyWave1::childrenDone(){
    return (ship1==NULL || ship1->isDone()) && (ship2==NULL || ship2->isDone()) && (ship3==NULL || ship3->isDone());
}

/**
 TestEnemyWave1::~TestEnemyWave1()
 Set the parent wave of all children to NULL
 */
TestEnemyWave1::~TestEnemyWave1() {
    if(ship1!=NULL)
        ship1->parentWave=NULL;
    if(ship2!=NULL)
        ship2->parentWave=NULL;
    if(ship3!=NULL)
        ship3->parentWave=NULL;
}
