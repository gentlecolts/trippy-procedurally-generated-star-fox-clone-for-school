#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "globals.h"

#include <ctime>
#include "vec3f.h"

class EnemyWave;
class Model;
class Animation;

class GameObject
{
public:
	Model *model;
	//float xpos,ypos,zpos,xvel,yvel,zvel;
	Vec3f pos,vel,rot;
	bool *attachPointsFilled;
	//float xrot,yrot,zrot;
	double avgDist;
	Animation* theAnimation;
	int numChildren;
	
	GameObject *parent;
	GameObject** children;

	virtual void init();

	GameObject();
	virtual ~GameObject();

	bool collidesWithNoise();
	bool collidesWithObject(GameObject *obj);
	void render();
	void doUpdate(double dt);
	void setup();
	void setAnimation(Animation *anim);
	Vec3f absolutePosition();
	Vec3f absoluteAngle();
	
	virtual void destroy();
	virtual void update(double dt);
	virtual void uniqueRenderAfterPop();
	virtual void uniqueRender();
	virtual void uniqueRenderFirst();
	virtual void uniqueRenderLast();
	virtual void fireWeapon();
	virtual bool isDone();
	virtual void addChild(GameObject *child);
	virtual void afterSetup();
protected:
	int modelSize;
	long invinceStart;
private:
	long t;
	bool didSetup;
};
#endif // GAMEOBJECT_H_INCLUDED
