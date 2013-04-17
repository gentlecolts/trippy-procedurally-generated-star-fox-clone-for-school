#include "enemyShip.h"
#include "globals.h"
#include "Model.h"
#include "vec3f.h"
#include "ExplodeAnimation.h"

EnemyShip::EnemyShip(int n) : GameObject(n)
{
	init((double)(rand())/RAND_MAX*2-1,(double)(rand())/RAND_MAX*2-1);
}

EnemyShip::EnemyShip(double x,double y, int n) : GameObject(n) {
    t=0;
	dead=false;
    init(x, y);
}

void EnemyShip::init(double x,double y){
}

void EnemyShip::update(double dt) {
    t+=dt;

	if(!dead) {
		xpos+=xvel*dt;
		ypos-=yvel*dt;
		zpos-=zvel*dt;
		
		for(int i=0;i<lasers.size();i++) {
			if(lasers.at(i)->collidesWithObject(this)) {
				invinceStart=clock();
				setAnimation(new ExplodeAnimation(model,this));
				xvel=0;
				yvel=0;
				
				dead=true;

				break;
			}
		}
	}
}

bool EnemyShip::isDone() {      //hack?
    return abs(xpos)>noiseScale || abs(ypos)>noiseScale || zpos>cameraOffset || zpos<-noiseScale*2;
}
