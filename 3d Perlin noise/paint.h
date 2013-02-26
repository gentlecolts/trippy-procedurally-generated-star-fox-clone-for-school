#ifndef PAINT_H_INCLUDED
#define PAINT_H_INCLUDED

//const double blahsdf=d/(grid-1);for(double z=grid-1;z>=0;z-=abs(blahsdf-z)){
for(double z=grid-1;z>lowz;z-=delta/5){
//for(double z=grid-1;z>lowz;z-=delta/(grid-z*z/grid) ){//z-=delta/(grid* (1-z*z/(grid*grid)) )
//for(double z=delta/20+lowz;z<grid;z-=delta/(grid-z*z/grid) ){
	for(double x=0;x<grid;x+=delta){
		for(double y=0;y<grid;y+=delta){
			//cout<<"getting ("<<x<<", "<<y<<", "<<z<<")"<<endl;
			//val=perlin.get(x,y,z+zshft);
			//cout<<val<<",";
			//cout<<"success"<<endl;

			//#define blahl
			#ifndef blahl
			if(perlin.get(x,y,z+zshft)>tolerance){
				//delta=delt2/5;
			#endif
				//for(double z2=z+5*delta;z2>=z;z2-=delta/10){
					#define z2 z
					scl=d/(d+z2/(grid)+raise);//plus raise so that the grid is not against the screen
					/*
					xleft=xmax*((x-grid2)*scl+grid2)/grid;
					ybottom=ymax*((y-grid2)*scl+grid2)/grid;
					vals[(int)xleft+xmax*(int)ybottom].dist=(x-grid2)*(x-grid2)+(y-grid2)*(y-grid2)+(z+raise)*(z+raise);
					/*/
					//xleft=max((int)(xmax*((x-grid2)*scl+grid2)/grid),0);
					//xright=min((int)(xmax*((x-grid2+delta)*scl+grid2)/grid),xmax);
					//ybottom=max((int)(ymax*((y-grid2)*scl+grid2)/grid),0);
					//ytop=min((int)(ymax*((y-grid2+delta)*scl+grid2)/grid),ymax);

					xleft=max((int)(xmax*((x-camx-delt2)*scl+grid2)/grid),0);
					xright=min((int)(xmax*((x-camx+delt2)*scl+grid2)/grid),xmax);
					ybottom=max((int)(ymax*((y-camy-delt2)*scl+grid2)/grid),0);
					ytop=min((int)(ymax*((y-camy+delt2)*scl+grid2)/grid),ymax);

					for(int i=xleft;i<=(int)xright;i++){
						for(int j=ybottom;j<=(int)ytop;j++){
							//if(vals[i+xmax*j].dist<0){

								//#if distanceNotDepth==1
								//vals[i+xmax*j].dist=(x-grid2)*(x-grid2)+(y-grid2)*(y-grid2)+(z2+raise)*(z2+raise);
								#define xtmp ((grid*i/xmax-grid2)/scl+grid2-x)//(x-grid*i/xmax)
								#define ytmp ((grid*j/ymax-grid2)/scl+grid2-y)//(y-grid*j/ymax)
								#define ztmp (z2-lowz)
								//*
								vals[i+xmax*j].dist=ztmp*ztmp;///FIXME: almost but not quite
								//if(vals[i+xmax*j].dist<0){cout<<"wtf"<<endl;}
								/*/
								const double tmp=xtmp*xtmp+ytmp*ytmp+ztmp*ztmp;
								if(tmp<vals[i+xmax*j].dist || vals[i+xmax*j].dist<0){vals[i+xmax*j].dist=tmp;}
								//*/
								#undef xtmp
								#undef ytmp
								#undef ztmp
								/*
								#else
								vals[i+xmax*j].dist=z+raise;
								#endif//*/
								//cout<<"set"<<endl;
								//if(vals[i+xmax*j].dist>maxdst){maxdst=vals[i+xmax*j].dist;}
							//}
						}
					}
				//}//*/
			#ifndef blahl
			}
			//else{delta=delt2;}
			#endif
			#undef blahl
			//cout<<"looped"<<endl;
		}
		//chkCloseEvent();
	}
	//delta=delt2;
}
#endif // PAINT_H_INCLUDED
