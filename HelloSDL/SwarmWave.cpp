//
//  SwarmWave.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "SwarmWave.h"

#include "HoverShip.h"
#include "../RamShip.h"
#include "ObjectFactory.h"

SwarmWave::SwarmWave(double diff) {
	done=false;
	difficulty=diff;
}

/**
 void SwarmWave::init()
 Creates 3 RamShips and puts them in play
 */
void SwarmWave::init(){
//	cout<<"swarm wave"<<endl;

	double x=thePlayerShip->pos[0];
	double y=thePlayerShip->pos[1];

	numShips=min((((double)rand())/RAND_MAX*.2+1)*(5+difficulty/3),10.0);

	ObjectType *type=typeForName("ramShip");

	ObjectTypeTree *tree=treeFun(type, 5+difficulty/3, 3+rand()%4);

	ships=new EnemyShip*[numShips];

	double slope=1.0/(rand()%10);

	for(int i=0;i<numShips;i++) {
		ships[i]=(EnemyShip *)expandTree(NULL, tree);
		ships[i]->init(x+i+((double)rand())/RAND_MAX*(3+i)-3, y+i*slope+((double)rand())/RAND_MAX*(3+i)-3,-10,4);
		ships[i]->parentWave=this;
		thePlayerShip->appendObject(ships[i]);
		ships[i]->score=20+difficulty;

		ships[i]->health=3;

		retain();
	}
}

/**
 void SwarmWave::tick()
 This wave does nothing after being created, just spawns some enemies at the beginnings
 */
void SwarmWave::tick(){

}

/**
 void SwarmWave::remove(GameObject *obj)
 Remove a destroyed ship
 */
void SwarmWave::remove(GameObject *obj) {
	for(int i=0;i<numShips;i++) {
		if(ships[i]==obj) {
			ships[i]=NULL;
			return;
		}
	}
}

/**
 bool SwarmWave::isDone()
 Return true if all of its children are done
 */
bool SwarmWave::isDone(){
    if(done)
        return true;
    else {
		done=childrenDone();
        return done;
    }
}

/**
 bool SwarmWave::childrenDone()
 Return true if all of its children are done or NULL
 */
bool SwarmWave::childrenDone(){
	bool chkdone=(ships[0]==NULL || ships[0]->isDone());

	for(int i=1;i<numShips;i++) {
		chkdone&=(ships[i]==NULL || ships[i]->isDone());
	}

    return chkdone;
}

/**
 SwarmWave::~SwarmWave()
 Set the parent wave of all children to NULL
 */
SwarmWave::~SwarmWave() {
	for(int i=0;i<numShips;i++) {
		if(ships[i]!=NULL) {
			ships[i]->parentWave=NULL;
		}
	}

	//delete the array without deleting the contents (this might be wrong)
	delete ships;
}
