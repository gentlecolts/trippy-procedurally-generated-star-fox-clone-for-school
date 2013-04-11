#include "camera.h"

#include "imports.h"
#include "globals.h"
#include "gameController.h"

#include "trace.h"
#include "glRender.h"
#include "outline.h"
#include "math.h"
#include "gameObject.h"


int precompindx(double x,double y,double z){
	//*
	x*=precompdivs;
	y*=precompdivs;
	z*=precompdivs;
	/*/
	x*=biznitch;
	y*=biznitch;
	z*=biznitch;
	//*/

	#if 0//isnoisebase2
	int
	i=((int)x)&(res-1),
	j=((int)y)&(res-1),
	k=((int)z)&(res-1);
	#else
	int
	i=((int)x)%res,
	j=((int)y)%res,
	k=((int)z)%res;

	if(i<0){i+=res;}
	if(j<0){j+=res;}
	if(k<0){k+=res;}
	#endif

	//cout<<"("<<x<<", "<<y<<", "<<z<<") -> "<<(int)(i+res*(j+res*k))<<endl;
	return (int)(i+res*(j+res*k));
}

void movecam(){
	//camx=thePlayerShip->xpos;
	//camy=-thePlayerShip->ypos;

    if(signum(thePlayerShip->xpos-camx)!=camPrevSgn) {
        camvx=0;
        camvy=0;
    } else {
        camvx+=0.01;
        camvy+=0.01;
    }

    camx+=min(camvx,abs(thePlayerShip->xpos-camx))*signum(thePlayerShip->xpos-camx);
    camy+=min(camvy,abs(thePlayerShip->ypos-camy))*signum(thePlayerShip->ypos-camy);

    camPrevSgn=signum(thePlayerShip->xpos-camx);

//	camx=max(-)

	if(space){
		anm8=min(anm8+anm8step,1.0);
	}else{
		anm8=max(anm8-anm8step,0.0);
	}

	//d=(1-anm8)*d1+anm8*d2;
	d=((1-anm8)*d1+anm8*d2)/2;

	#if doGL
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewangle,1,0.5,1/d+1);
	#endif
}

void render(){
	#if doGL
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	#endif

	for(int i=0;i<xmax*ymax;i++){
		vals[i].dist=-1;
	}

	#if drawmethod==4
		trace();
		doOutline();
	#elif drawmethod==9
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glTranslatef(-camx,camy,0);

		//gluLookAt(0,0,0,thePlayerShip->xpos,thePlayerShip->ypos,thePlayerShip->zpos,0,1,0);			BEST CAMERA
		//gluLookAt(camx/2,-camy/2,cameraOffset,thePlayerShip->xpos,thePlayerShip->ypos,thePlayerShip->zpos,0,1,0);
        gluLookAt(camx,camy+1,cameraOffset,thePlayerShip->xpos,thePlayerShip->ypos,thePlayerShip->zpos*3,0,1,0);

        glPushMatrix();
        glScalef(noiseScale, noiseScale, noiseScale);
		glBegin(GL_QUADS);
		glColor3f(0.5f,0.5f,0.5f);
		glRender();
		glEnd();

		/*
		glBegin(GL_QUAD_STRIP);
		for(int i=0;i<rand();i++){
			gluLookAt(rand()/(float)0xffffff,rand()/(float)0xffffff,rand()/(float)0xffffff,
						rand()/(float)0xffffff,rand()/(float)0xffffff,rand()/(float)0xffffff,
						rand()/(float)0xffffff,rand()/(float)0xffffff,rand()/(float)0xffffff);
			glColor3b(rand()&0xff,rand()&0xff,rand()&0xff);
			glVertex3d((4.0*(rand()&0xffff))/0xffff-1,(4.0*(rand()&0xffff))/0xffff-1,(-(1/d+1.0)*(rand()&0xffff))/0xffff);
		}glEnd();
		//*/
        glPopMatrix();

		renderObjects();
	#elif drawmethod==11///awww yeah turn it up to 11
		#include "cltrace.h"
		renderObjects();
	#endif
}
