#include "playerShip.h"

#include "ModelConstants.h"
#include "math.h"
#include "imports.h"
#include "Model.h"
#include "vec3f.h"

/**
 PlayerShip::PlayerShip(int n)
 Constructor just calls init after super
 */
PlayerShip::PlayerShip(int n) : GameObject(n) {
	init();
}

/**
 void PlayerShip::init()
 Sets the model to the constant playerShipModel, sets the z position to -playerOffset
 */
void PlayerShip::init(){
	model=playerShipModel;
    modelSize=playerShipModel->length;

    zpos=-playerOffset;
}

/**
 void PlayerShip::uniqueRenderAfterPop()
 Draws the targeting reticule
 */
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

    double dist=2;

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
}

/**
 void PlayerShip::update(double dt)
 Calls handleKeyInput(), then sets the velocities to maxV in the direction it's pointing. Uses xvel and yvel to change xpos and ypos. Checks collision detection with enemies and terrain (and eventually projectiles).
 */
void PlayerShip::update(double dt) {
	handleKeyInput(dt);
	
	double vec[3];
	
	getVector(xrot, yrot, vec);
	
	xvel=vec[0]*maxV;
	yvel=vec[1]*maxV;
	zvel=vec[2]*maxV;
	
	xpos+=xvel*dt;
    ypos+=yvel*dt;
	
	xpos=max(min((double)xpos,1.0*noiseScale),-1.0*noiseScale);
	ypos=max(min((double)ypos,1.0*noiseScale),-1.0*noiseScale);

    /*zrot=-xvel/maxV*18;//90*2/5;
    yrot=-xvel/maxV*36;
    xrot=yvel/maxV*36;*/


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
            //xvel=0;
            //xvel=0;
        }
    }
}


/**
 void PlayerShip::handleKeyInput(double dt)
 Rotates in y and x based on the keyboard input
 */
void PlayerShip::handleKeyInput(double dt) {
	if(leftmov){
		yrot+=accel*dt;
	} else if(rightmov){
		yrot-=accel*dt;
	} else {
		if(abs(yrot)-accel*dt>0)
			yrot-=accel*dt*signum(yrot);
		else
			yrot=0;
	}
	if(upmov){
		xrot+=accel*dt;
	} else if(downmov){
		xrot-=accel*dt;
	} else {
		if(abs(xrot)-accel*dt>0)
			xrot-=accel*dt*signum(xrot);
		else
			xrot=0;
	}

	yrot=max(min((double)yrot, angleCap),-angleCap);
	xrot=max(min((double)xrot, angleCap),-angleCap);
}
