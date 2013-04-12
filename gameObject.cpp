#include "gameObject.h"

#include "imports.h"

#include "camera.h"
#include "GLHelper.h"
#include "gameController.h"
#include "Model.h"
#include "vec3f.h"
#include "Animation.h"

#include <iostream>


GameObject::GameObject(int n) {
	parentWave=NULL;
	invinceStart=-1;
	didSetup=false;
	init();
	index=n;
	avgDist=-100;
}


void GameObject::render() {
	glPushMatrix();
	glTranslatef(xpos, ypos, zpos);

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

	glScalef(objScale,objScale,objScale);

	glDisable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	if(theAnimation==NULL)
		glBegin(GL_TRIANGLES); // of the pyramid

    if(invinceStart>=0)
        glColor3f(1.0,0,0);

	for(int i=0;i<modelSize;i++) {
		if(i%3==0 && theAnimation!=NULL) {
			glPushMatrix();
			theAnimation->doTriangleTransform(i);
			glBegin(GL_TRIANGLES);
		} else if(i%3==0) {
			glNormal3f(model->normals[i/3][0], model->normals[i/3][1], model->normals[i/3][2]);
		}
		
        if(invinceStart<0)
            glColor3f(model->colors[i][0],model->colors[i][1],model->colors[i][2]);
		glVertex3f(model->vertices[i][0],model->vertices[i][1],model->vertices[i][2]);
		
		if(i%3==2 && theAnimation!=NULL) {
			glEnd();
			glPopMatrix();
		}
	}
	
	if(theAnimation==NULL)
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
	
	if(theAnimation!=NULL)
		theAnimation->tick();

    if(invinceStart>=0 && clock()-invinceStart>invinceLength) {
        invinceStart=-1;
    }

    update();
}

void GameObject::setup() {
    didSetup=true;
	
    avgDist=0;
    for(int i=0;i<modelSize;i++) {
		for(int j=0;j<3;j++) {
			avgDist+=abs(model->vertices[i][j]);
		}
    }
    avgDist/=3*modelSize;
    avgDist*=objScale;
}

bool GameObject::collidesWithNoise() {
    for(int i=0;i<modelSize;i++) {
        const double
            x=(model->vertices[i][0]*objScale+xpos)/noiseScale *grid2+grid2,
            y=(model->vertices[i][1]*objScale+ypos)/noiseScale *grid2+grid2,
            z=-d*grid*((model->vertices[i][2]*objScale+zpos)/noiseScale+d/2);
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
	
	if(sqrt(xD*xD+yD*yD+zD*zD)<avgDist+obj->avgDist)
		cout<<"dists: "<<sqrt(xD*xD+yD*yD+zD*zD)<<","<<avgDist<<","<<obj->avgDist<<endl;

    return sqrt(xD*xD+yD*yD+zD*zD)<avgDist+obj->avgDist;
}

void GameObject::init(){
	theAnimation=NULL;
}
void GameObject::update(){}
void GameObject::uniqueRender(){}
void GameObject::uniqueRenderAfterPop(){}
bool GameObject::isDone(){return false;}

void GameObject::fireWeapon() {
    addLaser(new Laser(xpos,ypos,zpos,xrot,yrot,zrot));
}

GameObject::~GameObject() {
	delete theAnimation;
    delete model;
}
