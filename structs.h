#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <iostream>
#include <stdint.h>

using namespace std;

struct pixel{
	double dist;
	uint32_t color;

	void init(uint32_t col,double distance){
		dist=distance;
		color=col;
	}
	pixel(){
		init(0,-1);
	}
	pixel(uint32_t col,double distance){
		init(col,distance);
	}
};

struct point3d{
	#if doGL
	GLdouble x,y,z;
	#else
	double x,y,z;
	#endif

	point3d(double x0=0,double y0=0,double z0=0){
		x=x0;
		y=y0;
		z=z0;
	}
};

struct vertex{
	float x,y,z;
	float r,g,b;

	vertex(float x2=0,float y2=0,float z2=0,float r2=0,float g2=0,float b2=0){
		x=x2;
		y=y2;
		z=z2;
		r=r2;
		g=g2;
		b=b2;
	}
};

struct octree{
	static const int maxdepth=8;
	octree* child[8];
	uint32_t rgb;//candidates for the extra 8 bits: alpha, lighting, shape(to reduce size)
	uint8_t shape;
	~octree(){
		for(int i=0;i<8;i++){//yay stackoverflow
			if(child[i]){
				delete child[i];
			}
		}
		//delete[] child;
	}
};

struct quadtree{
	static const int maxdepth=12;
	quadtree* child[4];
	uint32_t rgb;
	uint8_t shape;//will use the other 4 bits to note whether or not the child is a leaf
	~quadtree(){
		for(int i=0;i<4;i++){
			if(child[i]){
				delete child[i];
			}
		}
//		delete[] child;
	}
};

struct vec3d{
	double dx,dy,dz;
	vec3d(double deltx=0,double delty=0,double deltz=0){
		dx=deltx;
		dy=delty;
		dz=deltz;
	}
	double operator +(vec3d vec){
		return dx*vec.dx+dy*vec.dy+dz*vec.dz;
	}
};

template <class T>
class cycle{
	T* dat;
public:
	int front;
	int length;
	cycle(){
	}
	cycle(const int len){
		init(len);
	}
	~cycle(){
		delete[] dat;
	}

	void init(const int len){
		dat=new T[len];
		length=len;
		front=0;
	}

	T& operator [](int i){
		return dat[(i+front)%length];
	}

	void addToEnd(T data){
		dat[front]=data;
		front=(front+1)%length;
	}
	void addToEnd(T data[],int len){
		int c=0;
		int i=0;
		for (;i<len;i++){
			this[c]=data[i];
			++c;
		}
		if(i==c){cout<<"dont need c, can use i"<<endl;}//do you /see/ what i did there
		front=(front+c)%length;
	}
};

#endif // STRUCTS_H_INCLUDED
