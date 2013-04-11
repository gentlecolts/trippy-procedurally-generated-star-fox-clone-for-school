#include "enemyShip.h"
#include "globals.h"

EnemyShip::EnemyShip(){init((double)(rand())/RAND_MAX*2-1,(double)(rand())/RAND_MAX*2-1);}

EnemyShip::EnemyShip(double x,double y) {
    init(x, y);
}

void EnemyShip::init(double x,double y){
    modelSize=24;

    model=new vertex[modelSize];
    model[0]=vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.0f);
    model[1]=vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[2]=vertex(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[3]=vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.0f);
    model[4]=vertex(0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[5]=vertex(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[6]=vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.0f);
    model[7]=vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[8]=vertex(0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
    model[9]=vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.0f);
    model[10]=vertex(0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[11]=vertex(0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
    model[12]=vertex(-1.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.0f);
    model[13]=vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[14]=vertex(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[15]=vertex(-1.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.0f);
    model[16]=vertex(0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[17]=vertex(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[18]=vertex(-1.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.0f);
    model[19]=vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[20]=vertex(0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
    model[21]=vertex(-1.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.0f);
    model[22]=vertex(0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[23]=vertex(0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);

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

    xpos+=xvel;
    ypos-=yvel;
    zpos-=zvel;

    xvel+=sin(radians(t))/1000;
    zvel+=sin(radians(t+270))/1000;

    yrot+=1;

    //cout<<zvel<<endl;

    for(int i=0;i<lasers.size();i++) {
        if(lasers.at(i)->collidesWithObject(this)) {
            invinceStart=clock();

            break;
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
