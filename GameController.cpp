#include "gameController.h"

#include "imports.h"
#include "globals.h"
#include "playerShip.h"
#include "enemyShip.h"
#include "enemyWave.h"
#include "testEnemyWave1.h"
#include <ctime>

void setupGame() {
    gameObjects.push_back(new PlayerShip());

    /*for(int i=1;i<numGameObjects;i++) {
        gameObjects.push_back(new EnemyShip());
    }*/
    
    
    
    light1[0]=0;
    light1[1]=0;
    light1[2]=-1.5;
    light1[3]=1;
    
    glLightfv(GL_LIGHT1, GL_POSITION, light1);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.125);
}

void updateObjects() {
    
    long prev=curTime;
    curTime=clock()-startTime;      //fack why is time an int?
    
    if(prev!=curTime && curTime%waveTime==0) {
        readyForNextWave=true;
    }
    if(currentWave==NULL || (readyForNextWave && currentWave->isDone())) {
        nextWave();
        readyForNextWave=false;
        
    }
    
	for(int i=0;i<gameObjects.size();i++) {
        if(gameObjects.at(i)->isDone() && (gameObjects.at(i)->parentWave==NULL || gameObjects.at(i)->parentWave->isDone())) {
            GameObject *obj=gameObjects.at(i);
            gameObjects.erase(gameObjects.begin()+i);
            
            obj->parentWave->remove(obj);
            obj->parentWave->release();
            
            delete obj;
            i--;
        }
        
        gameObjects.at(i)->doUpdate();
        
    }

    for(int i=0;i<lasers.size();i++) {
        lasers.at(i)->update();
        
        //lasers.at(i)->zpos<-noiseScale*2  <- and this is why -> is a stupid operator
        
        if(lasers.at(i)->collidesWithNoise() || lasers.at(i)->zpos<-noiseScale*2 ||lasers.at(i)->zpos>cameraOffset) {
            Laser *obj=lasers.at(i);
            lasers.erase(lasers.begin()+i);
            
            delete obj;
            i--;
        }
    }
}

void nextWave() {
    if(currentWave!=NULL)
        currentWave->release();
    
    currentWave=new TestEnemyWave1;
    
    currentWave->init();
    currentWave->retain();
}

void renderObjects() {
    //glScalef(0.3f,0.3f,0.3f);

    for(int i=0;i<gameObjects.size();i++) {
        gameObjects.at(i)->render();
    }

    for(int i=0;i<lasers.size();i++) {
        lasers.at(i)->render();
    }
}

void addLaser(Laser* las) {      //THIS NEEDS TO BE ELSEWHERE BUT FKING includeS
    
	lasers.push_back(las);
}

void unloadGame() {
    delete currentWave;
    
    for(int i=0;i<gameObjects.size();i++){
        delete gameObjects.at(i);
    }
    
    for(int i=0;i<lasers.size();i++){
        delete lasers.at(i);
    }
}
