#include "math.h"///WHY THE FLYING FUCK DO WE HAVE math.h?!?!?! see above line for my confusion

#include "constants.h"

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

double radians(double degrees) {
    return degrees*pi/180;
}


//Gets the unit vector in the direction of (0,0,-1) rotated by xrot (pitch) and yrot (yaw)
void getVector(double xrot,double yrot,double vect[3]) {
	vect[0]=-sin(radians(yrot));
    vect[1]=sin(radians(xrot))*cos(radians(yrot));
	vect[2]=-cos(radians(xrot))*cos(radians(yrot));
}

int signum(double val) {
    /*if(val<0.01 && val>-0.01)
        return 0;
    return val>0 ? 1 : -1;*/
    return (0<val)-(val<0);
}

/*long double longDoubleMod(long double a, long double b) {      //this probably is in std somewhere
    int i=a/b;
    return a-b*i;
}*/