#ifndef SOLVE_H_INCLUDED
#define SOLVE_H_INCLUDED

//this is shitty as it baltently disregards the smoothing function
double x,y,z2;
double a,b,c,d;
for(int z=grid-1;z>=0;z--){
	scl=d/(d+(z+raise)/(grid+raise));

	xleft=max(xmax*(1-scl)/2,0.0);
	xright=min(xmax*((grid2+delta)*scl+grid2)/grid,(double)xmax);
	ybottom=max(ymax*(1-scl)/2,0.0);
	ytop=min(ymax*((grid2+delta)*scl+grid2)/grid,(double)ymax);
	//*/
	for(int i=xleft;i<=xright;i++){
		for(int j=ybottom;j<=ytop;j++){
			x=grid*(i-xleft)/(xright-xleft);
			y=grid*(j-yleft)/(yright-yleft);
			z2=perlin.solvez(x,y);
			scl=d/(d+(z+raise)/(grid+raise));

		}
	}
}

#endif // SOLVE_H_INCLUDED
