#ifndef LASER_H_INCLUDED
#define LASER_H_INCLUDED

#include "gameShip.h"

class Laser : public GameShip
{
public:
	Laser(Vec3d p, Vec3d a);

	void init(Vec3d p, Vec3d a);
	void update(double dt);
	void uniqueRenderFirst();
	void uniqueRenderLast();
	//void render();
    //bool collidesWithObject(GameObject* obj);
    //bool collidesWithNoise();
	bool isDone();
};

#endif // LASER_H_INCLUDED
