#include "playerShip.h"

#include "math.h"
#include "imports.h"

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


    zpos=-playerOffset;
    /*
    cout<<"init()"<<endl;
    cout<<"this in init:"<<endl;
    cout<<this<<endl;
    //*/
}

PlayerShip::PlayerShip(){init();}

void PlayerShip::uniqueRenderAfterPop() {
    glPushMatrix();

	double vect[3];
	getVector(xrot,yrot,vect);

    /*double x=-sin(radians(yrot));
    double y=sin(radians(xrot))*cos(radians(yrot));
	double z=-cos(radians(xrot))*cos(radians(yrot*/

	double x=vect[0];
    double y=vect[1];
	double z=vect[2];

    double dist=1;

    glTranslatef(x*dist+xpos,y*dist+ypos,z*dist+zpos);

    glLineWidth(3);

    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);


    double halfLength=objScale;

    glVertex3f(halfLength,halfLength,0);
    glVertex3f(-halfLength,halfLength,0);
    glVertex3f(-halfLength,halfLength,0);
    glVertex3f(-halfLength,-halfLength,0);
    glVertex3f(-halfLength,-halfLength,0);
    glVertex3f(halfLength,-halfLength,0);
    glVertex3f(halfLength,-halfLength,0);
    glVertex3f(halfLength,halfLength,0);

    glEnd();

    glTranslatef(x*dist,y*dist,z*dist);

    glBegin(GL_LINES);

    glVertex3f(halfLength,halfLength,0);
    glVertex3f(-halfLength,halfLength,0);
    glVertex3f(-halfLength,halfLength,0);
    glVertex3f(-halfLength,-halfLength,0);
    glVertex3f(-halfLength,-halfLength,0);
    glVertex3f(halfLength,-halfLength,0);
    glVertex3f(halfLength,-halfLength,0);
    glVertex3f(halfLength,halfLength,0);

    glEnd();
    glPopMatrix();

    /*glTranslatef(xpos,ypos,zpos);
    glPushMatrix();
    glBegin(GL_LINES);

    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,0.0,0.0);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,1.0,0.0);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,1.0);

    glEnd();

    glPopMatrix();*/
}

void PlayerShip::update() {
	handleKeyInput();

    xpos+=xvel;
    ypos+=yvel;

	xpos=max(min((double)xpos,1.0*noiseScale),-1.0*noiseScale);
	ypos=max(min((double)ypos,1.0*noiseScale),-1.0*noiseScale);

    zrot=-xvel/maxV*18;//90*2/5;
    yrot=-xvel/maxV*36;
    xrot=yvel/maxV*36;


    if(invinceStart<0) {
        bool hit=false;

        for(int i=0;i<gameObjects.size();i++) {
            if(this!=gameObjects.at(i) && collidesWithObject(gameObjects.at(i))) {
                hit=true;
                break;
            }
        }
        if(hit || collidesWithNoise()) {
            invinceStart=clock();
            xvel=0;
            xvel=0;
        }
    }
}

void PlayerShip::handleKeyInput() {
	if(leftmov){
		if(upmov!=downmov){//aka xor operator, deal w/ it
			xvel-=accel*rt2;
		}else{
			xvel-=accel;
		}
	} else if(rightmov){
		if(upmov!=downmov){
			xvel+=accel*rt2;
		}else{
			xvel+=accel;
		}
	} else {
		xvel*=0.8;
	}
	if(upmov){
		if(leftmov!=rightmov){
			yvel+=accel*rt2;
		}else{
			yvel+=accel;
		}
	} else if(downmov){
		if(leftmov!=rightmov){
			yvel-=accel*rt2;
		}else{
			yvel-=accel;
		}
	} else {
		yvel*=.7;
	}

	xvel=max(min((double)xvel, maxV),-maxV);
	yvel=max(min((double)yvel, maxV),-maxV);
}
