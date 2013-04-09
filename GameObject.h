#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "globals.h"

class EnemyWave;

class GameObject
{
public:
    vertex *model;
    float xpos,ypos,zpos,xvel,yvel,zvel;
    float xrot,yrot,zrot;
    double avgDist;
    EnemyWave *parentWave=NULL;

	GameObject();
	virtual ~GameObject();

	bool collidesWithNoise();
    bool collidesWithObject(GameObject *obj);
	void render();
    void doUpdate();
    void setup();

	virtual void init();
	virtual void update();
	virtual void uniqueRenderAfterPop();
	virtual void uniqueRender();
	virtual void fireWeapon();
    virtual bool isDone();
protected:
	int modelSize;
    long invinceStart=-1;
private:
    long t;
    bool didSetup=false;
};

#endif // GAMEOBJECT_H_INCLUDED
