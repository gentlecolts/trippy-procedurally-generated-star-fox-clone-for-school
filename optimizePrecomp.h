#ifndef OPTIMIZEPRECOMP_H_INCLUDED
#define OPTIMIZEPRECOMP_H_INCLUDED

for(double z=grid-precompdelta;z>0;z-=precompdelta){
	for(double x=precompdelta;x<grid;x+=precompdelta){
		for(double y=precompdelta;y<grid;y+=precompdelta){
			indx=precompindx(x,y,z);
			//shouldremove[indx]=false;
			blahl=true;

			if(noise[indx]>tolerance){
				/*
				for(int k=-1;k<2;k++){
				for(int i=-1;i<2;i++){
				for(int j=-1;j<2;j++){
					if(noise[precompindx(x+i*precompdelta,y+j*precompdelta,z-k*precompdelta)]<=tolerance){
						blahl=false;
						goto next;
					}
				}}}
				//shouldremove[indx]=true;
				/*/
				for(int i=-1;i<2;i+=2){
					///if any of the non-dagonal, adjacent boxes are empty, then it can be seen
					if(
					noise[precompindx(x+i*precompdelta,y,z)]<=tolerance
					||
					noise[precompindx(x,y+i*precompdelta,z)]<=tolerance
					||
					noise[precompindx(x,y,z-i*precompdelta)]<=tolerance
					){
						blahl=false;
						goto next;
					}
				}
				//*/
			}
			next:
			shouldremove[indx]=blahl;
		}
	}
}

for(double z=grid-precompdelta;z>0;z-=precompdelta){
	for(double x=precompdelta;x<grid;x+=precompdelta){
		for(double y=precompdelta;y<grid;y+=precompdelta){
			indx=precompindx(x,y,z);
			if(shouldremove[indx]){
				noise[indx]=tolerance-12;
			}
		}
	}
}

#endif // OPTIMIZEPRECOMP_H_INCLUDED
