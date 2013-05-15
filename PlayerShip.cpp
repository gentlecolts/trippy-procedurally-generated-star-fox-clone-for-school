#include "playerShip.h"

#include "ModelConstants.h"
#include "math.h"
#include "imports.h"
#include "Model.h"
#include "Vec3d.h"
#include "BasicGun.h"
#include "gameController.h"
#include "BasicStrut.h"
#include "RotateStrut.h"
#include "FanStrutThing.h"
#include "AimingStrut.h"
#include "BasicRocketLauncher.h"

/**
 PlayerShip::PlayerShip(int n)
 Constructor just calls init after super
 */
PlayerShip::PlayerShip(int n) : GameShip(n) {
	init();
}

/**
 void PlayerShip::init()
 Sets the model to the constant playerShipModel, sets the z position to -playerOffset
 */
void PlayerShip::init(){
	model=playerShipModel;
    modelSize=model->length;
	player=true;
	health=10;

    pos[2]=-playerOffset;
}

/**
 void PlayerShip::uniqueRenderAfterPop()
 Draws the targeting reticule
 */
void PlayerShip::uniqueRenderAfterPop() {
    glPushMatrix();

	Vec3d vect=getVector(rot[0],rot[1]);

    /*double x=-sin(radians(yrot));
    double y=sin(radians(xrot))*cos(radians(yrot));
	double z=-cos(radians(xrot))*cos(radians(yrot*/

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
}

void PlayerShip::afterSetup() {
//	addChild(new FanStrut(this, 1, basicStrutModel), 0);
//	addChild(new FanStrut(this, 1, basicStrutModel), 1);
	
	//addChild(new RotateStrut(this,longStrutModel, Vec3d(30,-70,360),Vec3d(-30,0,-360), 0.5), 0);
	//children[0]->addChild(new BasicGun(children[0]), 1);
	
	//	for(int i=0;i<model->numAttachPoints;i++) {
	addChild(new BasicStrut(this, basicStrutModel), 0, Vec3d(0,180,0));	//???
//		addChild(new AimingStrut(this, 9000, basicStrutModel), 0);
	children[0]->addChild(new BasicRocketLauncher(children[0]), 0);
	addChild(new BasicStrut(this, basicStrutModel), 1, Vec3d(0,180,0));	//???
		children[1]->addChild(new BasicGun(children[1]), 0);
//	}
}

/**
 void PlayerShip::update(double dt)
 Calls handleKeyInput(), then sets the velocities to maxV in the direction it's pointing. Uses xvel and yvel to change xpos and ypos. Checks collision detection with enemies and terrain (and eventually projectiles).
 */
void PlayerShip::update(double dt) {
	handleKeyInput(dt);
	
	Vec3d vec=getVector(rot[0], rot[1]);
	
	vel=vec*maxV;
	
	pos[0]+=vel[0]*dt;
    pos[1]+=vel[1]*dt;
	
	pos[0]=max(min((double)pos[0],1.0*noiseScale),-1.0*noiseScale);
	pos[1]=max(min((double)pos[1],1.0*noiseScale),-1.0*noiseScale);


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
			
            //xvel=0;
            //xvel=0;
        }
		
		if(health<0) {
			needToUnload=true;
		}
    }
}

void PlayerShip::doFire() {
//	addLaser(new Laser(pos,rot),player);
}


/**
 void PlayerShip::handleKeyInput(double dt)
 Rotates in y and x based on the keyboard input
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
