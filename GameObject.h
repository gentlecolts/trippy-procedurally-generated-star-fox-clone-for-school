#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "globals.h"

#include <ctime>//i dont give a fuck if xcode does shit for you, lrn 2 include...
//this was needed in 3 other files too...i was just going to paste the above line in all of them and not tell you,
//but i decided that was a bit more cruel than i felt like being
//you're welcome
//p.s. its your fault if this fucks something up

class EnemyWave;

class GameObject
{
public:
	vertex *model;
	float xpos,ypos,zpos,xvel,yvel,zvel;
	float xrot,yrot,zrot;
	double avgDist;
	EnemyWave* parentWave;

	virtual void init();

	GameObject():parentWave(NULL),invinceStart(-1),didSetup(false){init();}
	virtual ~GameObject();

	bool collidesWithNoise();
	bool collidesWithObject(GameObject *obj);
	void render();
	void doUpdate();
	void setup();

	virtual void update();
	virtual void uniqueRenderAfterPop();
	virtual void uniqueRender();
	virtual void fireWeapon();
	virtual bool isDone();
protected:
	int modelSize;
	long invinceStart;
private:
	long t;
	bool didSetup;
};
#endif // GAMEOBJECT_H_INCLUDED
