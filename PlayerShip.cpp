#include "playerShip.h"

#include "ModelConstants.h"
#include "math.h"
#include "imports.h"
#include "Model.h"
#include "Vec3d.h"
#include "HelloSDL/BasicGun.h"
#include "gameController.h"
#include "HelloSDL/BasicStrut.h"
#include "HelloSDL/RotateStrut.h"
#include "HelloSDL/FanStrutThing.h"
#include "HelloSDL/AimingStrut.h"
#include "HelloSDL/BasicRocketLauncher.h"

/**
 PlayerShip::PlayerShip(int n)
 Constructor just calls init after super
 */
PlayerShip::PlayerShip() : GameShip() {
	init();
}

char* PlayerShip::getType(){return "PlayerShip";}

/**
 void PlayerShip::init()
 Sets the model to the constant playerShipModel, sets the z position to -playerOffset, sets health to playerHP, and that it is on the player side
 */
void PlayerShip::init(){
	model=playerShipModel;
    modelSize=model->length;
	player=true;

    pos[2]=-playerOffset;
}

/**
 void PlayerShip::uniqueRenderAfterPop()
 Draws the targeting reticule and the health bar
 */
void PlayerShip::uniqueRenderAfterPop() {
    glPushMatrix();

	glDisable(GL_LIGHTING);

	Vec3d vect=getVector(rot[0],rot[1]);

	double x=vect[0];
    double y=vect[1];
	double z=vect[2];

    double dist=2;

    glTranslatef(x*dist+pos[0],y*dist+pos[1],z*dist+pos[2]);

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

	glPushMatrix();
	glTranslatef(-.7+pos[0],1+pos[1],pos[2]);

	glBegin(GL_QUADS);
	glColor3f(((double)max(0,playerHP-health))/playerHP, 1+((double)(health-playerHP))/playerHP, 0.3);
	glVertex3d(-0.2, 0.05,1);
	glVertex3d(0.2-(playerHP-(double)health)/playerHP*0.4, 0.05,1);
	glVertex3d(0.3-(playerHP-(double)health)/playerHP*0.5, -0.05,1);
	glVertex3d(-0.2, -.05,1);
	glEnd();

	glEnable(GL_LIGHTING);

	glPopMatrix();
}

/**
 void PlayerShip::afterSetup()
 Sets up the guns: two forward and a rocket launcher also forward but a bit up
 */
void PlayerShip::afterSetup() {
	addChild(new BasicStrut(this, basicStrutModel), 0, Vec3d(0,180,0));
	children[0]->addChild(new BasicStrut(children[0], basicStrutModel), 5);
	children[0]->children[5]->addChild(new BasicRocketLauncher(children[0]->children[5]), 5);
	children[0]->addChild(new BasicGun(children[0]), 0);

	addChild(new BasicStrut(this, basicStrutModel), 1, Vec3d(0,180,0));
		children[1]->addChild(new BasicGun(children[1]), 0);


	health=playerHP;
}

/**
 void PlayerShip::update(double dt)
 Calls handleKeyInput(), then sets the velocities to maxV in the direction it's pointing. Uses the velocities to rotate the ship. Checks collision detection with enemies and terrain and projectiles. Ends the game if the player dies
 */
void PlayerShip::update(double dt) {
	handleKeyInput(dt);

	Vec3d vec=getVector(rot[0], rot[1]);

	vel=vec*maxV;

	pos[0]+=vel[0]*dt;
    pos[1]+=vel[1]*dt;

	pos[0]=max(min((double)pos[0],1.0*frameSize),-1.0*frameSize);
	pos[1]=max(min((double)pos[1],1.0*frameSize),-1.0*frameSize);


    if(invinceStart<0) {
        bool hit=false;

		GameShip *obj=getNext();
		while(obj!=NULL) {
			if(collidesWithObject(obj)) {
                hit=true;
                break;
            }

			obj=obj->getNext();
		}

		GameShip *las=enemyLasers;
		while(las!=NULL) {
			if(las->collidesWithObject(this)) {
				hit=true;

				break;
			}

			las=las->getNext();
		}

        if(hit || collidesWithNoise()) {
            invinceStart=clock();

			if(hit) {
				if(obj!=NULL) {
					health-=obj->getDamage(this);
				}
				if(las!=NULL) {
					health-=las->getDamage(this);
				}
			} else {
				health-=3;
			}
        }

		if(health<0) {
			needToUnload=true;
		}
    }
}


/**
 void PlayerShip::handleKeyInput(double dt)
 Rotates in y and x based on the keyboard input, and fires the lasers and/or the rocket launcher
 */
void PlayerShip::handleKeyInput(double dt) {
	if(leftmov){
		rot[1]+=accel*dt;
	} else if(rightmov){
		rot[1]-=accel*dt;
	} else {
		if(abs(rot[1])-accel*dt>0)
			rot[1]-=accel*dt*signum(rot[1]);
		else
			rot[1]=0;
	}
	if(upmov){
		rot[0]+=accel*dt;
	} else if(downmov){
		rot[0]-=accel*dt;
	} else {
		if(abs(rot[0])-accel*dt>0)
			rot[0]-=accel*dt*signum(rot[0]);
		else
			rot[0]=0;
	}
	if(fire) {
		fireWeapon();
	}
	if(fireRockets) {
		fireBigGuns();
	}

	rot[1]=max(min((double)rot[1], angleCap),-angleCap);
	rot[0]=max(min((double)rot[0], angleCap),-angleCap);
}
