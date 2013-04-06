//#import "math.h"
//#include <cmath>
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
