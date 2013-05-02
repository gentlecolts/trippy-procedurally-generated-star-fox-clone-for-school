#include "gameController.h"

#include "imports.h"
#include "globals.h"
#include "playerShip.h"
#include "enemyShip.h"
#include "enemyWave.h"
#include "testEnemyWave1.h"
#include "ModelConstants.h"
#include "terrain.h"
#include <ctime>

/**
 void setupGame()
 Calls initModels() from ModelConstants, creates the player ship, and creates the light applied to objects only
 */
void setupGame() {
	initModels();
	
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
	while(obj!=NULL) {
		//cout<<obj<<", ";
		obj->doUpdate(dt);

		if(obj->scheduledToDelete || (obj->isDone() && (obj->parentWave==NULL || obj->parentWave->isDone()))) {
			
			obj=obj->destroyAndGetNext();
			//cout<<" and now at "<<obj;
		} else {
			obj=obj->getNext();
		}
	}
	//cout<<endl;

    for(int i=0;i<lasers.size();i++) {
        lasers.at(i)->update(dt);

        //lasers.at(i)->zpos<-noiseScale*2  <- and this is why -> is a stupid operator

        if(lasers.at(i)->collidesWithNoise() || lasers.at(i)->zpos<-noiseScale*2 ||lasers.at(i)->zpos>cameraOffset) {
            Laser *obj=lasers.at(i);
            lasers.erase(lasers.begin()+i);

            delete obj;
            i--;
        }
    }
	
	for(int i=0;i<enemyLasers.size();i++) {
        enemyLasers.at(i)->update(dt);
		
        //enemyLasers.at(i)->zpos<-noiseScale*2  <- and this is why -> is a stupid operator
		
        if(enemyLasers.at(i)->collidesWithNoise() || enemyLasers.at(i)->zpos<-noiseScale*2 ||enemyLasers.at(i)->zpos>cameraOffset) {
            Laser *obj=enemyLasers.at(i);
            enemyLasers.erase(enemyLasers.begin()+i);
			
            delete obj;
            i--;
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

    for(int i=0;i<lasers.size();i++) {
        lasers.at(i)->render();
    }
    
	for(int i=0;i<enemyLasers.size();i++) {
        enemyLasers.at(i)->render();
    }
}

/**
 void addLaser(Laser* las)
 Adds a laser; probably not necessary
 */
void addLaser(Laser* las, bool player) {
	if(player)
		lasers.push_back(las);
	else
		enemyLasers.push_back(las);
}

/**
 void unloadGame()
 Deletes everything
 */
void unloadGame() {
    delete currentWave;

	thePlayerShip->deleteAndDeleteChildren();

    for(int i=0;i<lasers.size();i++){
        delete lasers.at(i);
    }
	
	for(int i=0;i<enemyLasers.size();i++){
        delete enemyLasers.at(i);
    }
}
