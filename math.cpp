#include "math.h"///WHY THE FLYING FUCK DO WE HAVE math.h?!?!?! see above line for my confusion

#include "constants.h"
#include "Vec3d.h"

/**
 double invsqrt(double x)
 Fast inverse square root function is quicker than the standard way of doing it, although slightly less precise

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
	Vec3d vect=Vec3d(0,0,-1);
	vect[0]=-sin(radians(yrot));
    vect[1]=sin(radians(xrot))*cos(radians(yrot));
	vect[2]=-cos(radians(xrot))*cos(radians(yrot));
	
	return vect;
}

Vec3d invGetVector(Vec3d vec) {
	vec=vec.normalize();
	
	double yrot=asin(-vec[0])/pi*180;
	//std::cout<<"vec[0]: "<<-vec[0]<<std::endl;
	double xrot=asin(vec[1]/cos(radians(yrot)))/pi*180;
	
	return Vec3d(xrot,yrot,0);
}

/**
 int signum(double val)
 Equivalent to Java Math.signum() because std doesn't have that apparently
 */
int signum(double val) {
    /*if(val<0.01 && val>-0.01)
        return 0;
    return val>0 ? 1 : -1;*/
    return (0<val)-(val<0);
}

Vec3d rotate(Vec3d v, Vec3d axis, float degrees) {
    axis = axis.normalize();
    float radians = degrees * pi / 180;
    float s = -sin(radians);		//it's negative deal with it
    float c = cos(radians);
    return v * c + axis * axis.dot(v) * (1 - c) + v.cross(axis) * s;
}

/**
 double distSq(double x1,double y1,double x2,double y2)
 Quick method for getting the distance squared, for readability/less typing
 */
double distSq(double x1,double y1,double x2,double y2) {
	double dx=x1-x2;
	double dy=y1-y2;
	
	return dx*dx+dy*dy;
}

/*long double longDoubleMod(long double a, long double b) {      //this probably is in std somewhere
    int i=a/b;
    return a-b*i;
}*/