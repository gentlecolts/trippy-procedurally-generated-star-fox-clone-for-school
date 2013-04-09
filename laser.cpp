#include "laser.h"

#include "imports.h"
#include "constants.h"
#include "math.h"
#include "GameObject.h"
#include "camera.h"
using namespace std;

Laser::Laser(double x, double y, double z, double xr, double yr, double zr){
    init(x,y,z,xr,yr,zr);
}

void Laser::init(double x, double y, double z, double xr, double yr, double zr){

    xpos=x;
    ypos=y;
    zpos=z;

    xrot=xr;
    yrot=yr;
    zrot=zr;

	double vect[3];
	getVector(xrot,yrot,vect);

    xvel=0.3*vect[0];
    yvel=0.3*vect[1];
	zvel=0.3*vect[2];

	xpos+=xvel*7;
	ypos+=yvel*7;
	zpos+=zvel*7;
}

void Laser::render() {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos);

    glScalef(objScale,objScale,objScale);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glBegin(GL_QUADS); // of the pyramid

    glColor3f(1,0,0);
    glVertex3f(-.2,0,0);
    glVertex3f(.2,0,0);
    glVertex3f(.2,0,5);
    glVertex3f(-.2,0,5);

    glEnd();

    glDisable(GL_LIGHT1);
    glEnable(GL_LIGHT0);

    glPopMatrix();
}

void Laser::update() {
    xpos+=xvel;
    ypos+=yvel;

    zpos+=zvel;
}

bool Laser::collidesWithObject(GameObject* obj) {
    double xD=xpos-obj->xpos;
    double yD=ypos-obj->ypos;
    double zD=zpos-obj->zpos;
    
    if(sqrt(xD*xD+yD*yD+zD*zD)<obj->avgDist*3) {
        return true;
    }
    
    zD+=5*objScale;
    
    return sqrt(xD*xD+yD*yD+zD*zD)<obj->avgDist*3;
}

bool Laser::collidesWithNoise() {
    const double
        x=xpos/noiseScale *grid2+grid2,
        y=ypos/noiseScale *grid2+grid2,
        z=-d*grid*(zpos/noiseScale+d/2),
        z2=-d*grid*((5*objScale+zpos)/noiseScale+d/2)
    ;
    if(noise[precompindx(x,y,z+zshft)]>tolerance ||
       noise[precompindx(x,y,z2+zshft)]>tolerance){
        return true;
    }
    return false;
}

Laser::~Laser(){}
