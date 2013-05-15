//#import "GLHelper.h"
#include "GLHelper.h"

#include <SDL/SDL.h>
#include <iostream>

#include "constants.h"
#include "globals.h"

using namespace std;

///libsdl.org/docs/html/guidevideoopengl.html
///http://www.sdltutorials.com/sdl-opengl-tutorial-basics
///http://www710.univ-lyon1.fr/~jciehl/Public/OpenGL_PG/index.html
///http://www.opengl.org/sdk/docs/man2/xhtml/glLightModel.xml

void glPreInit(){
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);//must be power of 2 for anti aliasing
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	/*
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,8);
	//*/

	/*
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);//Anti aliasing
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,2);//how much antialiasing
	//*/
}

void glInit(){


	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	glClearColor(0,0,0,0);

	glViewport(0,0,xmax,ymax);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//const float rar=(float)xmax/(float)ymax;
	//gluPerspective(viewangle,rar,1.0,1024.0);
	//gluPerspective(viewangle,1,1.0,-1);
	//glOrtho(0,xmax,ymax,0,1,-1);
	//glFrustum(0,xmax,ymax,0,d,2);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();

	GLenum error=glGetError();
	if(error!=GL_NO_ERROR){
		//printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		cout<<"Error initializing OpenGL! "<<gluErrorString(error)<<endl;
		exit(0x91d13d);//gl died );
	}
}

void drawquad(point3d p[4]){
	//glBegin(GL_QUADS);
	glVertex3d(p[0].x,p[0].y,p[0].z);
	glVertex3d(p[1].x,p[1].y,p[1].z);
	glVertex3d(p[2].x,p[2].y,p[2].z);
	glVertex3d(p[3].x,p[3].y,p[3].z);
	//glEnd();
}

void initLights() {
	//GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat mat_diffuse[] = { 100, 100, 100/*-curTime/100*/, 1.0 };
//	cout<<"val: "<<(100-curTime/100)<<endl;
	GLfloat light_position[] = {0,0,4,1};
	glShadeModel(GL_SMOOTH);
	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,1);
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.125);
	
	glEnable(GL_LIGHT0);
	
	
	light1[0]=0;
    light1[1]=0;
    light1[2]=-1.5;
    light1[3]=1;
	
	GLfloat diffuse[]={3.0,0.0,0.0,1.0};
	
    glLightfv(GL_LIGHT1, GL_POSITION, light1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.125);
	
	glEnable(GL_LIGHT1);
}

void drawquad(){
	//glBegin(GL_QUADS);
	/*
	glColor3f(1,1,1);glVertex3d(face[0].x,face[0].y,face[0].z);
	glColor3f(1,1,1);glVertex3d(face[1].x,face[1].y,face[1].z);
	glColor3f(1,1,1);glVertex3d(face[2].x,face[2].y,face[2].z);
	glColor3f(1,1,1);glVertex3d(face[3].x,face[3].y,face[3].z);
	/*/
	glVertex3d(face[0].x,face[0].y,face[0].z);
	glVertex3d(face[1].x,face[1].y,face[1].z);
	glVertex3d(face[2].x,face[2].y,face[2].z);
	glVertex3d(face[3].x,face[3].y,face[3].z);
	//*/
	//glEnd();
}

//x,y,and z are the center NOT a corner
void drawCube(double x,double y,double z,double wid){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(camx,camy,0);
}

void drawRect3d(double x,double y,double z,double dx,double dy,double dz){

}
