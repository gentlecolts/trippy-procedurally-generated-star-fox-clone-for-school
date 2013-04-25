#include "enemyShip.h"
#include "globals.h"
#include "Model.h"
#include "vec3f.h"
#include "ExplodeAnimation.h"

/**
 EnemyShip::EnemyShip(int n)
 Conveniently initializes it at a random location, setting t to 0 and dead to false
 */
EnemyShip::EnemyShip(int n) : GameShip(n)
{
    t=0;
	dead=false;
	init((double)(rand())/RAND_MAX*2-1,(double)(rand())/RAND_MAX*2-1);
}

/**
 EnemyShip::EnemyShip(int n)
 Conveniently initializes it at a specified location, setting t to 0 and dead to false
 */
EnemyShip::EnemyShip(double x,double y, int n) : GameShip(n) {
    t=0;
	dead=false;
    init(x, y);
}

/**
 void EnemyShip::init(double x,double y)
 Does nothing because this shouldn't be instantiated, only subclassed
 */
void EnemyShip::init(double x,double y){
}

/**
 void EnemyShip::update(double dt)
 Increments t by dt, then moves by xvel, yvel, and zvel, and does collision detection with lasers (and eventually other objects)
 */
void EnemyShip::update(double dt) {
    t+=dt;
	zpos-=thePlayerShip->zvel*dt;
	//cout<<"subtracting "<<(thePlayerShip->zvel)<<endl;
	//cout<<"dt "<<dt<<endl;

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

/**
 bool EnemyShip::isDone()
 Returns true if it's out of the game area in x, y or z
 */
bool EnemyShip::isDone() {
    return abs(xpos)>noiseScale || abs(ypos)>noiseScale || zpos>cameraOffset || zpos<-noiseScale*2;
}
