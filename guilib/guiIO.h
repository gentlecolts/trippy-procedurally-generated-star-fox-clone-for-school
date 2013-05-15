#ifndef GUIIO_H_INCLUDED
#define GUIIO_H_INCLUDED

#include "guifont.h"
#include "guiobj.h"

class stringOutput:public picture{
protected:
	string s;
public:
	guifont* font;
	stringOutput(guifont* fontPntr,string str="");
	stringOutput(guifont* fontPntr,int xPos,int yPos,string str="");
	virtual void setString(string s);
	virtual void append(char c);
	virtual void append(string s);
	virtual void del(int num=1);
	virtual void clr();
	//virtual void update();
	virtual void setBaseLeftPos(int x,int y);
};

class inputScreen:public stringOutput{
public:
	SDL_Event* e;
	inputScreen(SDL_Event* evnt,guifont* fontPntr,string str="");
	inputScreen(SDL_Event* evnt,guifont* fontPntr,int xPos,int yPos,string str="");
	virtual void update();
};

#endif // GUIIO_H_INCLUDED
