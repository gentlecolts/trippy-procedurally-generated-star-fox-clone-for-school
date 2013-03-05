#ifndef NOISE_H_INCLUDED
#define NOISE_H_INCLUDED

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
struct octree{
	octree* child[8];
	uint8_t shape;
	uint32_t rgb;
};

class perlin3d{
public:
	double vals[grid*grid*grid];
	octree noise;
	double maxval;

	//for int[w][h]->int[w*h], int[x][y] == int[x+y*w]
	//for int[w][h][d]->int[w][h*d], int[x][y][z] == int[x][y+h*z]
	//for int[w][h][d]->int[w*h*d], int[x][y][z] == int[x+w*(y+h*z)]
	//if x=w-1,y=h-1,z=d-1 will be x+w*(y+h*z) == w-1+w*(h-1+h*(d-1)) == w-1+w*(h-1+h*d-h) == w-1+w*(h*d-1) == w-1+w*h*d-w == w*h*d-1
	double get(double x,double y,double z){
		int
		gx0=((int)x)%grid,
		gy0=((int)y)%grid,
		gz0=((int)z)%grid,
		gx1=(gx0+1)%grid,
		gy1=(gy0+1)%grid,
		gz1=(gz0+1)%grid;

		double sx=(x-gx0),sy=(y-gy0),sz=(z-gz0);
		/**
		 weighted average using f(x)=6x^5-15x^4+10x^3
		 this function has the following important properties:
		 f(0)=0		f(1)=1
		 f'(0)=0	f''(0)=0
		 f'(1)=0	f''(1)=0
		*/
		sx*=sx*sx*(10-sx*(15-6*sx));
		sy*=sy*sy*(10-sy*(15-6*sy));
		sz*=sz*sz*(10-sz*(15-6*sz));

		if(gx0<0){gx0+=grid;}
		if(gy0<0){gy0+=grid;}
		if(gz0<0){gz0+=grid;}
		if(gx1<0){gx1+=grid;}
		if(gy1<0){gy1+=grid;}
		if(gz1<0){gz1+=grid;}

		double
		g0=vals[gx0+grid*(gy0+grid*gz0)],
		g1=vals[gx1+grid*(gy0+grid*gz0)],
		g2=vals[gx0+grid*(gy1+grid*gz0)],
		g3=vals[gx1+grid*(gy1+grid*gz0)],
		g4=vals[gx0+grid*(gy0+grid*gz1)],
		g5=vals[gx1+grid*(gy0+grid*gz1)],
		g6=vals[gx0+grid*(gy1+grid*gz1)],
		g7=vals[gx1+grid*(gy1+grid*gz1)];


		g0=(1-sx)*g0+sx*g1;
		g1=(1-sx)*g2+sx*g3;
		g2=(1-sx)*g4+sx*g5;
		g3=(1-sx)*g6+sx*g7;

		g0=(1-sy)*g0+sy*g1;
		g1=(1-sy)*g2+sy*g3;

		/*
		if((sz*g0+(1-sz)*g1)/maxval>1){
			cout<<"x: "<<x<<"\ty: "<<y<<"\tz: "<<z<<"\tsx: "<<sx<<"\tsy: "<<sy<<"\tsz: "<<sz<<"\tval: "<<sz*g0+(1-sz)*g1<<"\tmaxval: "<<maxval<<endl;
		}//*/
		return (1-sz)*g0+sz*g1;
	}

	void init(uint32_t seed){
		//double rnd=seed;//TODO: use better psrng
		//srand(seed);
		//cout<<"initialized"<<endl;
		maxval=-1;
		double rnd=(double)seed/(double)UINT_MAX;
		for(int i=0; i<grid*grid*grid; i++){
			rnd*=4*(1-rnd);
			vals[i]=2*rnd-1;
			maxval=max(vals[i],maxval);
			//cout<<vals[i]<<",";
		}
	}

	perlin3d(uint32_t seed){
		init(seed);
	}
	perlin3d(){init(0xDEADBEEF);}
};

#endif // NOISE_H_INCLUDED
