#include "laser.h"

#include "imports.h"
#include "constants.h"
#include "math.h"
#include "camera.h"
#include "ModelConstants.h"
#include "Model.h"
using namespace std;

#define laserSpeed 15

/**
 Laser::Laser(double x, double y, double z, double xr, double yr, double zr)
 Calls init
 */
Laser::Laser(Vec3d p, Vec3d a) : GameShip(0){
	model=laserModel;
	modelSize=laserModel->length;
    init(p, a);
}

/**
 void Laser::init(double x, double y, double z, double xr, double yr, double zr)
 Sets the position to the given position, the rotation to the given rotation, and calculates the velocity based on the rotation, then moves forward slightly so it doesn't clip out of the back of objects firing it
 */
void Laser::init(Vec3d p, Vec3d a){

    pos=p;

    rot=a;

	//Vec3d vect=getVector(xrot,yrot);
	
	Vec3d vect=Vec3d(0,0,-1);
	vect=rotate(vect,Vec3d(1,0,0),rot[0]);
	vect=rotate(vect,Vec3d(0,1,0),rot[0]);
	vect=rotate(vect,Vec3d(0,0,1),rot[0]);

    vel=laserSpeed*vect;
}

void Laser::uniqueRenderFirst() {
	GameShip::uniqueRenderFirst();
	
	glDisable(GL_LIGHTING);
}

void Laser::uniqueRenderLast() {
	glEnable(GL_LIGHTING);
	
	GameShip::uniqueRenderLast();
}

/**
 void Laser::render()
 Draws a red quad at its position; will be improved later.
 */
/*void Laser::render() {
	
	glDisable(GL_LIGHTING);
	glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);

    glScalef(objScale,objScale,objScale);
	glRotatef(rot[0], 0.0f, 0.0f, 1.0f);
	glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rot[2], 1.0f, 0.0f, 0.0f);

    glDisable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    glBegin(GL_QUADS); // of the pyramid

    glColor4f(1,.3,.3,0.7);
	glTexCoord2f(28, 4);
    glVertex3f(-.2,0,0);
	glTexCoord2f(36, 4);
    glVertex3f(.2,0,0);
	glTexCoord2f(28, 58);
    glVertex3f(.2,0,-5);
	glTexCoord2f(36, 58);
    glVertex3f(-.2,0,-5);

    glEnd();

    //glDisable(GL_LIGHT1);
    glEnable(GL_LIGHT0);

    glPopMatrix();
	glEnable(GL_LIGHTING);
}*/

bool Laser::isDone() {
	return (collidesWithNoise() || pos[2]<-noiseScale*2 || pos[2]>cameraOffset);
}

/**
 void Laser::update(double dt)
 Move by xvel, yvel, and zvel
 */
void Laser::update(double dt) {
	pos+=vel*dt;
}

/**
 bool Laser::collidesWithObject(GameObject* obj)
 Performs collision detection by checking against a sphere with radius equal to the average distance of each vertex of the object's model from the front and back of the laser
 */
/*bool Laser::collidesWithObject(GameObject* obj) {
	Vec3d d=pos-obj->pos;
    
    if(sqrt(d[0]*d[0]+d[1]*d[1]+d[2]*d[2])<obj->avgDist*3) {
        return true;
    }
    
    d[2]-=5*objScale;
    
    return sqrt(d[0]*d[0]+d[1]*d[1]+d[2]*d[2])<obj->avgDist*3;
}*/

/**
 bool Laser::collidesWithNoise()
 Does collision detection with the noise by checking at the front and back of the laser
 */
/*bool Laser::collidesWithNoise() {
    const double
        x=pos[0]/noiseScale *grid2+grid2,
        y=pos[1]/noiseScale *grid2+grid2,
        z=-d*grid*(pos[2]/noiseScale+d/2),
        z2=-d*grid*((-5*objScale+pos[2])/noiseScale+d/2)
    ;
    if(noise[precompindx(x,y,z+zshft)]>tolerance ||
       noise[precompindx(x,y,z2+zshft)]>tolerance){
        return true;
    }
    return false;
}*/
