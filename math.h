#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

class Vec3f;

double invsqrt(double x);
double radians(double degrees);
Vec3f getVector(double xrot,double yrot);
int signum(double val);
double distSq(double x1,double y1,double x2,double y2);
Vec3f rotate(Vec3f v, Vec3f axis, float degrees);
//long double longDoubleMod(long double a, long double b);

#endif // MATH_H_INCLUDED
