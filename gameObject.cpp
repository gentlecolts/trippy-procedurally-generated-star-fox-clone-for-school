#include "gameObject.h"

#include "imports.h"

#include "camera.h"
#include "GLHelper.h"
#include "gameController.h"

#include <iostream>

/*
GameObject::GameObject() {
		init();
}
//*/

void GameObject::render() {
	glPushMatrix();
	glTranslatef(xpos, ypos, zpos);

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

	glScalef(objScale,objScale,objScale);

	glDisable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glBegin(GL_TRIANGLES); // of the pyramid

    if(invinceStart>=0)
        glColor3f(1.0,0,0);

	for(int i=0;i<modelSize;i++) {
        if(invinceStart<0)
            glColor3f(model[i].r,model[i].g,model[i].b);
		glVertex3f(model[i].x,model[i].y,model[i].z);
	}

	glEnd();

	uniqueRender();

	//glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);

	glPopMatrix();

	uniqueRenderAfterPop();
}

void GameObject::doUpdate() {
    if(!didSetup)
        setup();

    if(invinceStart>=0 && clock()-invinceStart>invinceLength) {
        invinceStart=-1;
    }

    update();
}

void GameObject::setup() {
    didSetup=true;

    avgDist=0;
    for(int i=0;i<modelSize;i++) {
        avgDist+=abs(model[i].x);
        avgDist+=abs(model[i].y);
        avgDist+=abs(model[i].z);
    }
    avgDist/=3*modelSize;
    avgDist*=objScale;
}

bool GameObject::collidesWithNoise() {
    for(int i=0;i<modelSize;i++) {
        const double
            x=(model[i].x*objScale+xpos)/noiseScale *grid2+grid2,
            y=(model[i].y*objScale+ypos)/noiseScale *grid2+grid2,
            z=-d*grid*((model[i].z*objScale+zpos)/noiseScale+d/2);
        if(noise[precompindx(x,y,z+zshft)]>tolerance){
            return true;
        }
    }
    return false;
}

bool GameObject::collidesWithObject(GameObject* obj) {      //crappy method
    double xD=xpos-obj->xpos;
    double yD=ypos-obj->ypos;
    double zD=zpos-obj->zpos;

    return sqrt(xD*xD+yD*yD+zD*zD)<avgDist+obj->avgDist;
}

void GameObject::init(){}
void GameObject::update(){}
void GameObject::uniqueRender(){}
void GameObject::uniqueRenderAfterPop(){}
bool GameObject::isDone(){return false;}

void GameObject::fireWeapon() {
    addLaser(new Laser(xpos,ypos,zpos,xrot,yrot,zrot));
}

GameObject::~GameObject() {
    delete[] model;
}
