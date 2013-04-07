#ifndef GLHELPER_H_INCLUDED
#define GLHELPER_H_INCLUDED

#include "imports.h"
#include "structs.h"

void glPreInit();
void glInit();
void drawquad(point3d p[4]);
void drawquad();
void drawCube(double x,double y,double z,double wid);
void drawRect3d(double x,double y,double z,double dx,double dy,double dz);

inline void drawquad(point3d p0,point3d p1,point3d p2,point3d p3){      //inline goes in .h
	glVertex3d(p0.x,p0.y,p0.z);
	glVertex3d(p1.x,p1.y,p1.z);
	glVertex3d(p2.x,p2.y,p2.z);
	glVertex3d(p3.x,p3.y,p3.z);
}

#endif // GLHELPER_H_INCLUDED
