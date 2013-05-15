//
//  menu.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "menu.h"
#include "globals.h"
#include "gameController.h"

button *playButton;

void play(button *b) {
	cout<<"PLAY!"<<endl;
	inGame=true;
}

void launchMenu() {
	initializeIMG();
	
	SDL_Surface *s1=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuPlayTest.png"),
		*s2=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuPlayTestH.png"),
		*s3=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuPlayTestC.png");
	
	if(s1==NULL || s2==NULL || s3==NULL) {
		cout<<"Image not found: menuPlayTest"<<endl;
	}
	
	playButton=new button(s1,s2,s3);
	
	playButton->fn=play;
}
