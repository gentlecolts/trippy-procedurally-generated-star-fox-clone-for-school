#include "gameController.h"

#include "imports.h"
#include "globals.h"
#include "playerShip.h"
#include "enemyShip.h"
#include "enemyWave.h"
#include "testEnemyWave1.h"
#include "ModelConstants.h"
#include "terrain.h"
#include "math.h"
#include "HelloSDL/Matrix.h"
#include <ctime>
#include "HelloSDL/ObjectFactoryRegister.h"
#include "HelloSDL/ObjectFactory.h"
#include "HelloSDL/SwarmWave.h"
#include "HelloSDL/BossWave.h"
#include "GLHelper.h"


void doTests() {
	cout<<"TESTS!"<<endl;
	getRandomObject(objects, 120, 40);
	getRandomObject(objects, 120, 20);
	getRandomObject(objects, 120, 10);
	getRandomObject(objects, 120, 5);
	cout<<"END TESTS!"<<endl;
}

/*
 dist: (0, 1, 0)
 ang: (90, -0, 0)
 mat: [(1, 0, 0, 0)
 (0, 6.12323e-17, -1, 0)
 (0, 1, 6.12323e-17, 0)
 (0, 0, 0, 1)]
 diff: (0, 1, -6.12323e-17)
 newAng: (90, -0, 0)

 */

/**
 void setupGame()
 Calls initModels() from ModelConstants, creates the player ship, and creates the light applied to objects only
 */
void setupGame() {
	didGameSetup=true;

	initModels();

	registerAll();

    //gameObjects.push_back(new PlayerShip(0));
	thePlayerShip=new PlayerShip(0);
	numObjects=1;

    /*for(int i=1;i<numGameObjects;i++) {
        gameObjects.push_back(new EnemyShip());
    }*/
}

/**
 void updateObjects()
 Ticks each object and laser, creates a new EnemyWave if necessary, deletes the old if necessary
 */
void updateObjects() {
//	cout<<"tick"<<endl;
    long prev=curTime;
    curTime=SDL_GetTicks();

    if(!readyForNextWave && curTime-lastWaveTime>waveTime) {
        readyForNextWave=true;
		waveTime*=0.98;
		noiseScale*=0.95;
		
		cout<<"noiseScale: "<<noiseScale<<endl;
		
		thePlayerShip->health+=10;
		thePlayerShip->health=min(playerHP,thePlayerShip->health);
		//cout<<gameObjects.size()<<endl;
    }
    if(currentWave==NULL || (readyForNextWave && currentWave->isDone())) {
        nextWave();
		lastWaveTime=curTime;
        readyForNextWave=false;
    }

	double dt=(double)(curTime-prev)/1000;		//millis to seconds
<<<<<<< HEAD
	
	playerScore+=dt;
	
=======

>>>>>>> ea6e2b2a642d651c58cf69f29f0be7ab55a1335c
	updateTerrain(dt);

	GameShip* obj=thePlayerShip;
//	cout<<"tick"<<endl;
	while(obj!=NULL) {
//		cout<<"obj: "<<obj<<endl;
		obj->doUpdate(dt);


		if(obj->scheduledToDelete || (obj->isDone() && (obj->parentWave==NULL || obj->parentWave->isDone()))) {

			obj=obj->destroyAndGetNext();
		} else {
			obj=obj->getNext();
		}
	}

	obj=lasers;
	while(obj!=NULL) {
		obj->doUpdate(dt);

		if(obj->scheduledToDelete || obj->isDone()) {

			if(obj==lasers)
				lasers=obj->getNext();
			obj=obj->destroyAndGetNext();
		} else {
			obj=obj->getNext();
		}
	}

	obj=enemyLasers;
	while(obj!=NULL) {
		obj->doUpdate(dt);

		if(obj->scheduledToDelete || obj->isDone()) {
			if(obj==enemyLasers)
				enemyLasers=obj->getNext();
			obj=obj->destroyAndGetNext();
		} else {
			obj=obj->getNext();
		}
	}

}

/**
 void nextWave()
 Releases the old wave if necessary, creates the next one
 */
void nextWave() {
    if(currentWave!=NULL)
        currentWave->release();

	int num=rand()%6;
	if(num<3) {
		currentWave=new TestEnemyWave1(curTime/1000);
	} else if(num==4) {
		currentWave=new SwarmWave(curTime/1000);
	} else {
		currentWave=new BossWave(curTime/1000);
	}

    currentWave->init();
    currentWave->retain();
}

/**
 void renderObjects()
 Draws each object, laser
 */
void renderObjects() {
    //glScalef(0.3f,0.3f,0.3f);

    /*for(int i=0;i<gameObjects.size();i++) {
        gameObjects.at(i)->render();
    }*/

	GameShip *obj=thePlayerShip;
	while(obj!=NULL) {
		obj->render();

		obj=obj->getNext();
	}

	obj=lasers;
	while(obj!=NULL) {
		obj->render();

		obj=obj->getNext();
	}

	obj=enemyLasers;
	while(obj!=NULL) {
		obj->render();

		obj=obj->getNext();
	}
}

/**
 void addLaser(Laser* las)
 Adds a laser; probably not necessary
 */
void addLaser(Laser* las, bool player) {
	if(player) {
		GameShip *oldLas=lasers;

		lasers=las;
		lasers->setNext(oldLas);
	} else {
		GameShip *oldLas=enemyLasers;

		enemyLasers=las;
		enemyLasers->setNext(oldLas);
	}
}

/**
 void unloadGame()
 Deletes everything
 */
void unloadGame() {
	if(didGameSetup) {
		delete currentWave;

		thePlayerShip->deleteAndDeleteChildren();
		if(lasers!=NULL)
			lasers->deleteAndDeleteChildren();
		if(enemyLasers!=NULL)
			enemyLasers->deleteAndDeleteChildren();
	}
}
