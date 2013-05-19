//
//  menu.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "menu.h"
#include "../globals.h"
#include "../IO.h"
#include "../gameController.h"

picture* instruct;
button *playButton, *quitButton;

void play(button *b) {
//	cout<<"PLAY!"<<endl;
	inGame=true;
}

#ifdef WIN32
#include <direct.h>
string getpath(){
	//char result[MAX_PATH];
	//return string(result,GetPath(NULL,result,MAX_PATH));
	char dir[FILENAME_MAX];
	return _getcwd(dir,sizeof(dir));
}
#endif

void launchMenu() {
	initializeIMG();

	#ifdef WIN32
	//*
	#if false
	SDL_Surface *s1=IMG_Load("Images/menuPlay.png"),
		*s2=IMG_Load("Images/menuPlayH.png"),
		*s3=IMG_Load("Images/menuPlayP.png"),
		*s4=IMG_Load("Images/menuQuit.png"),
		*s5=IMG_Load("Images/menuQuitH.png"),
		*s6=IMG_Load("Images/menuQuitP.png"),
		*s7=IMG_Load("Images/instructions.png");
	#else
	cout<<"./"<<endl;
	SDL_Surface *s1=IMG_Load(".\\menuPlay.png"),
		*s2=IMG_Load(".\\menuPlayH.png"),
		*s3=IMG_Load(".\\menuPlayP.png"),
		*s4=IMG_Load(".\\menuQuit.png"),
		*s5=IMG_Load(".\\menuQuitH.png"),
		*s6=IMG_Load(".\\menuQuitP.png"),
		*s7=IMG_Load(".\\instructions.png");
	#endif
	/*/
	string path=getpath();
	cout<<path<<endl;
	cout<<(path+"\\menuPlay.png").c_str()<<endl;
	SDL_Surface *s1=IMG_Load((path+"\\menuPlay.png").c_str()),
		*s2=IMG_Load((path+"\\menuPlayH.png").c_str()),
		*s3=IMG_Load((path+"\\menuPlayP.png").c_str()),
		*s4=IMG_Load((path+"\\menuQuit.png").c_str()),
		*s5=IMG_Load((path+"\\menuQuitH.png").c_str()),
		*s6=IMG_Load((path+"\\menuQuitP.png").c_str()),
		*s7=IMG_Load((path+"\\instructions.png").c_str());
	//*/
	#else
	SDL_Surface *s1=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuPlay.png"),
		*s2=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuPlayH.png"),
		*s3=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuPlayP.png"),
		*s4=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuQuit.png"),
		*s5=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuQuitH.png"),
		*s6=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/menuQuitP.png"),
		*s7=IMG_Load("/Users/jonahchazan/Desktop/trippy-procedurally-generated-star-fox-clone-for-school/Images/instructions.png");
	#endif

	if(s1==NULL || s2==NULL || s3==NULL || s4==NULL || s5==NULL || s6==NULL) {
		cout<<"Image not found: menuPlayTest"<<endl;
	}

	delete instruct;
	delete playButton;
	delete quitButton;
	instruct=new picture(s7);
	playButton=new button(s1,s2,s3);
	quitButton=new button(s4,s5,s6);

	instruct->setPos(0,0);
	playButton->setPos(0, 0);
	quitButton->setPos(0, 300);

	playButton->fn=play;
	quitButton->fn=quit;
}
