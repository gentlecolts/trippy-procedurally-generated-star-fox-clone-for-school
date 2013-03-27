#include "gameController.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "globals.h"
#include "playerShip.h"
#include "enemyShip.h"

void setupGame() {
    gameObjects[0]=new PlayerShip();

    for(int i=1;i<numGameObjects;i++) {
        gameObjects[i]=new EnemyShip();
    }
}

void updateObjects() {
	for(int i=0;i<numGameObjects;i++) {
        gameObjects[i]->update();
    }

    for(int i=0;i<lasers.size();i++) {
        lasers.at(i).update();
    }
}

void renderObjects() {
    glScalef(0.3f,0.3f,0.3f);

    for(int i=0;i<numGameObjects;i++) {
        gameObjects[i]->render();
    }

    for(int i=0;i<lasers.size();i++) {
        lasers.at(i).render();
    }
}

void addLaser(Laser las) {      //THIS NEEDS TO BE ELSEWHERE BUT FKING includeS
	lasers.push_back(las);
}

void unloadGame() {
    for(int i=0;i<numGameObjects;i++){
        delete gameObjects[i];
    }
}
