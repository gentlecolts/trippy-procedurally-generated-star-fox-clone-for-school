#include "outline.h"

#include <stdint.h>
#include "globals.h"

void doOutline() {      //FIXME: do we even need this? And what is color? CodeBlocks can't find its definition in the other project
	/*
	color is the new color in for the current pixel, if it isnt declared here, it was probably declared in render.cpp
	it should be a uint32_t
	also we need this if we want to draw outlines on the objects,
	this used to be the function that drew everything for non opengl rendering
	also, note that if we ever use this again, we may need to fix parts within any #if shadenorm
	*/
/*
    uint32_t* pixels=(uint32_t *)screen->pixels;
    double tmp,avg,dst,t;
    int c=0;
    //bool edge;

    #define outline_red 0
    #define outline_green 0
    #define outline_blue 0

    uint8_t r,g,b;

    //double nmin=50,nmax=-33;
    for(int i=0;i<xmax;i++){
        for(int j=0;j<ymax;j++){
            //#define crap
            #if !test2d
            #define colcap (255/4.0)

            #error instance of shadenorm, make sure this is correct before removing (that is if this ever gets reimplemented)
            #if shadenorm
            #define falloffcolor colcap*( ((grid-2)/(0.125*vals[i+xmax*j].dist+2))*((2+normals[i+xmax*j])/4) )
            //#define falloffcolor colcap*( ((grid-2)/(0.125*vals[i+xmax*j].dist+2))*(normals[i+xmax*j]*normals[i+xmax*j]) )
            //nmin=min(nmin,normals[i+xmax*j]);
            //nmax=max(nmax,normals[i+xmax*j]);
            #else
            #define falloffcolor colcap*((grid-2)/(0.125*vals[i+xmax*j].dist+2))
            #endif

            if(vals[i+xmax*j].dist>0){
                #if outline==1
                c=0;
                avg=0;
                //edge=false;

                for(int h=-1;h<=1;h++){
                    for(int k=-1;k<=1;k++){
                        if(!(h==0 && k==0) && i+h>=0 && i+h<xmax && j+k>=0 && j+k<ymax){
                            if(vals[i+h+xmax*(j+k)].dist<0){
                                //edge=true;
                                color=(outline_red<<16)|(outline_green<<8)|outline_blue;
                                goto endofloop;
                            }
                            #define d1 vals[i+h+xmax*(j+k)].dist
                            #define d2 vals[i+xmax*j].dist
                            //cout<<"d1: "<<d1<<"\t1/invsqrt: "<<1/invsqrt(d1)<<"\td2: "<<d2<<"\t1/invsqrt: "<<1/invsqrt(d2)<<endl;
                            /*
                            //dst=(1/invsqrt(d1)-1/invsqrt(d2));
                            //dst*=dst;
                            //dst=d1+d2-2*sqrt(d1*d2);
                            //double x=d1*d2;
                            dst=d1+d2-2/invsqrt(d1*d2);
                            avg+=dst;
                            / /
                            #if 0
                            //dst=d1-d2;
                            dst=1-d1/d2;
                            avg+=dst*dst;
                            #else
                            avg+=1-d1*d1/(d2*d2);
                            #endif
                            // /
                            #undef d1
                            #undef d2
                            ++c;
                        }
                    }
                }
                //dst=abs(vals[i+xmax*j].dist-avg/c);
                //if(abs(vals[i+xmax*j].dist-avg/c)>1){//sqrt(3)){

                /*
                #if 0
                t=(c-1)/(avg*tol2*grid);
                #else
                t=tol2*(c-1)/(avg*grid);
                #endif

                if(abs(t)<1){
                / /
                #if 0
                //+tol2 -> thicker
                #define tol2 2//1.25
                //if(avg/(c-1)>1.0/(tol2*grid)){
                if(tol2*grid*avg>(c-1)){
                    t=(c-1)/(avg*tol2*grid);
                #else
                //+tol2 -> thinner
                #define tol2 2//1.25//0.75
                //if(avg/(c-1)>tol2/grid){
                if(avg*grid>tol2*(c-1)){
                    t=tol2*(c-1)/(avg*grid);
                #endif

                // /

                    //cout<<"set blue with avg="<<avg<<endl;

                    //cout<<"setting to blue"<<endl;
                    //#define range 200.0
                    //#define base vals[i+xmax*j].dist+range/colcap

                    //color=colcap+range/(base);
                    //color=colcap*((grid-2)/(0.125*vals[i+xmax*j].dist+0.5/invsqrt(vals[i+xmax*j].dist)+2));
                    color=falloffcolor;
                    //const uint8_t
                    r=outline_red*(1-t)+t*color;
                    g=outline_green*(1-t)+t*color;
                    b=outline_blue*(1-t)+t*color;
                    color=(r<<16)|(g<<8)|b;
                }else{
                #endif
                    /*
                    #if outline==0
                    #define range 200.0
                    #define base vals[i+xmax*j].dist+range/colcap
                    #endif

                    //color=colcap+ra0nge/(base);
                    / /
                    color=falloffcolor;
                    // /
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
                else{color=0;}// /
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
    SDL_Flip(screen);
    }

    //cout<<"min: "<<nmin<<"\tmax: "<<nmax<<endl;
*/
}
