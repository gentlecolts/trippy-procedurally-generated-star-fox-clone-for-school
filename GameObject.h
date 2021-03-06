#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "globals.h"

#include <ctime>
#include "Vec3d.h"

class EnemyWave;
class Model;
class Animation;

class GameObject
{
public:
	Model *model;
	//float xpos,ypos,zpos,xvel,yvel,zvel;
	Vec3d pos,vel,rot;
	bool *attachPointsFilled;
	//float xrot,yrot,zrot;
	double avgDist;
	Animation* theAnimation;
	int numChildren;
	bool player;
	double t;
	int health;
	bool bigGun;
	int score;
	
	GameObject *parent;
	GameObject** children;

	virtual void init();

	GameObject();
	virtual ~GameObject();

	virtual bool collidesWithNoise();
	virtual bool collidesWithObject(GameObject *obj);
	virtual void render();
	void doUpdate(double dt);
	void setup();
	void setAnimation(Animation *anim);
	Vec3d absolutePosition();
	Vec3d absoluteAngle();
	void fireWeapon();
	void fireBigGuns();
	void addUpHealth(int h);
	void setPlayer(bool p);
	virtual int getDamage(GameObject *other);
	
	Matrix getMatrix();
	
	virtual void destroy();
	virtual void update(double dt);
	virtual void uniqueRenderAfterPop();
	virtual void uniqueRender();
	virtual void uniqueRenderFirst();
	virtual void uniqueRenderLast();
	virtual bool isDone();
	virtual void addChild(GameObject *child, int index);
	virtual void addChild(GameObject *child, int index, Vec3d angle);
	virtual void afterSetup();
	virtual void doFire();
protected:
	int modelSize;
	long invinceStart;
private:
	bool didSetup;
};


#endif // GAMEOBJECT_H_INCLUDED
