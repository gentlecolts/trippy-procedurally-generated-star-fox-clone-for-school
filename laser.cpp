#include "laser.h"

#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>

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

    xvel=sin(xr)*cos(yr);
    yvel=sin(xr)*sin(yr);

    zvel=cos(xr);
}

void Laser::render() {
    glPushMatrix();
    glTranslatef(xpos, ypos, zpos);

    glScalef(0.3f,0.3f,0.3f);
    glRotatef(xrot,1.0,0,0);
    glRotatef(yrot,0.0,1.0,0);

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
    ypos-=yvel;

    zpos+=zvel;
}

Laser::~Laser(){}
