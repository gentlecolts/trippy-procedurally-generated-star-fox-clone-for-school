#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

void render(){
	//cout<<"render start"<<endl;

	for(int i=0;i<xmax*ymax;i++){
		vals[i].dist=-1;
	}

	double val,scl,scl2;//,z2;

	uint32_t color;
	double maxdst=-1;

	#if !test2d
		#if drawmethod<=2 || (drawmethod>=5 && drawmethod<=7)
		//const double lowz=max(-raise,0.0);
		const double lowz=-grid*(d+raise);
			#if drawmethod==0
			int xleft,xright,ytop,ybottom;
			#include "paint.h"
			#elif drawmethod==1
			double xleft,xright,ytop,ybottom;
			#include "paint2.h"
			#elif drawmethod==2
			int i,j;
			#include "cube2.h"
			#elif drawmethod==5
			int xleft,xright,ytop,ybottom;
			#include "paintcube.h"
			#elif drawmethod==6
			//const double lowz=max(-raise,0.0);
			int xleft,xright,ytop,ybottom;
			#include "precomp.h"
			#elif drawmethod==7
			double xleft,xright,ytop,ybottom;
			#include "precomp2.h"
			#endif
		#elif drawmethod==3
		#include "solve.h"
		#elif drawmethod==4
		#include "trace.h"
		#else
			#if quad==1
			#include "quad.h"
			#elif quad==2
			#include "oct.h"
			#endif
		#endif
	#endif

	chkCloseEvent();
	//cout<<"drawing"<<endl;

	uint32_t* pixels=(uint32_t *)screen->pixels;
	double tmp,avg,dst;
	int c=0;
	//bool edge;
	for(int i=0;i<xmax;i++){
		for(int j=0;j<ymax;j++){
			//#define crap
			#if !test2d
			if(vals[i+xmax*j].dist>0){
				#if outline==1
				c=0;
				avg=0;
				//edge=false;

				for(int a=-1;a<=1;a++){
					for(int b=-1;b<=1;b++){
						if(!(a==0 && b==0) && i+a>=0 && i+a<xmax && j+b>=0 && j+b<ymax){
							if(vals[i+a+xmax*(j+b)].dist<0){
								//edge=true;
								goto drawout;
							}
							#define d1 vals[i+a+xmax*(j+b)].dist
							#define d2 vals[i+xmax*j].dist
							//cout<<"d1: "<<d1<<"\t1/invsqrt: "<<1/invsqrt(d1)<<"\td2: "<<d2<<"\t1/invsqrt: "<<1/invsqrt(d2)<<endl;
							/*
							//dst=(1/invsqrt(d1)-1/invsqrt(d2));
							//dst*=dst;
							//dst=d1+d2-2*sqrt(d1*d2);
							//double x=d1*d2;
							dst=d1+d2-2/invsqrt(d1*d2);
							avg+=dst;
							/*/
							//dst=d1-d2;
							dst=1-d1/d2;
							avg+=dst*dst;
							//*/
							#undef d1
							#undef d2
							++c;
						}
					}
				}
				//dst=abs(vals[i+xmax*j].dist-avg/c);
				//if(abs(vals[i+xmax*j].dist-avg/c)>1){//sqrt(3)){
				//if(avg/(c-1)>1.0/(1*grid)){
				#define tol2 1.25//0.75
				if(avg*grid>tol2*(c-1)){
					//cout<<"set blue with avg="<<avg<<endl;

					//cout<<"setting to blue"<<endl;
					#define colcap (255/4.0)
					#define range 200.0
					#define base vals[i+xmax*j].dist+range/colcap
					if(false){
						drawout:
						color=0xff;//<<16;
					}else{
						const double t=tol2*(c-1)/(avg*grid);
						color=colcap+range/(base);
						const uint8_t
							r=t*color,
							g=t*color,
							b=255*(1-t)+t*color;
						color=(r<<16)|(g<<8)|b;
					}
					goto endofloop;//just in case?
				}else{
				#endif
					/*
					#else
					#define dst vals[i+xmax*j].dist
					#define sqr(x) (x)*(x)
					#define deep (dst*dst/(grid*grid)+sqr((double)i/xmax-0.5)+sqr((double)j/ymax-0.5))

					#define base deep/3+2
					#endif
					//*/
					#if outline==0
					#define colcap (255/4.0)
					#define range 200.0
					#define base vals[i+xmax*j].dist+range/colcap
					#endif

					color=colcap+range/(base);
					#undef colcap
					#undef range
					#undef base
					#undef dst
					#undef deep
					#undef sqr
					//color==(color<<16)|(color<<8)|((uint8_t)( (color*(1-dst/sqrt(3)) + dst/sqrt(3)*255) ));
					color|=(color<<16)|(color<<8);
				#if outline==1
				}
				#endif
			}else{
				color=0;
			}
			#else
			tmp=perlin.get(grid*i/xmax,grid*j/ymax,2);//perlin.maxval;
			cout<<"x: "<<grid*i/xmax<<"\ty: "<<grid*j/ymax<<"\tval: "<<tmp<<endl;
				#define coloring 0
				#if coloring==1
				if(tmp>0){
					color=(uint8_t)(tmp*255);
					//color&=0xff;
					color|=(color<<16)|(color<<8);
				}else{color=0;}/*
				if(perlin.get(grid*i/xmax,grid*j/ymax,0)>0){color==0xffffff;}
				else{color=0;}//*/
				#elif coloring==1
				color=(tmp>0)?0xffffff:0;
				#else
				color=255*(perlin.get(grid*i/xmax,grid*j/ymax,5)+1)/(perlin.maxval+1);
				color|=(color<<16)|(color<<8);
				#endif
				#undef coloring
			#endif

			endofloop:
			pixels[i+xmax*j]=color;
			//cout<<color<<",";
		}
		//cout<<endl;
	}

	SDL_Flip(screen);
}

#endif // RENDER_H_INCLUDED
