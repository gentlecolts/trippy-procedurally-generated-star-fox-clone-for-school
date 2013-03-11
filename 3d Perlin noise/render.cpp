#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#if doGL
#include "glbullshit.cpp"
#endif

void render(){
	//cout<<"render start"<<endl;

	for(int i=0;i<xmax*ymax;i++){
		vals[i].dist=-1;
	}

	double val,scl,scl2;//,z2;

	uint32_t color;
	double maxdst=-1;

	#if !test2d
		#if quad==0 && (drawmethod<=2 || (drawmethod>=5 && drawmethod<=7))
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
		#elif drawmethod>=8 && drawmethod<=10
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(-camx/grid2,camy/grid2,0);
			glBegin(GL_QUADS);glColor3f(0.5f,0.5f,0.5f);
			//glColor3f(1,1,1);
			#if drawmethod==8
				#include "glrender.h"
			#elif drawmethod==9
				#include "glrender2.h"
			#elif drawmethod==10
				#include "glQuad.h"
			#endif
			glEnd();
		#elif drawmethod==11///awww yeah turn it up to 11
			#include "cltrace.h"
		#else
			#if quad==1
			#include "quad.h"
			#elif quad==2
			#include "oct.h"
			#endif
		#endif
	#endif

    //glLoadIdentity();
    for(int i=0;i<numGameObjects;i++) {
        gameObjects[i].render();
    }

	chkCloseEvent();
	//cout<<"drawing"<<endl;

	#if doGL
	#if outline
	#include "gloutline.h"
	#endif
	#else
	#include "outline.h"
	#endif
}

#endif // RENDER_H_INCLUDED
