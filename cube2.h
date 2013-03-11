#ifndef CUBE2_H_INCLUDED
#define CUBE2_H_INCLUDED


for(double z=grid-1;z>lowz;z-=delta){
//for(double z=grid-1;z>lowz;z-=delta/(grid-z*z/grid) ){//z-=delta/(grid* (1-z*z/(grid*grid)) )
//for(double z=delta/20+lowz;z<grid;z-=delta/(grid-z*z/grid) ){
	for(double x=grid-1;x>lowz;x-=delta){
		for(double y=grid-1;y>lowz;y-=delta){
			if(perlin.get(x,y,z+zshft)>tolerance){
				#define d3 delta/10
				for(double dz=0;dz<delta;dz+=d3){
					scl=d/(d+(z+dz)/grid+raise);
					for(double dx=0;dx<delta;dx+=d3){
						for(double dy=0;dy<delta;dy+=d3){
							i=xmax*((x-grid2)*scl+grid2)/grid;
							j=ymax*((y-grid2)*scl+grid2)/grid;
							if(i>=0 && i<xmax && j>=0 && j<ymax){
								#define xtmp (x-grid*i/(double)xmax)
								#define ytmp (y-grid*j/(double)ymax)
								vals[i+xmax*j].dist=xtmp*xtmp+ytmp*ytmp+(z-lowz)*(z-lowz);
								#undef xtmp
								#undef ytmp
								//if(vals[i+xmax*j].dist>maxdst){maxdst=vals[i+xmax*j].dist
							}
						}
					}
				}
			}//end if
		}
	}
}

#endif // SOLVE2_H_INCLUDED
