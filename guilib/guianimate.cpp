#include "guianimate.h"
#include <ctime>
#include <iostream>
using namespace std;

#define STATE_MOVING 0x01
#define STATE_MOVE_FN 0x02
#define STATE_MOVE_FN_XY 0x04
#define STATE_MOVESTATE 0x07

#define STATE_ALPHA_TRANS 0x08
#define STATE_ALPHA_FN 0x10
#define STATE_ALPHA_STATE 0x18

void aniPic::AniInit(){
	state=0;
}
/**
transition the alpha to a certian value over an amount of time
*/
void aniPic::alphaTo(float a,long millis){
	alphaTo(alpha,a,millis);
}
/**
same as above but also provide a starting alpha
*/
void aniPic::alphaTo(float a0,float a,long millis){
	alpha0=a0;
	alpha_target=a;
	state|=STATE_ALPHA_TRANS;
	state&=~STATE_ALPHA_FN;
	alpha_t_target=(millis*CLOCKS_PER_SEC)/1000+(alpha_t0=clock());
}

/**
move this object to a specific point in an amount of time
*/
void aniPic::moveTo(point p,long millis){
	moveTo(dest.x,dest.y,p.x,p.y,millis);
}
void aniPic::moveTo(int x,int y,long millis){
	moveTo(dest.x,dest.y,x,y,millis);
}
/**
move this object from a point to another point in an amount of time
*/
void aniPic::moveTo(point p0,point p,long millis){
	moveTo(p0.x,p0.y,p.x,p.y,millis);
}
void aniPic::moveTo(int x0,int y0,int x,int y,long millis){
	p0.x=x0;
	p0.y=y0;
	p_target.x=x;
	p_target.y=y;
	state|=STATE_MOVING;
	state&=~STATE_MOVE_FN;
	p_t_target=(millis*CLOCKS_PER_SEC)/1000 + (p_t0=clock());
}

/**
change the alpha over time as specified by the given function
*/
void aniPic::alphaFn(float (*a)(double t),long millis,double start,double stop){
	alpha_a=start;
	alpha_b=stop;
	state|=STATE_ALPHA_TRANS|STATE_ALPHA_FN;
	alphaFunc=a;
	alpha_t_target=(millis*CLOCKS_PER_SEC)/1000+(alpha_t0=clock());
}
/**
move the object according to a function
*/
void aniPic::moveAlong(int (*x)(double t),int (*y)(double t),long millis,double start,double stop){
	p_a=start;
	p_b=stop;
	state|=STATE_MOVING|STATE_MOVE_FN|STATE_MOVE_FN_XY;
	fx=x;
	fy=y;
	p_t_target=(millis*CLOCKS_PER_SEC)/1000+(alpha_t0=clock());
}
void aniPic::moveAlong(point (*func)(double t),long millis,double start,double stop){
	p_a=start;
	p_b=stop;
	state|=STATE_MOVING|STATE_MOVE_FN;
	state&=~STATE_MOVE_FN_XY;
	fn=func;
	p_t_target=(millis*CLOCKS_PER_SEC)/1000+(alpha_t0=clock());
}

/**
has the alpha finished animating
*/
bool aniPic::isAlphaDone(){
	return clock()>alpha_t_target;
}
/**
has the object finished moving
*/
bool aniPic::isMoveDone(){
	return clock()>p_t_target;
}

/**
update the alpha and position
*/
point p;
void aniPic::checkAnm(){
	long t=clock();
	double tAlpha=min(double(t-alpha_t0)/(alpha_t_target-alpha_t0),1.0);
	double tPos=min(double(t-p_t0)/(p_t_target-p_t0),1.0);

	if(state&STATE_ALPHA_FN){//!=0
		alpha=alphaFunc((alpha_b-alpha_a)*tAlpha+alpha_a);
	}else if(state&STATE_ALPHA_TRANS){
		alpha=(alpha_target-alpha0)*tAlpha+alpha0;
	}

	if(state&STATE_MOVE_FN){//!=0
		if(state&STATE_MOVE_FN_XY){
			dest.x=fx((p_b-p_a)*tPos+p_a);
			dest.y=fy((p_b-p_a)*tPos+p_a);
		}else{
			p=fn((p_b-p_a)*tPos+p_a);
			dest.x=p.x;
			dest.y=p.y;
		}
	}else if(state&STATE_MOVING){
		dest.x=(p_target.x-p0.x)*tPos+p0.x;
		dest.y=(p_target.y-p0.y)*tPos+p0.y;
		//cout<<p_t0<<'\t'<<t<<'\t'<<p_t_target<<'\t'<<tPos<<endl;
		//cout<<"x: "<<dest.x<<"\ty: "<<dest.y<<endl;
		//cout<<endl;
	}
	//cout<<"got here"<<endl;
}

/**
update the object
*/
void aniPic::update(){
	checkAnm();
	draw();
}
void aniBtn::update(){
	checkAnm();
	updateBtn();
	button::draw(current);//for some reason i cant help but feel that this will come back to haunt me
}
