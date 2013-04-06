#include "gameObject.h"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "camera.h"
#include "GLHelper.h"
#include "gameController.h"

#include <iostream>

GameObject::GameObject() {
		//model=&playerModel;
		//modelSize=0;
		init();

		light1[0]=0;
		light1[1]=0;
		light1[2]=-1.5;
		light1[3]=1;

		glLightfv(GL_LIGHT1, GL_POSITION, light1);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.125);
}

void GameObject::render() {
		glPushMatrix();
		glTranslatef(xpos, ypos, zpos);

		glScalef(0.3f,0.3f,0.3f);
		glRotatef(xrot, 1.0f, 0.0f, 0.0f);
		glRotatef(zrot, 0.0f, 0.0f, 1.0f);
		//glRotatef(-90, 1.0f, 0.0f, 0.0f);
		/*
		cout<<"model:"<<endl;
		cout<<model<<endl;
		cout<<"model size:"<<endl;
		cout<<modelSize<<endl;
		cout<<"this:"<<endl;
		cout<<this<<endl;
		//*/

		glDisable(GL_LIGHT0);
		//glEnable(GL_LIGHT1);
		glBegin(GL_TRIANGLES); // of the pyramid

		for(int i=0;i<modelSize;i++) {
			glColor3f(model[i].r,model[i].g,model[i].b);
			glVertex3f(model[i].x,model[i].y,model[i].z);
		}

		glEnd();

		//glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);

		glPopMatrix();
}

bool GameObject::collidesWithNoise() {
    bool fuck=false;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for(int i=0;i<modelSize;i++) {
        const double
            x=(model[i].x+xpos)*0.3 *grid2+grid2,
            y=(model[i].y+ypos)*0.3 *grid2+grid2,
            z=-d*grid*((model[i].z+zpos)*0.3+d/2);
        //cout<<x<<'\t'<<y<<'\t'<<z<<endl;
        if(noise[precompindx(x,y,z+zshft)]>tolerance){
            glBegin(GL_QUADS);
            glColor3f(1.0f,0,0);

            point3d corners[8];
            int indx;
            for(int i=-1;i<=1;i+=2){
            for(int j=-1;j<=1;j+=2){
            for(int k=-1;k<=1;k+=2){
                indx=((k+1)<<1)|(j+1)|((i+1)>>1);//acceptable because these are each either 0 or 2
                corners[indx].x=(x+i*delt2-grid2)/grid2;
                corners[indx].y=(y+j*delt2-grid2)/grid2;
                corners[indx].z=-(z+k*delt2)/(d*grid)-d/2;

                cout<<"some shit "<<corners[indx].x<<'\t'<<corners[indx].y<<'\t'<<corners[indx].z<<endl;
            }}}

            drawquad(corners[0],corners[1],corners[3],corners[2]);
            drawquad(corners[0],corners[1],corners[5],corners[4]);
            drawquad(corners[0],corners[2],corners[6],corners[4]);
            drawquad(corners[3],corners[2],corners[6],corners[7]);
            drawquad(corners[3],corners[1],corners[5],corners[7]);
            drawquad(corners[6],corners[4],corners[5],corners[7]);

            glEnd();
            //return true;
            fuck=true;
        }
    }
    //return false;
    return fuck;
}

void GameObject::init(){}
void GameObject::update(){}

void GameObject::fireWeapon() {
    addLaser(Laser(xpos,ypos,zpos-.5,xrot,yrot,zrot));
}

GameObject::~GameObject() {
    delete[] model;
}
