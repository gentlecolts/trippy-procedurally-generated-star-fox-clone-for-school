#ifndef GLRENDER_H_INCLUDED
#define GLRENDER_H_INCLUDED

point3d corners[8];
int indx;
//glMatrixMode(GL_MODELVIEW);
//glLoadIdentity();

//glBegin(GL_QUADS);
//cout<<"penis"<<endl;
bool inCube,beenDrawn;
double lastz;
///TRY THIS http://www710.univ-lyon1.fr/~jciehl/Public/OpenGL_PG/ch08.html#id5502750
/*
for(double x=0;x<grid;x+=delta/2){
	for(double y=0;y<grid;y+=delta/2){
/*/
double x,y,z;
const double step=delta/2;

///NOTE: need to resolve the issue of the last rect not being drawn
for(int a=0;a<grid/step;a++){
	//x=grid*a/(grid/(delta/2));
	x=a*step;
	for(int b=0;b<grid/step;b++){
	y=b*step;
//*/
		//glBegin(GL_QUADS);glColor3f(0.5f,0.5f,0.5f);
		inCube=false;
		beenDrawn=true;
		lastz=0;
		/*
		for(double z=0;z<grid;z+=delta){
		/*/
		for(int c=0;c<grid/delta;c++){
		z=c*step;
		//*/
			if(noise[precompindx(x,y,z+zshft)]>tolerance){
				if(!inCube){
					inCube=true;
					beenDrawn=false;
					lastz=z;
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
					corners[indx].x=(x-grid2+i*delt2)/grid2;
					corners[indx].y=(y-grid2+j*delt2)/grid2;
					/*/
					corners[indx].x=x+i*delt2;
					corners[indx].y=y+j*delt2;
					//*/
					//corners[indx].z=-(z+k*delt2)/grid-0.5;
					//corners[indx].z=-2*(lastz+(z-delta-lastz)*(k+1)/2+k*delt2)/grid-1.5;
					//corners[indx].z=(lastz+(z-delta-lastz)*(k+1)/2+k*delt2)/grid-1.5;
					//corners[indx].z=-(lastz+(z-delta-lastz)*(k+1)/2+k*delt2)-1;
					//corners[indx].z=-(lastz+(z-delta-lastz)*(k+1)/2+k*delt2)/(d*grid)-1;
					corners[indx].z=-(lastz+(z-delta-lastz)*(k+1)/2+k*delt2)/(d*grid)-d/2;
					}}}

					//glBegin(GL_QUADS);glColor3f(0.5f,0.5f,0.5f);
					///zyx
					#if 1
					//000,001,011,010
					drawquad(corners[0],corners[1],corners[3],corners[2]);

					//000,001,101,100
					drawquad(corners[0],corners[1],corners[5],corners[4]);

					//000,010,110,100
					drawquad(corners[0],corners[2],corners[6],corners[4]);

					//011,010,110,111
					drawquad(corners[3],corners[2],corners[6],corners[7]);

					//011,001,101,111
					drawquad(corners[3],corners[1],corners[5],corners[7]);

					//110,100,101,111
					drawquad(corners[6],corners[4],corners[5],corners[7]);
					//glEnd();
					#else
					face[0]=corners[0];//000
					face[1]=corners[1];//001
					face[2]=corners[3];//011
					face[3]=corners[2];//010
					drawquad();

					//face[0]=corners[0];//000
					//face[1]=corners[1];//001
					face[2]=corners[5];//101
					face[3]=corners[4];//100
					drawquad();

					//face[0]=corners[0];//000
					face[1]=corners[2];//010
					face[2]=corners[6];//110
					//face[3]=corners[4];//100
					drawquad();

					face[0]=corners[3];//011
					//face[1]=corners[2];//010
					//face[2]=corners[6];//110
					face[3]=corners[7];//111
					drawquad();

					//face[0]=corners[3];//011
					face[1]=corners[1];//001
					face[2]=corners[5];//101
					//face[3]=corners[7];//111
					drawquad();

					face[0]=corners[6];//110
					face[1]=corners[4];//100
					//face[2]=corners[5];//101
					//face[3]=corners[7];//111
					drawquad();
					//glEnd();
					#endif
				}
			}
		}
		//glEnd();
	}
}
//glEnd();

#endif // GLRENDER_H_INCLUDED

//cout<<"pingas"<<endl;
