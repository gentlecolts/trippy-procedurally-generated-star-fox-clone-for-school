#include "enemyShip.h"

#include "globals.h"

EnemyShip::EnemyShip(){init();}

void EnemyShip::init(){
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

    xpos=(double)(rand())/RAND_MAX*2-1;
    ypos=(double)(rand())/RAND_MAX*2-1;
    zpos=-5;

    xvel=.01;
    yvel=-.01;
    zvel=.01;

    t=0;

    cout<<"ENEMY SHIELDS ANALYZIED"<<endl;
}

void EnemyShip::update() {
    t++;

    xpos+=xvel;
    ypos-=yvel;
    zpos-=zvel;

    xvel+=sin(t)/100;
    zvel+=sin(t)/100;
}
