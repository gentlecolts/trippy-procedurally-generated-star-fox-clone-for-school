#ifndef GUIANIMATE_H_INCLUDED
#define GUIANIMATE_H_INCLUDED
#include "guiobj.h"

struct point{
	int x,y;
	point():x(0),y(0){}
	point(int x0,int y0): x(x0),y(y0){}
};

class aniPic:public picture{
protected:
	point p0,p_target;
	long p_t0,p_t_target;

	float alpha0,alpha_target;
	long alpha_t0,alpha_t_target;

	uint8_t state;

	double alpha_a,alpha_b,p_a,p_b;
	float (*alphaFunc)(double t);
	int (*fx)(double t),(*fy)(double t);
	point (*fn)(double t);
public:
	virtual void AniInit();
	aniPic(const char* file): picture(file){AniInit();}
	aniPic(SDL_Surface* pict): picture(pict){AniInit();}

	virtual void alphaTo(float a,long millis);
	virtual void moveTo(point p,long millis);
	virtual void moveTo(int x,int y,long millis);

	virtual void alphaTo(float a0,float a,long millis);
	virtual void moveTo(point p0,point p,long millis);
	virtual void moveTo(int x0,int y0,int x,int y,long millis);

	virtual void alphaFn(float (*a)(double t),long millis,double start=0,double stop=1);
	virtual void moveAlong(int (*x)(double t),int (*y)(double t),long millis,double start=0,double stop=1);
	virtual void moveAlong(point (*fn)(double t),long millis,double start=0,double stop=1);

	virtual void checkAnm();
	virtual void update();

	virtual bool isAlphaDone(),isMoveDone();
};

class aniBtn:public aniPic,public button{
public:
	void update();
};

#endif // GUIANIMATE_H_INCLUDED
