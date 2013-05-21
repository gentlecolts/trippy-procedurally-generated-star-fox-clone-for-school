//
//  Nade.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/5/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "Nade.h"
#include "../ModelConstants.h"
#include "../Model.h"

//sets the model, doesn't start. init() is called later when it's ready to fire.
Grenade::Grenade() : Laser() {
	model=grenadeModel;
	modelSize=grenadeModel->length;

	going=false;
}

//calls init, sets the model, starts the projectile
Grenade::Grenade(Vec3d p, Vec3d v, Vec3d a, double r, long mt) : Laser() {
	init(p, v, a, r, mt);

	model=grenadeModel;
	modelSize=grenadeModel->length;

	going=true;
}

//initializes the grenade
void Grenade::init(Vec3d p, Vec3d v, Vec3d a, double r, long mt) {
	Vec3d vect=Vec3d(
					 cos(radians(v[0]))*sin(radians(v[1])),
					 -sin(radians(v[0])),
					 cos(radians(v[0]))*cos(radians(v[1]))
					 );

	pos=p;
	vel=vect*5;
	rot=v;
	accell=a;
	radius=r;
	maxTime=mt;

	explodeTime=-1;
}

//gets the damage it would deal to another object. 3 before detonation, otherwise dependent on their distance.
int Grenade::getDamage(GameObject *other) {
	if(explodeTime<0 && t<maxTime) {
		return 3;
	}

	Vec3d diff=pos-other->pos;

	return 30/(1+diff.magnitude());
}

//it's done if it's started moving and its offscreen in z
bool Grenade::isDone() {
	return going && (pos[2]<-frameSize*2 || pos[2]>cameraOffset);
}

//if the explosion is on, increase its radius. Otherwise if it has started moving, move it. If it gets close to an enemy or collides with noise, detonate it.
void Grenade::update(double dt) {
	if(going) {
//		cout<<"explodeTime in update: "<<explodeTime<<" "<<this<<endl;
		if(explodeTime<0 && t<maxTime) {
			t+=dt;
//			cout<<"t: "<<t<<endl;
			pos+=vel*dt;
			vel+=accell*dt;

			GameShip *obj=thePlayerShip;
			while(obj!=NULL) {
				Vec3d diff=obj->pos-pos;
				if(obj->player!=player && diff[2]>0 && diff.magnitude()<radius/2) {
					explode();
					break;
				}

				obj=obj->getNext();
			}

			if(collidesWithNoise()) {
				explode();
			}
		} else {
//			cout<<"here? "<<this<<endl;
			pos[2]-=thePlayerShip->vel[2]/4*dt;

			avgDist+=dt*5;

			if(avgDist>=radius) {
//				cout<<"I'm dead! "<<this<<endl;

				destroy();
			}
		}
	}
}

//draws its model normally if the explosion hasn't started; otherwise draws a perturbed circular form that is the actual animation
void Grenade::render() {
//	cout<<"explodeTime: "<<explodeTime<<" "<<this<<endl;
	if(!going || (explodeTime<0 && t<maxTime)) {
		GameObject::render();
	} else {
//		cout<<"drawing?!"<<endl;

		glDisable(GL_LIGHTING);

		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2]);

		glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
		glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
		glRotatef(rot[2], 0.0f, 0.0f, 1.0f);

		glScalef(objScale, objScale, objScale);

		glColor4f(1.0, 0.0, 0.0, avgDist/radius);
		
		glBegin(GL_TRIANGLE_FAN);

		glVertex3d(0,0,0);

		for(int i=0;i<=10;i++) {
			glColor4f(1.0, ((double)rand())/RAND_MAX*1.0, ((double)rand())/RAND_MAX*0.5, avgDist/radius);
			glVertex3d(avgDist*cos(pi/5*i)+((double)rand())/RAND_MAX*10-5, avgDist*sin(pi/5*i)+((double)rand())/RAND_MAX*10-5,0);
		}

		glEnd();

		glPopMatrix();

		glEnable(GL_LIGHTING);
	}
}

//starts the motion; this allows it to go from sitting on a rocket launcher as a component to being a projectile
void Grenade::activate() {
	t=0;
	going=true;
}

//starts the explosion
void Grenade::explode() {
//	cout<<"exploding! "<<this<<endl;

	explodeTime=SDL_GetTicks();

//	cout<<"explodeTime 2: "<<explodeTime<<endl;
}
