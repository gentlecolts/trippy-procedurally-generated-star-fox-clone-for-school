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

/**
 void doTests()
 A function for arbitrary test code.
 */
void doTests() {
	cout<<"TESTS!"<<endl;
	getRandomObject(objects, 120, 40);
	getRandomObject(objects, 120, 20);
	getRandomObject(objects, 120, 10);
	getRandomObject(objects, 120, 5);
	cout<<"END TESTS!"<<endl;
}

/**
 void setupGame()
 Calls initModels() from ModelConstants, creates the player ship, and registers objects for the object factory
 */
void setupGame() {
	didGameSetup=true;

	initModels();

	registerAll();

	thePlayerShip=new PlayerShip();
}

void updateObjFrom(GameShip** base,double dt){
	GameShip* obj=*base;

	if(obj!=NULL){
		printf(("\n---updating objects---\nobject type: "+string((*base)->getType())+"\n").c_str());
	}

	while(obj!=NULL) {
		printf("obj before doUpdate: %p\n",obj);
		printf("calling doUpdate\n");
		obj->doUpdate(dt);
		printf("doUpdate done");

		printf("asdf\n");
		printf("obj after doUpdate: %p\n",obj);
		printf("blah\n");

		if(obj->scheduledToDelete || obj->isDone()) {
			if(obj==*base){
				*base=obj->getNext();
			}
			obj=obj->destroyAndGetNext();
		} else {
			obj=obj->getNext();
		}
	}
}

/**
 void updateObjects()
 Ticks each object and laser, creates a new EnemyWave if necessary, deletes the old if necessary, scales the difficulty, and increases the player's score.
 */
void updateObjects() {
//	cout<<"tick"<<endl;
    long prev=curTime;
    curTime=SDL_GetTicks();

    if(!readyForNextWave && curTime-lastWaveTime>waveTime) {
        readyForNextWave=true;
		waveTime*=0.98;
		noiseScale*=0.95;

//		cout<<"noiseScale: "<<noiseScale<<endl;

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

	playerScore+=dt;
	updateTerrain(dt);

	updateObjFrom(&thePlayerShip,dt);
	updateObjFrom(&lasers,dt);
	updateObjFrom(&enemyLasers,dt);

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
