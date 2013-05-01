#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

class Vec3d;

double invsqrt(double x);
double radians(double degrees);
Vec3d getVector(double xrot,double yrot);
Vec3d invGetVector(Vec3d vec);
int signum(double val);
double distSq(double x1,double y1,double x2,double y2);
Vec3d rotate(Vec3d v, Vec3d axis, float degrees);
//long double longDoubleMod(long double a, long double b);

#endif // MATH_H_INCLUDED
