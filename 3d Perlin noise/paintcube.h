#ifndef PAINTCUBE_H_INCLUDED
#define PAINTCUBE_H_INCLUDED

//double scl2;
double delt2;
for(double z=grid-1;z>lowz;z-=(delt2=delta/(grid-z*z/grid)) ){//z-=delta/(grid* (1-z*z/(grid*grid)) )
//for(double z=delta/20+lowz;z<grid;z-=delta/(grid-z*z/grid) ){
	for(double x=0;x<grid;x+=delta){
		for(double y=0;y<grid;y+=delta){
			if(perlin.get(x,y,z+zshft)>tolerance){
				scl=d/(d+z/(grid)+raise);//plus raise so that the grid is not against the screen
				scl2=d/(d+(z+delt2)/(grid)+raise);

				//it is not just  min or max of scl and scl2 because of the sign provided by the coordinate
				xleft  =xmax*( min((x-grid2)*scl,(x-grid2)*scl2) +grid2)/grid;
				ybottom=ymax*( min((y-grid2)*scl,(y-grid2)*scl2) +grid2)/grid;
				xright =xmax*( max((x-grid2+delta)*scl,(x-grid2+delta)*scl2) +grid2)/grid;
				ytop   =ymax*( max((y-grid2+delta)*scl,(y-grid2+delta)*scl2) +grid2)/grid;

				xleft=max((int)(left),0);
				xright=min((int)(xright),xmax);
				ybottom=max((int)(ybottom),0);
				ytop=min((int)(ytop),ymax);

				for(int i=xleft;i<=(int)xright;i++){
					for(int j=ybottom;j<=(int)ytop;j++){
						if(max((grid*i/xmax-grid2)/scl2,x)<min((grid*i/xmax-grid2)/scl,x+delta)){

							#define xtmp ((grid*i/xmax-grid2)/scl+grid2-x)//(x-grid*i/xmax)
							#define ytmp ((grid*j/ymax-grid2)/scl+grid2-y)//(y-grid*j/ymax)
							#define ztmp (z-lowz)

							vals[i+xmax*j].dist=ztmp*ztmp;///FIXME: almost but not quite

							#undef xtmp
							#undef ytmp
							#undef ztmp
						}
						//else if(x*x+y*y<100){vals[i+xmax*j].dist=1;}
					}
				}
			}
		}
	}
}
#endif // PAINTCUBE_H_INCLUDED
