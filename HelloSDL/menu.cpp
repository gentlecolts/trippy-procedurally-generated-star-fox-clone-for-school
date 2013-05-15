//
//  menu.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "menu.h"
#include "globals.h"
#include "IO.h"
#include "gameController.h"

button *playButton, *quitButton;

void play(button *b) {
	cout<<"PLAY!"<<endl;
	inGame=true;
}

void launchMenu() {
	initializeIMG();
	
	SDL_Surface *s1=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuPlay.png"),
		*s2=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuPlayH.png"),
		*s3=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuPlayP.png"),
		*s4=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuQuit.png"),
		*s5=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuQuitH.png"),
		*s6=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuQuitP.png");
	
	if(s1==NULL || s2==NULL || s3==NULL || s4==NULL || s5==NULL || s6==NULL) {
		cout<<"Image not found: menuPlayTest"<<endl;
	}
	
	playButton=new button(s1,s2,s3);
	quitButton=new button(s4,s5,s6);
	
	playButton->setPos(0, 0);
	quitButton->setPos(0, 300);
	
	playButton->fn=play;
	quitButton->fn=quit;
}
