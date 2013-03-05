#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

const double dt=0.005;
double x,y,z;
double tlow=1,tmax;
//const point3d from(grid-camx,grid-camy,-grid*d);
const point3d from(grid2,grid2,-grid*d);
point3d D(0,0,grid*d);
for(int i=0;i<xmax;i++){
	//D.x=((double)grid)*i/xmax+camx-grid - from.x;
	D.x=((double)grid)*i/xmax - from.x;
	for(int j=0;j<ymax;j++){
		D.y=((double)grid)*j/ymax - from.y;

		//tlow=max(max(-(grid2+from.x)/D.x,-(grid2+from.y)/D.y),-(grid2+from.z)/D.z);
		//tlow=max( max(max(-(grid2+from.x)/D.x,-(grid2+from.y)/D.y),-(grid2+from.z)/D.z) ,1.0);
		//tlow=1;
		//tmax=min(min((grid2-from.x+grid2)/D.x,(grid2-from.y+grid2)/D.y),(grid2-from.z+grid2)/D.z);
		//tmax=min(min((grid-from.x)/D.x,(grid-from.y)/D.y),(grid-from.z)/D.z);
		//tmax=min( min(min((grid2-from.x)/D.x,(grid2-from.y)/D.y),(grid2-from.z)/D.z) ,1+1/d);
		//tmax=1+1/d;
		///note to self: removing the -grid+camx allows looping forever
		/*
		tmax=(D.x>=0) ? ((grid-(from.x-grid+camx))/D.x) : (-(grid+(from.x-grid+camx))/D.x);
		tmax=min(tmax,(D.y>=0) ? ((grid-(from.y-grid+camy))/D.y) : -(grid+(from.y-grid+camy))/D.y);
		tmax=min(tmax,(D.z>=0) ? ((grid-from.z)/D.z) : -(grid+from.z)/D.z);
		/*/
		tmax=(D.x>=0) ? ((3*grid2-camx)/D.x) : (-(grid2+camx)/D.x);
		tmax=min(tmax,(D.y>=0) ? ((3*grid2-camy)/D.y) : -(grid2+camy)/D.y);
		tmax=min(tmax,(D.z>=0) ? ((grid-from.z)/D.z) : -(grid+from.z)/D.z);
		//*/

		/*
		if(tlow>tmax){
			tmax=abs(tmax);
			if(tmax<tlow){swap(tmax,tlow);}
		}//*/
		for(double t=tlow;t<=tmax;t+=dt){
				if(noise[
					precompindx(
						(x=D.x*t+from.x+camx-grid),
						(y=D.y*t+from.y+camy-grid),
						(z=D.z*t+from.z)+zshft
					)]
					>tolerance
					){
					vals[i+xmax*j].dist=x*x+y*y+z*z;
					goto free;
				}
			}
		free:;
	}
}


#endif // TRACE_H_INCLUDED
