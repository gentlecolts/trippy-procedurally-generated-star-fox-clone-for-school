#ifndef GUIOBJ_H_INCLUDED
#define GUIOBJ_H_INCLUDED

#include <string>
#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>
#include <SDL/SDL_image.h>

#include "linkedlist.h"

struct mouse{
	uint8_t state;
	int x,y;
	bool isDown,downPrev;
};

/**
#define dbgType
//*/

class picture{
protected:
	//unsigned int refcount;//assume that each one is unique
	static linkedlist<picture*> objects;
	void init();

	#ifdef dbgType
	int type;
	#endif
public:
	static mouse mousepos;
	SDL_Surface* pic;
	SDL_Rect bounds;
	SDL_Rect dest;//destination bounding box, x and y of this are the coordinates that the pic is drawn to
	static SDL_Surface* target;
	float alpha;
	bool visible;
	picture(const char* file);
	picture(SDL_Surface* pict=NULL);
	virtual void setPos(int x,int y);
	virtual ~picture();
	virtual void draw();
	virtual void draw(SDL_Surface* src);
	virtual void update();
	virtual void scaleAlpha(SDL_Surface* src);
	virtual void scaleAlpha(SDL_Surface* src,float a);
	static void updateAll(SDL_Event* e);
};

void GUI_Free(picture* obj);

class button:public picture{
protected://because why use private? someone may want to subclass this at some point
	static void nullfn(button*){return;}
	bool isDown;
	virtual void updateBtn();
public:
	void (*fn)(button*);
	bool hasMouseover,hasClicked;//does it have specific pictures for each
	SDL_Surface *over,*down;
	SDL_Surface *current;
	button(SDL_Surface* pict,SDL_Surface* mouseover=NULL,SDL_Surface* mousedown=NULL);
	button(const char* file,const char* mouseover="\0",const char* mousedown="\0");
	virtual void update();
};

//void loadpic(std::string path);
void initializeIMG();

#endif // GUIOBJ_H_INCLUDED
