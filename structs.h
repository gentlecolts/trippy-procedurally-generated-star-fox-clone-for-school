#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "imports.h"

using namespace std;


/**
 struct point3d
 A 3d point; possibly redundant with Vec3d
 */
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

#endif // STRUCTS_H_INCLUDED
