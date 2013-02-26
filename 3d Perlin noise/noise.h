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
	static const int maxdepth=8;
	octree* child[8];
	uint32_t rgb;//candidates for the extra 8 bits: alpha, lighting, shape(to reduce size)
	uint8_t shape;
	~octree(){
		for(int i=0;i<8;i++){//yay stackoverflow
			if(child[i]){
				delete child[i];
			}
		}
		delete[] child;
	}
};

struct quadtree{
	static const int maxdepth=12;
	quadtree* child[4];
	uint32_t rgb;
	uint8_t shape;//will use the other 4 bits to note whether or not the child is a leaf
	~quadtree(){
		for(int i=0;i<4;i++){
			if(child[i]){
				delete child[i];
			}
		}
		delete[] child;
	}
};

struct vec3d{
	double dx,dy,dz;
	vec3d(double deltx=0,double delty=0,double deltz=0){
		dx=deltx;
		dy=delty;
		dz=deltz;
	}
	double operator +(vec3d vec){
		return dx*vec.dx+dy*vec.dy+dz*vec.dz;
	}
};

template <class T>
class cycle{
	T* dat;
public:
	int front;
	int length;
	cycle(){
	}
	cycle(const int len){
		init(len);
	}
	~cycle(){
		delete[] dat;
	}

	void init(const int len){
		dat=new T[len];
		length=len;
		front=0;
	}

	T& operator [](int i){
		return dat[(i+front)%length];
	}

	void addToEnd(T data){
		dat[front]=data;
		front=(front+1)%length;
	}
	void addToEnd(T data[],int len){
		int c=0;
		int i=0;
		for (;i<len;i++){
			this[c]=data[i];
			++c;
		}
		if(i==c){cout<<"dont need c, can use i"<<endl;}//do you /see/ what i did there
		front=(front+c)%length;
	}
};

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

	static vec3d vec;

	inline void setdotp(double x,double y,double z){
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
public:
	//static const int deep=8,grid=10;
	vec3d vals[grid*grid*grid];
	#if quad==1
	cycle<quadtree> noise;//(grid);
	static const int maxdepth=quadtree::maxdepth;
	#elif quad==2
	octree noise;
	static const int maxdepth=octree::maxdepth;
	#endif
	//double maxval;//may want for quadtree

	double get(double x,double y,double z){
		gx=((int)x)%grid;
		gy=((int)y)%grid;
		gz=((int)z)%grid;

		if(gx<0){gx+=grid;}
		if(gy<0){gy+=grid;}
		if(gz<0){gz+=grid;}

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

	double solvez(double x,double y,int z){
		gx=((int)x)%grid;
		gy=((int)y)%grid;
		gz=z%grid;

		if(gx<0){gx+=grid;}
		if(gy<0){gy+=grid;}
		if(gz<0){gz+=grid;}

		x=(x-gx);
		y=(y-gy);
		z=(z-gz);

		setdotp(x,y,z);

		x=((6*x-15)*x+10)*x*x*x;
		y=((6*y-15)*y+10)*y*y*y;

		dotp[0]=(1-x)*dotp[0]+x*dotp[1];
		dotp[1]=(1-x)*dotp[2]+x*dotp[3];
		dotp[2]=(1-x)*dotp[4]+x*dotp[5];
		dotp[3]=(1-x)*dotp[6]+x*dotp[7];

		dotp[0]=(1-y)*dotp[0]+y*dotp[1];
		dotp[1]=(1-y)*dotp[2]+y*dotp[3];

		return dotp[0]/(dotp[0]-dotp[1]);
	}

	#if quad==1
	void buildtree(quadtree* q,double x,double y,double z,int scale){//x and y of top corner of square with size grid/scale
		scale*=2;
		//recurse
		const double tmp=grid/scale;
		int addr;
		if(scale>grid || scale>(1<<maxdepth)){
			for(int i=0;i<1;i++){
				for(int j=0;j+=1;j++){
					if(get(x+i*tmp,y+j*tmp,z)>tolerance){
						//addr=(i+(j<<1));
						//q->shape|=(0x1<<(addr+4)) | (0x1<<addr);
						q->shape|=0x11<<addr;
					}
				}
			}
		}else{
			for(int i=0;i<1;i++){
				for(int j=0;j+=1;j++){
					buildtree(q->child[i+(j<<1)]=(quadtree*)(new quadtree()),x+i*tmp,y+j*tmp,z,scale);
				}
			}
		}

		//optimize
		for(int i=0;i<4;i++){
			if(q->child[i]!=NULL){
				//*
				q->shape|=((q->child[i]->shape==0)?0x11:0x10)<<i;/*/
				if(q->child[i].shape==0){
					q->shape|=0x11<<i;//child[i] exists and is a leaf
				}else{
					q->shape|=0x10<<i;//child[i] exists
				}//*/
			}
		}
		if(((q->shape)&0xf)==0xf){
			delete[] q->child;
			q->shape=0;
		}
	}
	#elif quad==2
	void buildtree(octree* q,int x,int y,int z,int scale){

	}
	#else
	#endif

	void init(uint32_t seed){
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

		#if drawmethod>=6
		//cout<<"note: tolerance is "<<tolerance<<endl;
		for(double x=0;x<grid;x+=delta){
			for(double y=0;y<grid;y+=delta){
				for(double z=0;z<grid;z+=delta){
					//cout<<"value at ("<<x<<", "<<y<<", "<<z<<") is "<<get(x,y,z)<<endl;
					noise[precompindx(x,y,z)].dist=get(x,y,z);
				}
			}
		}
		#endif

		#if quad!=0
		#if quad==1
		//cycle<quadtree> tmp(grid);
		//noise=tmp;
		noise.init(grid);
		#endif
		for(int z=0;z<grid;z++){
			#if quad==1
			buildtree(&noise[z],0.0,0.0,z,1);
			#else

			#endif
		}
		#endif
	}

	perlin3d(uint32_t seed){
		init(seed);
	}
	perlin3d(){init(0xDEADBEEF);}
};

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

#endif // NOISE_H_INCLUDED
