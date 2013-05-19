#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

class Vec3d;

double invsqrt(double x);
double radians(double degrees);
Vec3d getVector(double xrot,double yrot);
Vec3d invGetVector(Vec3d vec);
int signum(double val);
Vec3d rotate(Vec3d v, Vec3d axis, float degrees);

#endif // MATH_H_INCLUDED
