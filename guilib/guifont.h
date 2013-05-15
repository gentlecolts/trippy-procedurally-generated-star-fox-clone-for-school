#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED
#include <SDL/SDL.h>
#include <string>

struct fontchar{
	uint32_t picpos;
	uint16_t w;
	char c;

	char operator =(char c);
	bool operator ==(char c);
	bool operator >(char c);
	bool operator <(char c);
	bool operator >=(char c);
	bool operator <=(char c);
};

class guifont{
protected:
	SDL_Surface* bitmap;
	int numchars;
	fontchar* chars;
	uint16_t height;

	virtual void init(std::string chars,SDL_Surface* data,SDL_Surface* map);
public:
	int base,horiz_spacing,vert_spacing;
	guifont(std::string chars,SDL_Surface* data);
	guifont(std::string chars,SDL_Surface* data,SDL_Surface* map);
	guifont(std::string chars,const char* datafile);
	guifont(std::string chars,const char* datafile,const char* mapfile);
	virtual ~guifont();
	virtual SDL_Rect getChar(char c,fontchar* character);
	virtual int getIndex(char c);
	virtual int getCharWidth(char c);
	virtual int getStrWidth(std::string s);
	virtual int getStrHeight(std::string s);
	virtual int getHeight();
	virtual SDL_Rect getStrDims(std::string s);
	virtual SDL_Surface* getString(std::string s);
};

#endif // FONT_H_INCLUDED
