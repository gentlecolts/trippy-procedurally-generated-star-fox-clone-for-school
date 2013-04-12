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
    init(x, y);
}

void EnemyShip::init(double x,double y){
    modelSize=24;
	
	model=new Model(modelSize);

	model->addVertex(Vec3f(1.0f, 0.0f, 0.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, 1.0f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, 1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(1.0f, 0.0f, 0.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, -1.0f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, 1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(1.0f, 0.0f, 0.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, 1.0f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, -1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(1.0f, 0.0f, 0.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, -1.0f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, -1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(-1.0f, 0.0f, 0.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, 1.0f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, 1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(-1.0f, 0.0f, 0.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, -1.0f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, 1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(-1.0f, 0.0f, 0.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, 1.0f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, -1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(-1.0f, 0.0f, 0.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, -1.0f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, -1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	
	model->computeNormals();
	
    xpos=x;
    ypos=y;
    //cout<<"x "<<xpos<<" y "<<ypos<<endl;
    zpos=-5;

    xvel=.01;
    yvel=-.01;
    zvel=.01;

    xrot=0;
    yrot=0;
    zrot=0;

    t=0;

    //cout<<"ENEMY SHIELDS ANALYZIED"<<endl;
}

void EnemyShip::update() {
    t+=.5;

	if(invinceStart<0) {
		xpos+=xvel;
		ypos-=yvel;
		zpos-=zvel;

		xvel+=sin(radians(t))/1000;
		zvel+=sin(radians(t+270))/1000;

		yrot+=1;
	}

    //cout<<zvel<<endl;

	if(invinceStart<0) {
	
		for(int i=0;i<lasers.size();i++) {
			if(lasers.at(i)->collidesWithObject(this)) {
				invinceStart=clock();
				theAnimation=new ExplodeAnimation(model,this);
				xvel=0;
				yvel=0;

				break;
			}
		}
	}
}

void EnemyShip::uniqueRender() {
//    if(!isDone()) {
//        cout<<"x:"<<xpos<<" y:"<<ypos<<endl;
//    }
}

bool EnemyShip::isDone() {      //hack?
    return abs(xpos)>noiseScale || abs(ypos)>noiseScale || zpos>cameraOffset || zpos<-noiseScale*2;
}
