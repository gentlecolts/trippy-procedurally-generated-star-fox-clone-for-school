#ifndef PRECOMP2_H_INCLUDED
#define PRECOMP2_H_INCLUDED

double x,y;
for(double z=grid-1;z>lowz;z-=delta/5){
//for(double z=lowz+delta/10;z<grid;z+=delta/5){
//for(double z=grid-1;z>lowz;z-=z+=delta/(grid-z*z/grid)){
//for(double z=delta/20+lowz;z<grid;z+=delta/(grid-z*z/grid) ){
	scl=d/(d+(z+raise)/(grid+raise));
	/*
	xleft=xmax*((0-grid2)*scl+grid2)/grid;
	xright=xmax*((grid-grid2+delta)*scl+grid2)/grid;
	ybottom=ymax*((0-grid2)*scl+grid2)/grid;
	ytop=ymax*((grid-grid2+delta)*scl+grid2)/grid;
	/*/
	xleft=max(xmax*(1-scl)/2,0.0);
	//xright=xmax*(scl*(delta/grid+0.5)+0.5);
	xright=min(xmax*((grid2+delta)*scl+grid2)/grid,(double)xmax);
	ybottom=max(ymax*(1-scl)/2,0.0);
	ytop=min(ymax*((grid2+delta)*scl+grid2)/grid,(double)ymax);
	//*/
	for(int i=xleft;i<=xright;i++){
		x=grid*(i-xleft)/(xright-xleft);
		for(int j=ybottom;j<=ytop;j++){
			y=grid*(j-ybottom)/(ytop-ybottom);
			if(noise[precompindx(x,y,z+zshft)].dist>tolerance){
			//if(smoothxy(x,y,z)>tolerance){
				//if(perlin.get(x,y,z+zshft)>tolerance){
					//*
					#define xtmp (x-grid*i/(double)xmax)
					#define ytmp (y-grid*j/(double)ymax)
					#define ztmp (z-lowz)
					/*/
					#define xtmp x
					#define ytmp y
					#define ztmp (z+d)
					//*/
					vals[i+xmax*j].dist=xtmp*xtmp+ytmp*ytmp+ztmp*ztmp;
					#undef xtmp
					#undef ytmp
					#undef ztmp
					//if(vals[i+xmax*j].dist>maxdst){maxdst=vals[i+xmax*j].dist;}
				//}
			}
		}
	}
}

#endif // PRECOMP2_H_INCLUDED
