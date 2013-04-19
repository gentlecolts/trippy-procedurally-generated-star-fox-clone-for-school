#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "globals.h"

#include <ctime>

class EnemyWave;
class Model;
class Animation;

class GameObject
{
public:
//	vertex *model;
	Model *model;
	float xpos,ypos,zpos,xvel,yvel,zvel;
	float xrot,yrot,zrot;
	double avgDist;
	EnemyWave* parentWave;
	Animation* theAnimation;
	int index;

	virtual void init();

	GameObject(int n);
	virtual ~GameObject();

	bool collidesWithNoise();
	bool collidesWithObject(GameObject *obj);
	void render();
	void doUpdate(double dt);
	void setup();
	void setAnimation(Animation *anim);

	virtual void update(double dt);
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
