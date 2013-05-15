#include "guifont.h"
#include <SDL/SDL_Image.h>
#include <iostream>
using namespace std;

char fontchar::operator =(char C){return c=C;}
bool fontchar::operator ==(char C){return c==C;}
bool fontchar::operator >(char C){return c>C;}
bool fontchar::operator <(char C){return c<C;}
bool fontchar::operator >=(char C){return c>=C;}
bool fontchar::operator <=(char C){return c<=C;}


void guifont::init(string charlist,SDL_Surface* data,SDL_Surface* mapPic){
	uint32_t *pixels,backcol,basecol;
	if(mapPic==NULL){
		pixels=(uint32_t*)data->pixels;
	}else{
		pixels=(uint32_t*)mapPic->pixels;
		printf("map: %p\n",mapPic);
	}
	backcol=pixels[0];

	this->base=-1;
	this->bitmap=data;
	this->chars=new fontchar[charlist.length()];
	this->height=data->h;
	this->numchars=charlist.length();
	this->horiz_spacing=0;
	this->vert_spacing=0;

	const int w=data->w,h=data->h;
	for(int i=0;i<h;i++){
		if(pixels[w*i]!=backcol){
			base=i;
			basecol=pixels[w*i];
			break;
		}
	}
	if(base==-1){
		base=0;
		basecol=backcol;
	}

	printf("basecol: %x\tbackcol: %x\n",basecol,backcol);

	int c=0,i=1;
	bool hascolor=false,inchar=false;
	while(c<charlist.length()){//for each character we need
		hascolor=false;
		for(int j=0;j<h;j++){
			if(pixels[i+h*j]!=backcol && pixels[i+h*j]!=basecol){
				printf("at (%i,%i) color %x\n",i,j,pixels[i+h*j]);
				hascolor=true;
				break;
				//hastrans=(((pixels[i+h*j]>>24)&0xff)<SDL_ALPHA_OPAQUE);
			}
		}

		if(hascolor && !inchar){//beginning of char
			chars[c]=charlist[c];
			chars[c].picpos=i;
			inchar=true;
			//cout<<"from: "<<i<<'\t';
		}else if(!hascolor && inchar){//end of char
			chars[c].w=i-chars[c].picpos;//dont need to add 1 because this i is outside of the character
			cout<<"to: "<<i<<"\tchar: "<<chars[c].c<<"\tw: "<<chars[c].w<<"\tat: "<<chars[c].picpos<<endl;
			c++;
			inchar=false;
		}
		++i;
	}
}

guifont::guifont(string chars,SDL_Surface* data){init(chars,data,NULL);}
guifont::guifont(string chars,SDL_Surface* data,SDL_Surface* map){init(chars,data,map);}
guifont::guifont(string chars,const char* datafile){init(chars,IMG_Load(datafile),NULL);}
guifont::guifont(string chars,const char* datafile,const char* mapfile){init(chars,IMG_Load(datafile),IMG_Load(mapfile));}

guifont::~guifont(){
	SDL_free(bitmap);
	delete[] chars;
}

int guifont::getIndex(char c){
	for(int i=0;i<numchars;i++){///TODO: use a binary search instead
		if(chars[i]==c){
			return i;
		}
	}
	return -1;
}

SDL_Rect guifont::getChar(char c,fontchar* character){
	int i=getIndex(c);
	SDL_Rect rect;

	if(i<0){
		rect.x=0;
		rect.w=0;
	}else{
		rect.x=chars[i].picpos;
		rect.w=chars[i].w;
		character->c=chars[i].c;
		character->picpos=chars[i].picpos;
		character->w=chars[i].w;
	}

	rect.y=0;
	//rect.h=this->height;
	rect.h=getHeight();
	return rect;
}

int guifont::getCharWidth(char c){
	int i=getIndex(c);
	if(i<0){
		return -1;
	}else{
		return chars[i].w;
	}
}
int guifont::getStrWidth(string s){
	int len=0,maxlen=0,linenum=1;
	int charwid;
	for(int i=0;i<s.length();i++){
		if(s[i]=='\n' || s[i]=='\r'){
			linenum++;
			maxlen=max(len,maxlen);
			len=0;
		}else{
			charwid=getCharWidth(s[i]);
			len+=(charwid>0)?charwid:0;
		}
	}
	return max(maxlen,len);
}
int guifont::getHeight(){return height;}
int guifont::getStrHeight(string s){
	int lines=1;
	for(int i=0;i<s.length();i++){
		lines+=(s[i]=='\n' || s[i]=='\r');
	}
	return getHeight()*lines+vert_spacing*(lines-1);
}
SDL_Rect guifont::getStrDims(string s){
	SDL_Rect rect;
	rect.w=getStrWidth(s);//ineffecient, but whatever (should combine these two instead of calling them)
	rect.h=getStrHeight(s);
	return rect;
}

SDL_Surface* guifont::getString(string s){
	const uint32_t
		rmask=0x00ff0000,
		gmask=0x0000ff00,
		bmask=0x000000ff,
		amask=0xff000000;
	SDL_Surface* str=SDL_CreateRGBSurface(SDL_SRCALPHA | SDL_HWSURFACE,getStrWidth(s),getStrHeight(s),32,rmask,gmask,bmask,amask);
	int x=0,y=0;
	SDL_Rect rect,dstrect;
	fontchar c;
	for(int i=0;i<s.length();i++){
		rect=getChar(s[i],&c);
		dstrect.x=x;
		dstrect.y=y;
		SDL_BlitSurface(bitmap,&rect,str,&dstrect);
		cout
			<<"blitted char: "<<c.c
			<<"\tx: "<<x
			<<"\ty: "<<y
			<<"\tw: "<<rect.w
			<<"\th: "<<rect.h
			<<"\tchar w: "<<c.w
			<<endl;
		x+=c.w+horiz_spacing;
	}

	return str;
}
