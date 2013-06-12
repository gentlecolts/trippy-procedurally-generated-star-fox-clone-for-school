#include "math.h"///WHY THE FLYING FUCK DO WE HAVE math.h?!?!?! see above line for my confusion
///well...there appears to be no above line...
///the confusion was that math.h is a standard library...

#include "constants.h"
#include "Vec3d.h"

using namespace std;
/**
 double invsqrt(double x)
 Fast inverse square root function is quicker than the standard way of computing 1/sqrt(x), although slightly less precise
 */
double invsqrt(double x) {
    double xhalf = x/2;
    long long i =*(long long*)&x;
    i = 0x5fe6eb50c7b537a9l - (i>>1);
    x = *(double*)&i;
    x = x*(1.5 - xhalf*x*x);
	//x = x*(1.5 - xhalf*x*x);
    return x;
}/*/
float invsqrt (float x){
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f375a86 - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return x;
}
//*/

/**
 double radians(double degrees)
 Convenience method for converting from degrees to radians
 */
double radians(double degrees) {
    return degrees*pi/180;
}


/**
 double getVector(double xrot, double yrot, double vect[3])
 Gets the unit vector in the direction of (0,0,-1) (forward in OpenGL) rotated by xrot (pitch) and yrot (yaw), and stores it in vect
 */
Vec3d getVector(double xrot,double yrot) {//TODO: consider only calulating once per frame
	Vec3d vect;
	vect[0]=-sin(radians(yrot));
    vect[1]=sin(radians(xrot))*cos(radians(yrot));
	vect[2]=-cos(radians(xrot))*cos(radians(yrot));

	return vect;
}

/**
 Vec3d invGetVector(Vec3d vec)
 Returns the 3 euler angles needed to rotate the vector (0,0,1) to point in the direction of vec
 */
Vec3d invGetVector(Vec3d vec) {
	vec=vec.normalize();

	double xrot=-asin(vec[1])/pi*180;
	double yrot=atan2(vec[0],vec[2])/pi*180;

	return Vec3d(xrot,yrot,0);
}

/**
 int signum(double val)
 Equivalent to Java Math.signum() because std doesn't have that apparently
 */
int signum(double val) {
    return (0<val)-(val<0);
}

/**
 Vec3d rotate(Vec3d v, Vec3d axis, float degrees)
 Returns the esult of rotating a vector around an axis
 */
Vec3d rotate(Vec3d v, Vec3d axis, float degrees) {
    axis = axis.normalize();
    float radians = degrees * pi / 180;
    float s = sin(radians);		//it's negative deal with it
    float c = cos(radians);
    return v * c + axis * axis.dot(v) * (1 - c) + v.cross(axis) * s;
}
