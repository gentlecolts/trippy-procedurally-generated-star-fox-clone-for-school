#ifndef GLRENDER_H_INCLUDED
#define GLRENDER_H_INCLUDED

point3d corners[8];
int indx;
//glMatrixMode(GL_MODELVIEW);
//glLoadIdentity();

//glBegin(GL_QUADS);
//cout<<"penis"<<endl;
for(double x=0;x<grid;x+=delta/4){
	for(double y=0;y<grid;y+=delta/4){
		//glBegin(GL_QUADS);glColor3f(0.5f,0.5f,0.5f);
		for(double z=0;z<grid;z+=delta){
			if(noise[precompindx(x,y,z+zshft)]>tolerance){

				//cout<<"pingas"<<endl;
				for(int i=-1;i<=1;i+=2){
				for(int j=-1;j<=1;j+=2){
				for(int k=-1;k<=1;k+=2){
				//indx=(((k+1)/2)<<2)|(((j+1)/2)<<1)|((i+1)/2);
				indx=((k+1)<<1)|(j+1)|((i+1)>>1);//acceptable because these are each either 0 or 2
				/*
				corners[0].x=2*(x+i*delt2)/grid-1;
				corners[0].y=2*(y+j*delt2)/grid-1;
				//corners[0].z=2*(z+k*delt2)/grid-1;
				corners[0].z=(z+k*delt2)/grid-0.5;
				/*/
				//corners[indx].x=(x+i*delt2)/grid-0.5;
				//corners[indx].y=(y+j*delt2)/grid-0.5;
				corners[indx].x=2*(x+i*delt2)/grid-1;
				corners[indx].y=2*(y+j*delt2)/grid-1;
				//corners[indx].z=-(z+k*delt2)/grid-0.5;
				//corners[indx].z=-2*(z+k*delt2)/grid-1;
				corners[indx].z=-(z+k*delt2)-1;
				//*/
				}}}

				//glBegin(GL_QUADS);glColor3f(0.5f,0.5f,0.5f);
				///zyx
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
				//face[3]=corners[6];//100
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

				///only 5 faces as we never see the backs of the cubes
				//glEnd();
			}
		}
		//glEnd();
	}
}
//glEnd();

#endif // GLRENDER_H_INCLUDED
