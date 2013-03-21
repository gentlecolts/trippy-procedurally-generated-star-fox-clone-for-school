#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Laser.h"
vector<Laser> lasers;
void addLaser(Laser las) {      //THIS NEEDS TO BE ELSEWHERE BUT FKING IMPORTS
    lasers.push_back(las);
}

struct vertex{
	float x,y,z;
	float r,g,b;

	vertex(float x2=0,float y2=0,float z2=0,float r2=0,float g2=0,float b2=0){
		x=x2;
		y=y2;
		z=z2;
		r=r2;
		g=g2;
		b=b2;
	}
};

GLfloat light1[4];

class GameObject
{
public:
    vertex *model;
    float xpos,ypos,zpos,xvel,yvel,zvel;
    float xrot,yrot,zrot;

    virtual void init(){}
	GameObject(){
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

	void render(){
		glPushMatrix();
		glTranslatef(xpos, ypos, zpos);

		glScalef(0.3f,0.3f,0.3f);
		glRotatef(xrot, 0.0f, 0.0f, 1.0f);
		glRotatef(yrot, 1.0f, 0.0f, 0.0f);
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
        glEnable(GL_LIGHT1);
		glBegin(GL_TRIANGLES); // of the pyramid

		for(int i=0;i<modelSize;i++) {
			glColor3f(model[i].r,model[i].g,model[i].b);
			glVertex3f(model[i].x,model[i].y,model[i].z);
		}

		glEnd();

		glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT0);

        glPopMatrix();
	}
	~GameObject(){delete[] model;}

	virtual void update() {

	}

	virtual void fireWeapon() {
	    addLaser(Laser(xpos,ypos,zpos-.5,xrot,yrot,zrot));
	}

	bool collidesWithNoise() {      //super-slow hacky version
        for(int i=0;i<modelSize;i++) {
            if(noise[precompindex(xpos+model[i].x*0.3,ypos+model[i].y*0.3,zpos+model[i].z*0.3+zshift)])
                return true;
        }
        return false;
	}
protected:
	int modelSize;
private:
};

#endif // GAMEOBJECT_H_INCLUDED
