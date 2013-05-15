#include "guiIO.h"
#include <fstream>
using namespace std;

stringOutput::stringOutput(guifont* fontPntr,string str):font(fontPntr){
//	init();
	setString(str);
}
stringOutput::stringOutput(guifont* fontPntr,int xPos,int yPos,string str):font(fontPntr){
//	init();
	setString(str);
	dest.x=xPos;
	dest.y=yPos;
}
void stringOutput::setString(string s){
	SDL_FreeSurface(pic);
	pic=font->getString(s);
	this->s=s;

	if(pic!=NULL){
		bounds.w=pic->w;
		bounds.h=pic->h;
		cout<<"string's width: "<<pic->w<<"\theight: "<<pic->h<<endl;
	}
}
void stringOutput::append(char c){
}
void stringOutput::append(string s){
}
void stringOutput::del(int num){
}
void stringOutput::clr(){
}
//void stringOutput::update(){}
void stringOutput::setBaseLeftPos(int x,int y){
	dest.x=x;
	dest.y=y-font->base;
}


inputScreen::inputScreen(SDL_Event* evnt,guifont* fontPntr,string str):stringOutput(fontPntr,str),e(evnt){
}
inputScreen::inputScreen(SDL_Event* evnt,guifont* fontPntr,int xPos,int yPos,string str):stringOutput(fontPntr,xPos,yPos,str),e(evnt){
}
void inputScreen::update(){
}
