#include "enemyShip.h"
#include "globals.h"
#include "Model.h"
#include "Vec3d.h"
#include "ExplodeAnimation.h"
#include "Laser.h"

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
	pos[2]-=thePlayerShip->vel[2]*dt;
	//cout<<"subtracting "<<(thePlayerShip->zvel)<<endl;
	//cout<<"dt "<<dt<<endl;

	if(!dead) {
		//pos+=vel*dt;
		pos[0]+=vel[0]*dt;
		pos[1]-=vel[1]*dt;
		pos[2]-=vel[2]*dt;
		
		GameShip *obj=lasers;
		
		while(obj!=NULL) {
			if(obj->collidesWithObject(this)) {
				invinceStart=clock();
				setAnimation(new ExplodeAnimation(model,this));
				
				for(int i=0;i<numChildren;i++) {
					children[i]->setAnimation(new ExplodeAnimation(children[i]->model,NULL));
				}
				
				vel[0]=0;
				vel[1]=0;
				
				dead=true;

				break;
			}
			obj=obj->getNext();
		}
	}
}

/**
 bool EnemyShip::isDone()
 Returns true if it's out of the game area in x, y or z
 */
bool EnemyShip::isDone() {
    return abs(pos[0])>noiseScale || abs(pos[1])>noiseScale || pos[2]>cameraOffset || pos[2]<-noiseScale*2;
}
