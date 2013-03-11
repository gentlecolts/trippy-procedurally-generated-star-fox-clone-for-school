#ifndef OPTIMIZEPRECOMP2_H_INCLUDED
#define OPTIMIZEPRECOMP2_H_INCLUDED

for(int i=1;i<res-1;i++){
	for(int j=1;j<res-1;j++){
		for(int k=1;k<res-1;k++){
			indx=i+res*(j+res*k);
			//shouldremove[indx]=false;
			blahl=true;

			if(noise[indx]>tolerance){
				//*
				for(int x=-1;x<2;x++){
				for(int y=-1;y<2;y++){
				for(int z=-1;z<2;z++){
					if(noise[i+x+res*(j+y+res*(k+z))]<=tolerance){
						blahl=false;
						goto next;
					}
				}}}
				//shouldremove[indx]=true;
				/*/
				for(int h=-1;h<2;h+=2){
					///if any of the non-dagonal, adjacent boxes are empty, then it can be seen
					if(
					noise[i+h+res*(j+res*k)]<=tolerance
					||
					noise[i+res*(j+h+res*k)]<=tolerance
					||
					noise[i+res*(j+res*(k+h))]<=tolerance
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

for(int i=0;i<res3;i++){
	if(shouldremove[i]){
		noise[i]=tolerance-1;
	}
}

#endif // OPTIMIZEPRECOMP2_H_INCLUDED
