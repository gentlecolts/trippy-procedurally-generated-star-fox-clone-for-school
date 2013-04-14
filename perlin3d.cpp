//#import "perlin3d.h"
#include "perlin3d.h"

#include <climits>

#include "globals.h"
#include "camera.h"

//silly c++ initialization of static vars
int perlin3d::gx,perlin3d::gy,perlin3d::gz;
double perlin3d::sx,perlin3d::sy,perlin3d::sz;

#if dotp1d
double perlin3d::dotp[8];
int perlin3d::a,perlin3d::b,perlin3d::c;
#else
double perlin3d::dotp[2][2][2];
#endif

vec3d perlin3d::vec;

inline void perlin3d::setdotp(double x,double y,double z){
	#if dotp1d
	for(int d=0;d<8;d++){
		/*
		a=d&0x1;
		b=(d>>1)&0x1;
		c=(d>>2)&0x1;
		//*/
	#else
	for(int c=0;c<2;c++){
		for(int b=0;b<2;b++){
			for(int a=0;a<2;a++){
	#endif
				//vec.x0=a;
				//vec.y0=b;

				#if dotp1d
				vec.dx=x-(a=d&0x1);
				vec.dy=y-(b=(d>>1)&0x1);
				vec.dz=z-(c=(d>>2)&0x1);
				#else
				vec.dx=x-a;
				vec.dy=y-b;
				vec.dz=z-c;
				#endif

				#define xtemp ((gx+a)%grid)
				#define ytemp ((gy+b)%grid)
				#define ztemp ((gz+c)%grid)

				#if quad==0
				#if dotp1d
				dotp[d]=vec+vals[xtemp+grid*(ytemp+grid*ztemp)];
				#else
				dotp[a][b][c]=vec+vals[xtemp+grid*(ytemp+grid*ztemp)];
				#endif
				#else
				///TODO implement this
				#endif
				#undef xtemp
				#undef ytemp
				#undef ztemp
		#if !dotp1d
			}
		}
		#endif
	}
}

double perlin3d::get(double x,double y,double z){
	/*
	gx=((int)x)%grid;
	gy=((int)y)%grid;
	gz=((int)z)%grid;

	if(gx<0){gx+=grid;}
	if(gy<0){gy+=grid;}
	if(gz<0){gz+=grid;}
	/*/
	if((gx=((int)x)%grid)<0){gx+=grid;}
	if((gy=((int)y)%grid)<0){gy+=grid;}
	if((gz=((int)z)%grid)<0){gz+=grid;}
	//*/

	x=(x-gx);
	y=(y-gy);
	z=(z-gz);
	/**
	 weighted average using f(x)=6x^5-15x^4+10x^3
	 this function has the following important properties:
	 f(0)=0		f(1)=1
	 f'(0)=0	f''(0)=0
	 f'(1)=0	f''(1)=0
	*/

	sx=((6*x-15)*x+10)*x*x*x;
	sy=((6*y-15)*y+10)*y*y*y;
	sz=((6*z-15)*z+10)*z*z*z;

	setdotp(x,y,z);
	//(0,0,0),(1,0,0),(0,1,0),(1,1,0),(0,0,1),(1,0,1),(0,1,1),(1,1,1)
	#if dotp1d
	dotp[0]=(1-sx)*dotp[0]+sx*dotp[1];
	dotp[1]=(1-sx)*dotp[2]+sx*dotp[3];
	dotp[2]=(1-sx)*dotp[4]+sx*dotp[5];
	dotp[3]=(1-sx)*dotp[6]+sx*dotp[7];

	dotp[0]=(1-sy)*dotp[0]+sy*dotp[1];
	dotp[1]=(1-sy)*dotp[2]+sy*dotp[3];

	return (1-sz)*dotp[0]+sz*dotp[1];
	#else
	dotp[0][0][0]=(1-sx)*dotp[0][0][0]+sx*dotp[1][0][0];
	dotp[1][0][0]=(1-sx)*dotp[0][1][0]+sx*dotp[1][1][0];
	dotp[0][1][0]=(1-sx)*dotp[0][0][1]+sx*dotp[1][0][1];
	dotp[1][1][0]=(1-sx)*dotp[0][1][1]+sx*dotp[1][1][1];

	dotp[0][0][0]=(1-sy)*dotp[0][0][0]+sy*dotp[1][0][0];
	dotp[1][0][0]=(1-sy)*dotp[0][1][0]+sy*dotp[1][1][0];

	return (1-sz)*dotp[0][0][0]+sz*dotp[1][0][0];
	#endif
}

void perlin3d::init(uint32_t seed){
	//double rnd=seed;//TODO: use better psrng
	//srand(seed);
	//cout<<"initialized"<<endl;
	double rnd=(double)seed/(double)UINT_MAX;
	/*
	for(int z=0;z<grid;z++){
		for(int y=0;y<grid;y++){
			for(int x=0;x<grid;x++){
				#define dx vals[x+grid*(y+grid*z)].dx
				#define dy vals[x+grid*(y+grid*z)].dy
				#define dz vals[x+grid*(y+grid*z)].dz
				dz=2*(rnd*=4*(1-rnd))-1;
				dy=2*(rnd*=4*(1-rnd))-1;
				dx=((rnd*=4*(1-rnd))>0.5?1:-1)*sqrt(1-(dz*dz+dy*dy));
				#undef dx
				#undef dy
				#undef dz
			}
		}
	}/*/
	double inc,azm;
	for(int i=0;i<grid*grid*grid;i++){
		#define dx vals[i].dx
		#define dy vals[i].dy
		#define dz vals[i].dz
		/*
		dx=2*(rnd*=4*(1-rnd))-1;
		dy=2*(rnd*=4*(1-rnd))-1;
		dz=((rnd*=4*(1-rnd))>0.5?1:-1)*sqrt(1-dx*dx+dx*dx);/*/
		inc=2*pi*(rnd*=4*(1-rnd));
		azm=2*pi*(rnd*=4*(1-rnd));
		dx=sin(inc)*cos(azm);
		dy=sin(inc)*sin(azm);
		dz=cos(inc);

		//cout<<"generated ("<<dx<<", "<<dy<<", "<<dz<<") "<<endl;
		//*/
		#undef dx
		#undef dy
		#undef dz
	}
	//*/

	//#if drawmethod>=6 || drawmethod==4
	//cout<<"note: tolerance is "<<tolerance<<endl;
	/*
	for(double x=0;x<grid;x+=precompdelta){
		for(double y=0;y<grid;y+=precompdelta){
			for(double z=0;z<grid;z+=precompdelta){
	/*/
	double x,y,z;
	for(int i=0;i<grid/precompdelta;i++){
		x=i*precompdelta;
		for(int j=0;j<grid/precompdelta;j++){
			y=j*precompdelta;
			for(int k=0;k<grid/precompdelta;k++){
				z=k*precompdelta;
	//*/
				//cout<<"value at ("<<x<<", "<<y<<", "<<z<<") is "<<get(x,y,z)<<endl;
				//noise[precompindx(x,y,z)].dist=get(x,y,z);
				#warning instance of shadenorm
				#error i cant use warning (its not cross platform) so i am using error, see the above line
				#if shadenorm
				int indx=precompindx(x,y,z);
				//noise[indx]=get(x,y,z);
				//normlist[indx]=normal(x,y,z);
				normlist[indx]=normal(x,y,z,&(noise[indx])).y;
				#else
				noise[precompindx(x,y,z)]=get(x,y,z);
				#endif
			}
		}
	}

	/*NOTE: this is bad for raytrace
	//optimize, in other words, if the point cannot be seen, dont bother with it
	bool blahl;
	bool* shouldremove=new bool[res3];
	int indx;
	#if 0
	#include "optimizePrecomp.h"//uses doubles for loop index
	#else
	#include "optimizePrecomp2.h"//uses int for loop index
	#endif
	//*/

	// #endif
}

perlin3d::perlin3d(uint32_t seed){
	init(seed);
}
