#include "playerShip.h"

#include <iostream>

void PlayerShip::init(){
    modelSize=18;

    model=new vertex[modelSize];
    model[0]=vertex(0.0f, 0.0f, -2.0f, 1.0f, 0.f, 0.0f);
    model[1]=vertex(0.0f, 0.5f, -0.0f, 0.0f, 1.0f, 0.0f);
    model[2]=vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[3]=vertex(0.0f, 0.0f, -2.0f, 1.0f, 0.f, 0.0f);
    model[4]=vertex(0.0f, -0.5f, -0.0f, 0.0f, 1.0f, 0.0f);
    model[5]=vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[6]=vertex(0.0f, 0.0f, -2.0f, 1.0f, 0.f, 0.0f);
    model[7]=vertex(0.0f, 0.5f, -0.0f, 0.0f, 1.0f, 0.0f);
    model[8]=vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[9]=vertex(0.0f, 0.0f, -2.0f, 1.0f, 0.f, 0.0f);
    model[10]=vertex(0.0f, -0.5f, -0.0f, 0.0f, 1.0f, 0.0f);
    model[11]=vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[12]=vertex(0.0f, 0.5f, -0.0f, 0.0f, 1.0f, 0.0f);//lost track here
    model[13]=vertex(0.0f, -0.5f, -0.0f, 0.0f, 1.0f, 0.0f);
    model[14]=vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[15]=vertex(0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[16]=vertex(0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[17]=vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);


    zpos=-3;
    /*
    cout<<"init()"<<endl;
    cout<<"this in init:"<<endl;
    cout<<this<<endl;
    //*/
}

PlayerShip::PlayerShip(){init();}

void PlayerShip::update() {
    xpos=camx;
    ypos=-camy;

    xvel=velX;  //camera acceleration; this is kind of backwards but oh well
    yvel=velY;

    zrot=-xvel/maxV*36;//90*2/5;
    xrot=-yvel/maxV*36;

    /*
    if(collidesWithNoise()) {
        velX=0;
        velY=0;
    }//*/
}
