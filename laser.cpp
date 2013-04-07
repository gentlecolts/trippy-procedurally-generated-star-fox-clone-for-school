#include "laser.h"

#include "imports.h"
#include "constants.h"
#include "math.h"
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

    glScalef(0.3f,0.3f,0.3f);
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

Laser::~Laser(){}
