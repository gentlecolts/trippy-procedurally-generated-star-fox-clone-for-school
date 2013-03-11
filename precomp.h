#ifndef PRECOMP_H_INCLUDED
#define PRECOMP_H_INCLUDED

//cout<<"better get here..."<<endl;
//double z2;
//for(double z=lowz+delta/10;z<grid;z-=delta/5){
for(double z=grid-delta/10;z>lowz;z-=delta/5){
//for(double z=grid-1;z>lowz;z-=delta/(grid-z*z/grid) ){//z-=delta/(grid* (1-z*z/(grid*grid)) )
//for(double z=delta/20+lowz;z<grid;z+=delta/(grid-z*z/grid) ){
	//z2=(z-lowz)*(z-lowz);
	for(double x=0;x<grid;x+=delta){
		for(double y=0;y<grid;y+=delta){
			//if(noise[precompindx(x,y,z+zshft)].dist>tolerance){
			if(noise[precompindx(x,y,z+zshft)]>tolerance){
				//cout<<"got here"<<endl;
				scl=d/(d+z/grid+raise);
				/*really fucking cool, but not what we want
				xleft=max((int)(xmax*((x-camx-delt2)*scl+camx)/grid),0);
				xright=min((int)(xmax*((x-camx+delt2)*scl+camx)/grid),xmax);
				ybottom=max((int)(ymax*((y-camy-delt2)*scl+camy)/grid),0);
				ytop=min((int)(ymax*((y-camy+delt2)*scl+camy)/grid),ymax);
				/*/
				xleft=max((int)(xmax*((x-camx-delt2)*scl+grid2)/grid),0);
				xright=min((int)(xmax*((x-camx+delt2)*scl+grid2)/grid),xmax);
				ybottom=max((int)(ymax*((y-camy-delt2)*scl+grid2)/grid),0);
				ytop=min((int)(ymax*((y-camy+delt2)*scl+grid2)/grid),ymax);
				//*/


				/*
				if(vals[xleft+xmax*ytop].dist<0 ||
					vals[xleft+xmax*ybottom].dist<0 ||
					vals[xright+xmax*ytop].dist<0 ||
					vals[xright+xmax*ybottom].dist<0){
				//*/
					for(int i=xleft;i<=xright;i++){
						for(int j=ybottom;j<=ytop;j++){
								//vals[i+xmax*j].dist=(x-grid2)*(x-grid2)+(y-grid2)*(y-grid2)+(z2+raise)*(z2+raise);
								#define xtmp ((grid*i/xmax-grid2)/scl+grid2-x)//(x-grid*i/xmax)
								#define ytmp ((grid*j/ymax-grid2)/scl+grid2-y)//(y-grid*j/ymax)
								#define ztmp (z-lowz)
								//*
								vals[i+xmax*j].dist=ztmp*ztmp;///FIXME: almost but not quite
								//vals[i+xmax*j].dist=z2;

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
						}
					}
				///}//endif
			}
		}
	}
}

#endif // PRECOMP_H_INCLUDED
