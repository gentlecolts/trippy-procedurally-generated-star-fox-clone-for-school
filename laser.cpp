#include "laser.h"

#include "imports.h"
#include "constants.h"
#include "math.h"
#include "GameObject.h"
#include "camera.h"
using namespace std;

#define laserSpeed 15

/**
 Laser::Laser(double x, double y, double z, double xr, double yr, double zr)
 Calls init
 */
Laser::Laser(double x, double y, double z, double xr, double yr, double zr){
    init(x,y,z,xr,yr,zr);
}

/**
 void Laser::init(double x, double y, double z, double xr, double yr, double zr)
 Sets the position to the given position, the rotation to the given rotation, and calculates the velocity based on the rotation, then moves forward slightly so it doesn't clip out of the back of objects firing it
 */
void Laser::init(double x, double y, double z, double xr, double yr, double zr){

    xpos=x;
    ypos=y;
    zpos=z;

    xrot=xr;
    yrot=yr;
    zrot=zr;

	Vec3d vect=getVector(xrot,yrot);

    xvel=laserSpeed*vect[0];
    yvel=laserSpeed*vect[1];
	zvel=laserSpeed*vect[2];

	xpos+=xvel*5*0.02;
	ypos+=yvel*5*0.02;
	zpos+=zvel*5*0.02;
}

/**
 void Laser::render()
 Draws a red quad at its position; will be improved later.
 */
void Laser::render() {
	
	glDisable(GL_LIGHTING);
	glPushMatrix();
    glTranslatef(xpos, ypos, zpos);

    glScalef(objScale,objScale,objScale);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

    glDisable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    glBegin(GL_QUADS); // of the pyramid

    glColor4f(1,.3,.3,0.7);
	glTexCoord2f(28, 4);
    glVertex3f(-.2,0,0);
	glTexCoord2f(36, 4);
    glVertex3f(.2,0,0);
	glTexCoord2f(28, 58);
    glVertex3f(.2,0,5);
	glTexCoord2f(36, 58);
    glVertex3f(-.2,0,5);

    glEnd();

    //glDisable(GL_LIGHT1);
    glEnable(GL_LIGHT0);

    glPopMatrix();
	glEnable(GL_LIGHTING);
}

/**
 void Laser::update(double dt)
 Move by xvel, yvel, and zvel
 */
void Laser::update(double dt) {
    xpos+=xvel*dt;
    ypos+=yvel*dt;

    zpos+=zvel*dt;
}

/**
 bool Laser::collidesWithObject(GameObject* obj)
 Performs collision detection by checking against a sphere with radius equal to the average distance of each vertex of the object's model from the front and back of the laser
 */
bool Laser::collidesWithObject(GameObject* obj) {
    double xD=xpos-obj->pos[0];
    double yD=ypos-obj->pos[1];
    double zD=zpos-obj->pos[2];
    
    if(sqrt(xD*xD+yD*yD+zD*zD)<obj->avgDist*3) {
        return true;
    }
    
    zD+=5*objScale;
    
    return sqrt(xD*xD+yD*yD+zD*zD)<obj->avgDist*3;
}

/**
 bool Laser::collidesWithNoise()
 Does collision detection with the noise by checking at the front and back of the laser
 */
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
