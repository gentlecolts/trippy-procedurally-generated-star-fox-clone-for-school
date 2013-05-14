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
#include "Matrix.h"
#include <ctime>
#include "ObjectFactoryRegister.h"
#include "ObjectFactory.h"


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
	initModels();
	
	registerAll();
	
    //gameObjects.push_back(new PlayerShip(0));
	thePlayerShip=new PlayerShip(0);
	numObjects=1;

    /*for(int i=1;i<numGameObjects;i++) {
        gameObjects.push_back(new EnemyShip());
    }*/

    light1[0]=0;
    light1[1]=0;
    light1[2]=-1.5;
    light1[3]=1;

	GLfloat diffuse[]={3.0,0.0,0.0,1.0};

    glLightfv(GL_LIGHT1, GL_POSITION, light1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.125);

	glEnable(GL_LIGHT1);
}

/**
 void updateObjects()
 Ticks each object and laser, creates a new EnemyWave if necessary, deletes the old if necessary
 */
void updateObjects() {
//	cout<<"tick"<<endl;
    long prev=curTime;
    curTime=SDL_GetTicks();

    if(curTime-lastWaveTime>waveTime) {
        readyForNextWave=true;
		//cout<<gameObjects.size()<<endl;
    }
    if(currentWave==NULL || (readyForNextWave && currentWave->isDone())) {
        nextWave();
		lastWaveTime=curTime;
        readyForNextWave=false;
    }
	
	double dt=(double)(curTime-prev)/1000;		//millis to seconds
	
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

    currentWave=new TestEnemyWave1;

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
    delete currentWave;

	thePlayerShip->deleteAndDeleteChildren();
	if(lasers!=NULL)
		lasers->deleteAndDeleteChildren();
	if(enemyLasers!=NULL)
		enemyLasers->deleteAndDeleteChildren();
}
