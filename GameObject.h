#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "globals.h"

class GameObject
{
public:
    vertex *model;
    float xpos,ypos,zpos,xvel,yvel,zvel;
    float xrot,yrot,zrot;

	GameObject();
	virtual ~GameObject();

	bool collidesWithNoise();
	void render();

	virtual void init();
	virtual void update();
	virtual void uniqueRenderAfterPop();
	virtual void uniqueRender();
	virtual void fireWeapon();
protected:
	int modelSize;
private:
    
    long t;
};

#endif // GAMEOBJECT_H_INCLUDED
