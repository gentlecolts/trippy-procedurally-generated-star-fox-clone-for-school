#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

const double dt=0.005;
//const double dt=0.005;
double x,y,z;
double tlow=0,//1,
		tmax;
//const point3d from(grid-camx,grid-camy,-grid*d);
const point3d from(grid2,grid2,-grid*d);
point3d D(0,0,grid*d);

const double xshft=camx-grid2,yshft=camy-grid2;

///creative names incomming
const double consts[]={
	/*
	3*grid2-camx,-(grid2+camx),
	3*grid2-camy,-(grid2+camy),
	grid-from.z,-(grid+from.z),
	/*/
	grid-xshft,-(grid2+camx),
	grid-yshft,-(grid2+camy),
	//grid-from.z,-(grid+from.z)
	grid*(d+1),grid*(d-1)
	//*/
	};

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

		//tmax=(D.x>=0) ? ((3*grid2-camx)/D.x) : (-(grid2+camx)/D.x);
		//tmax=min(tmax,(D.y>=0) ? ((3*grid2-camy)/D.y) : -(grid2+camy)/D.y);
		//tmax=min(tmax,(D.z>=0) ? ((grid-from.z)/D.z) : -(grid+from.z)/D.z);

		tmax=(D.x>=0) ? consts[0]/D.x : consts[1]/D.x;
		tmax=min(tmax,(D.y>=0) ? consts[2]/D.y : consts[3]/D.y);
		tmax=min(tmax,(D.z>=0) ? consts[4]/D.z : consts[5]/D.z);
		//*/


		for(double t=tlow;t<=tmax;t+=dt){
		//for(double t=tlow;t<=tmax;t+=dt*(t+d)){
			#if 0
			if(noise[
				precompindx(
					/*
					(x=D.x*t+from.x+camx-grid),
					(y=D.y*t+from.y+camy-grid),
					(z=D.z*t+from.z)+zshft
					/*/
					(x=D.x*t+xshft),
					(y=D.y*t+yshft),
					(z=D.z*t+from.z)+zshft
					//*/
				)]
				>tolerance
				){
				vals[i+xmax*j].dist=(x-xshft)*(x-xshft)+(y-yshft)*(y-yshft)+(z+grid*d)*(z+grid*d);
				goto free;
			}
			#else
			#if shadenorm
			const int preindx=precompindx(D.x*t+xshft,D.y*t+yshft,D.z*t+from.z+zshft);
			if(noise[preindx]>tolerance){
				normals[i+xmax*j]=normlist[preindx];
			#else
			if(noise[
				precompindx(
					D.x*t+xshft,
					D.y*t+yshft,
					D.z*t+from.z+zshft
				)]
				>tolerance
			){
			#endif
				vals[i+xmax*j].dist=(D.x*D.x+D.y*D.y+D.z*D.z)*t*t;
				goto free;
			}
			#endif
		}
		free:;
	}
}


#endif // TRACE_H_INCLUDED
