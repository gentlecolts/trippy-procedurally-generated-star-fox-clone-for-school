#ifndef PERLIN3D_H_INCLUDED
#define PERLIN3D_H_INCLUDED

#include "structs.h"
#include "constants.h"
#include "vec3d.h"

/**how to determine position
 if the cube has side lengths of 2, and the center is at 0,0
 then the center of child[n] is at
 x=2*(n&1)-1 //if the first bit is one then x=1 else x = -1
 y=2*((n>>1)&1)-1 //same but for second bit
 z=2*((n>>2)&1)-1 //same but for third bit

 since (a&b)>>c == (a>>c)&(b>>c) and the same applies for rshift

 x=2*(n&1)-1 = ((n&1)<<1)-1 = ((n&1)<<1)-1 = ((n<<1)&2)-1
 y=2*((n>>1)&1)-1 = (((n>>1)&1)<<1)-1 = (n&2)-1
 z=2*((n>>2)&1)-1 = (((n>>2)&1)<<1)-1 = ((n>>1)&2)-1
*/

class perlin3d{
private:
	//here we define all of the variables which will be used in functions in the class, but are not acutal members
	//also, they will be static until multiple instances of this are needed
	static int gx,gy,gz;
	static double sx,sy,sz;

	#define dotp1d 1//b4 u bitch: yes, this is used elsewhere
	#if dotp1d
	static double dotp[8];
	static int a,b,c;
	#else
	static double dotp[2][2][2];
	#endif

	static Vec3d vec;

	inline void setdotp(double x,double y,double z);
public:
	Vec3d vals[grid*grid*grid];

	double get(double x,double y,double z);
	void init(uint32_t seed);

	perlin3d(uint32_t seed);
	perlin3d(){init(0xDEADBEEF);}
};

#endif // PERLIN3D_H_INCLUDED
