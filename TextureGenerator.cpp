//
//  TextureGenerator.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/19/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "TextureGenerator.h"
#include "imports.h"

void generateLaserGradient(int w,int h,GLubyte* data) {
	int texW;
	for(texW=1;texW<w || texW<h;texW*=2);
	
	data=new GLubyte[texW*texW*4];
	
	for(int i=texW/2-w/2;i<texW/2+w/2;i++) {
		for(int j=texW/2-h/2;j<texW/2+h/2;j++) {
			
		}
	}
}