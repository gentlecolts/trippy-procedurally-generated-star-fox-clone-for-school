#include "laser.h"

#include "imports.h"
#include "constants.h"
#include "math.h"
#include "camera.h"
#include "ModelConstants.h"
#include "Model.h"
using namespace std;

#define laserSpeed 15

Laser::Laser() : GameShip() {
}

char* Laser::getType(){return "Laser";}

/**
 Laser::Laser(double x, double y, double z, double xr, double yr, double zr)
 Calls init
 */
Laser::Laser(Vec3d p, Vec3d a) : GameShip(){
	model=laserModel;
	modelSize=laserModel->length;
    init(p, a);
}

/**
 void Laser::init(double x, double y, double z, double xr, double yr, double zr)
 Sets the position to the given position, the rotation to the given rotation, and calculates the velocity based on the rotation
 */
void Laser::init(Vec3d p, Vec3d a){

    pos=p;

    rot=a;

	Vec3d vect=Vec3d(
					 cos(radians(rot[0]))*sin(radians(rot[1])),
					 -sin(radians(rot[0])),
					 cos(radians(rot[0]))*cos(radians(rot[1]))
					 );

    vel=laserSpeed*vect;
}

//Turns off lighting so the lasers are easy to see; we could have just given it an emissive component to the material, but we didn't know that son enough
void Laser::uniqueRenderFirst() {

	GameShip::uniqueRenderFirst();

	glDisable(GL_LIGHTING);
}

//Turns on lighting so the things drawn later look pretty
void Laser::uniqueRenderLast() {
	glEnable(GL_LIGHTING);

	GameShip::uniqueRenderLast();
}

//Lasers are done when they hit the terrain or go too far away
bool Laser::isDone() {
	return (collidesWithNoise() || pos[2]<-frameSize*2 || pos[2]>cameraOffset);
}

/**
 void Laser::update(double dt)
 Move by xvel, yvel, and zvel
 */
void Laser::update(double dt) {
	pos+=vel*dt;
}
