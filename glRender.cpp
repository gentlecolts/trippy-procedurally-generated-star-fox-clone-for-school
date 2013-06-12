#include "glRender.h"

#include "structs.h"
#include "constants.h"
#include "globals.h"
#include "camera.h"
#include "GLHelper.h"

#include <ctime>
using namespace std;

void glRender() {
	point3d corners[8];
	point3d normals[8];
	int indx;
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//glBegin(GL_QUADS);
	//cout<<"penis"<<endl;
	bool inCube,beenDrawn;
	double lastx;
	///TRY THIS http://www710.univ-lyon1.fr/~jciehl/Public/OpenGL_PG/ch08.html#id5502750
	/*
	for(double x=0;x<grid;x+=delta/2){
		for(double y=0;y<grid;y+=delta/2){
	/*/
	double x,y,z;
	const double step=delt2;

	///NOTE: need to resolve the issue of the last rect not being drawn
	double counter=0;
	for(int a=0;a<grid/step;a++){
		z=grid-a*step;
		if(z/grid>((double)playerOffset*5)/frameSize) {
			counter+=sin(a/(grid/step))*2;
			//counter+=500*sin(clock()/100.0*a/(grid/step))*2;
		}
	}
	glRotatef(counter, 0.0, 1.0, 0.3);
	//glRotatef(counter*5, 0.0, 0.0, 0.3);

	for(int a=0;a<grid/step;a++){
		//x=grid*a/(grid/(delta/2));
		z=grid-a*step;

		if(z/grid>((double)playerOffset*5)/frameSize) {
			glRotatef(-sin(a/(grid/step)), 0.0, 1.0, 0.3);
			//glRotatef(-sin(a/(grid/step))*5, 0.0, 0.0, 0.3);

		}
		glBegin(GL_QUADS);

		for(int b=0;b<grid/step;b++){
		y=b*step;
	//*/
			//glBegin(GL_QUADS);glColor3f(0.5f,0.5f,0.5f);
			inCube=false;
			beenDrawn=true;
			lastx=0;
			/*
			for(double z=0;z<grid;z+=delta){
			/*/
			for(int c=0;c<grid/step;c++){
			x=c*step;

			//*/
				if(noise[precompindx(x,y,z+zshft)]>tolerance){
//				if(perlin.get(x,y,z+zshft)>tolerance){
					if(!inCube){
						inCube=true;
						beenDrawn=false;
						lastx=x;
					}
				}else{
					if(!beenDrawn){
						inCube=false;
						beenDrawn=true;

						for(int i=-1;i<=1;i+=2){
						for(int j=-1;j<=1;j+=2){
						for(int k=-1;k<=1;k+=2){
						//indx=(((k+1)/2)<<2)|(((j+1)/2)<<1)|((i+1)/2);
							indx=((k+1)<<1)|(j+1)|((i+1)>>1);//acceptable because these are each either 0 or 2
						//*
							//corners[indx].x=(x-grid2+i*delt2)/grid2;
							corners[indx].x=( lastx+(x-lastx)*(i+1)/2 -grid2+i*delt2)/grid2;

							corners[indx].y=(y-grid2+j*delt2)/grid2;
							corners[indx].z=-(z-grid2+k*delt2)/(d*grid)-d/2+(fmod(zshft,step));
							//corners[indx].z=-(lastz+(z-delta-lastz)*(k+1)/2+k*delt2)/(d*grid)-d/2+(zshft-(int)zshft)/frameSize;

							//*
#if 0
							normals[indx].x=i;
							normals[indx].y=j;
							normals[indx].z=k; //butts
#else
#define h 0.001

							double tmp=perlin.get(lastx+(x-lastx)*(i+1)/2+i*delt2, y+j*delt2, (z+k*delt2)/(d*grid)-d/2);
							normals[indx].x=-(perlin.get(lastx+(x-lastx)*(i+1)/2+i*delt2+h, y+j*delt2, (z+k*delt2)/(d*grid)-d/2)-tmp)/h;
							normals[indx].y=-(perlin.get(lastx+(x-lastx)*(i+1)/2+i*delt2, y+j*delt2+h, (z+k*delt2)/(d*grid)-d/2)-tmp)/h;
							normals[indx].z=-(perlin.get(lastx+(x-lastx)*(i+1)/2+i*delt2+h, y+j*delt2, (z+k*delt2)/(d*grid)-d/2)-tmp+h)/h;


							/* //More correct, but spazzy

							 double tmp=perlin.get(lastx+(x-lastx)*(i+1)/2+i*delt2, y+j*delt2, (z+k*delt2)/(d*grid)-d/2+zshft);
							normals[indx].x=-(perlin.get(lastx+(x-lastx)*(i+1)/2+i*delt2+h, y+j*delt2, (z+k*delt2)/(d*grid)-d/2+zshft)-tmp)/h;
							normals[indx].y=-(perlin.get(lastx+(x-lastx)*(i+1)/2+i*delt2, y+j*delt2+h, (z+k*delt2)/(d*grid)-d/2+zshft)-tmp)/h;
							normals[indx].z=-(perlin.get(lastx+(x-lastx)*(i+1)/2+i*delt2+h, y+j*delt2, (z+k*delt2)/(d*grid)-d/2+zshft)-tmp+h)/h;*/

							/*
							 Even more correct, but stupid-looking

							 double mag=sqrt(normals[indx].x*normals[indx].x+normals[indx].y*normals[indx].y+normals[indx].z*normals[indx].z);

							normals[indx].x/=mag;
							normals[indx].y/=mag;
							normals[indx].z/=mag;*/
#undef h
#endif
							/*/
							normals[indx].x=rand();
							normals[indx].y=rand();
							normals[indx].z=rand();

							#define a normals[indx].x
							#define b normals[indx].y
							#define c normals[indx].z

							float bluh=sqrt(a*a+b*b+c*c);
							a/=bluh;
							b/=bluh;
							c/=bluh;

							#undef a
							#undef b
							#undef c
							//*/
						}}}

						//glBegin(GL_QUADS);glColor3f(0.5f,0.5f,0.5f);
						///zyx
						//000,001,011,010
						//drawquad(corners[0],corners[1],corners[3],corners[2]);
						drawquadnorm(corners[0],normals[0],corners[1],normals[1],corners[3],normals[3],corners[2],normals[2]);
						drawquadnorm(corners[0],normals[0],corners[1],normals[1],corners[5],normals[5],corners[4],normals[4]);
						drawquadnorm(corners[0],normals[0],corners[2],normals[2],corners[6],normals[6],corners[4],normals[4]);
						drawquadnorm(corners[3],normals[3],corners[2],normals[2],corners[6],normals[6],corners[7],normals[7]);
						drawquadnorm(corners[3],normals[3],corners[1],normals[1],corners[5],normals[5],corners[7],normals[7]);
						drawquadnorm(corners[6],normals[6],corners[4],normals[4],corners[5],normals[5],corners[7],normals[7]);

						//000,001,101,100
						/*drawquad(corners[0],corners[1],corners[5],corners[4]);

						//000,010,110,100
						drawquad(corners[0],corners[2],corners[6],corners[4]);

						//011,010,110,111
						drawquad(corners[3],corners[2],corners[6],corners[7]);

						//011,001,101,111
						drawquad(corners[3],corners[1],corners[5],corners[7]);

						//110,100,101,111
						drawquad(corners[6],corners[4],corners[5],corners[7]);*/
						//glEnd();
						//cout<<"a"<<endl;///if this shows up then make sure glbegin and glend are being called
						///ok so a was written...
					}
				}
			}
		}
		glEnd();
	}
}
