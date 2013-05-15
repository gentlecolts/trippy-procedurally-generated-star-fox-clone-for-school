#include "guiobj.h"

#include <iostream>
using namespace std;

linkedlist<picture*> picture::objects;
SDL_Surface* picture::target;
mouse picture::mousepos;

void initializeIMG(){
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
}
//picture::picture(const char* file): refcount(0),alpha(1),pic(IMG_Load(file)){
picture::picture(const char* file): pic(IMG_Load(file)),alpha(1){
	init();

	#ifdef dbgType
	type=0;
	#endif
}
//picture::picture(SDL_Surface* pict): refcount(0),alpha(1),pic(pict){
picture::picture(SDL_Surface* pict): pic(pict),alpha(1){
	init();

	#ifdef dbgType
	type=0;
	#endif
}

void picture::init(){
	visible=true;
	bounds.x=0;
	bounds.y=0;

	if(pic==NULL){
		bounds.w=0;
		bounds.h=0;
	}else{
		bounds.w=pic->w;
		bounds.h=pic->h;
	}
	objects.addToBack(this);

	//cout<<"created type: "<<type<<" at: "<<this<<endl;
	//cout<<"created picture object at: "<<this<<endl;
	//printf("created picture object at: %p\n",this);
}

picture::~picture(){//dont forget: this is called after child destructor(s)
	//cout<<"deleted "<<this<<endl;
	node<picture*> *tmp=objects.head,*tmp2=tmp;
	//no need to check for null case, the object has to exist for the destructor to be called,
	//therefore there must always be at least one element in objects when this is called,
	//with the possible exception of multiple threads calling delete on the same object
	//this is/will be fixed by GUI_Free function
	while(tmp->data!=this){//data is of type picture*
		tmp2=tmp;
		tmp=tmp->next;
		/*
		if(tmp==NULL){
			//couldnt find self: panic
			throw(0xf00);//what kind of foo does it throw? ox foo? or maybe some deadbeef? whatever it is, i just hope it hasnt gone baz
		}
		//*/
	}

	if(tmp2==tmp){//at the end or there is only one element
		objects.deletend();
	}else{
		tmp2->next=tmp->next;
		delete tmp;
	}
	SDL_free(pic);
}
void picture::setPos(int x,int y){
	dest.x=x;
	dest.y=y;
}

void picture::updateAll(SDL_Event* e){
	mousepos.state=SDL_GetMouseState(&mousepos.x,&mousepos.y);
	if(e->type==SDL_MOUSEBUTTONDOWN){
		mousepos.isDown=true;
	}else if(e->type==SDL_MOUSEBUTTONUP){
		mousepos.isDown=false;
	}

	node<picture*>* tmp=objects.head;
	while(tmp!=NULL){
		//void* blah=NULL;
		//cout<<tmp<<endl;
		//cout<<tmp->data<<'\t'<<blah<<endl<<endl;
		if(tmp->data!=NULL && tmp->data->visible){
			tmp->data->update();
		}
		tmp=tmp->next;
	}

	mousepos.downPrev=mousepos.isDown;
}
void picture::update(){
	draw();
}

void picture::draw(){
	draw(pic);
}
void picture::draw(SDL_Surface* pic){
	if(pic!=NULL){
		dest.w=target->w;
		dest.h=target->h;

		if(pic->format->BitsPerPixel==32){
			SDL_Surface* src=SDL_ConvertSurface(pic,pic->format,pic->flags);
			//SDL_Surface* src=pic;
			scaleAlpha(src);
			//printf("%*\n",sizeof(SDL_PixelFormat),*pic->format);
			SDL_BlitSurface(src,&bounds,target,&dest);
			SDL_FreeSurface(src);
		}else{
			SDL_SetAlpha(pic,SDL_SRCALPHA | SDL_SRCCOLORKEY,255*alpha);
			//SDL_SetColorKey(pic,SDL_SRCCOLORKEY,((uint32_t)(255*alpha))<<16);
			SDL_BlitSurface(pic,&bounds,target,&dest);
		}

		//printf("%i\n",pic->format->BitsPerPixel);
	}
}

void picture::scaleAlpha(SDL_Surface* src){
	scaleAlpha(src,alpha);
}
void picture::scaleAlpha(SDL_Surface* src,float a){
	int w=src->w,h=src->h;

	uint32_t* pixel=(uint32_t*)src->pixels;
	//uint32_t* pixel=(uint32_t*)ret.pixels;
	#if 1
	for(int i=0;i<w*h;i++){
		//printf("alpha: %f\t%u -> ",a,pixel[i]>>24);
		pixel[i]=(pixel[i]&0x00ffffff) | (((uint32_t)((pixel[i]>>24)*a))<<24);
		//printf("%u\n",pixel[i]>>24);
	}
	#else
	#endif
}

void GUI_Free(picture* obj){
	///TODO: make this thread safe
	delete obj;
}

//note to self: http://msdn.microsoft.com/en-us/library/91563f79(v=VS.80).aspx
button::button(SDL_Surface* pict,SDL_Surface* mouseover,SDL_Surface* mousedown)
: picture(pict),isDown(false),fn(nullfn),hasMouseover(false),hasClicked(false),over(mouseover),down(mousedown){
	//init();//superclass constructor will call init

	#ifdef dbgType
	type=1;
	#endif
}
button::button(const char* file,const char* mouseover,const char* mousedown)
: picture(IMG_Load(file)),isDown(false),fn(nullfn),hasMouseover(false),hasClicked(false),over(IMG_Load(mouseover)),down(IMG_Load(mousedown)){
	//init();//superclass constructor will call init

	#ifdef dbgType
	type=1;
	#endif
}

long tmp_lng;
void button::updateBtn(){
		const int x=mousepos.x-dest.x,y=mousepos.y-dest.y;

#if 1
	if(x>0 && x<dest.w && y>0 && y<dest.h){//if the mouse is over the button and:
		//if(!isDown && mousepos.isDown && !mousepos.downPrev){//clicked(state change only)
		if(mousepos.isDown && !mousepos.downPrev){//clicked(state change only)
			isDown=true;
			current=down;
		}else if(!mousepos.isDown){//the mouse is not pressed

			if(isDown){//and this button was clicked (the button was released)
				fn(this);
			}

			isDown=false;
		}

		if(!isDown){//in the box but not clicked
			current=over;
		}
	}else if(!(isDown && mousepos.isDown)){
		isDown=false;
		current=pic;
	}
#else
///TODO: try and see if it is possible to make a branchless version of this
	if(x>0 && x<dest.w && y>0 && y<dest.h){//if the mouse is over the button and:
		//if(!isDown && mousepos.isDown && !mousepos.downPrev){//clicked(state change only)
		if(mousepos.isDown && !mousepos.downPrev){//clicked(state change only)
			isDown=true;
			current=down;
		}else if(!mousepos.isDown){//the mouse is not pressed

			if(isDown){//and this button was clicked (the button was released)
				fn(this);
			}

			isDown=false;
		}

		if(!isDown){//in the box but not clicked
			current=over;
		}
	}else if(!(isDown && mousepos.isDown)){
		isDown=false;
		current=pic;
	}

	isDown=( (x>0 && x<dest.w && y>0 && y<dest.h) && (
#endif
#if 1
	/*
	current+=(current==down && down==NULL)*(over-current);
	//current=(current==NULL)*pic+(current!=NULL)*current;
	//current=(current==NULL)*pic+(1-(current==NULL))*current;
	//current=(current==NULL)*pic+current-(current==NULL)*current;
	//current=current+(current==NULL)*(pic-current);
	current+=(current==NULL)*(pic-current);
	/*/
	#if 0
	tmp_lng=(long)current;
	tmp_lng^=(tmp_lng==(long)down && down==NULL)*((long)over^tmp_lng);
	//tmp^=(tmp==NULL)*((long)pic^tmp);
	//current=(SDL_Surface*)tmp;
	current=(SDL_Surface*)(tmp_lng^((tmp_lng==NULL)*((long)pic^tmp_lng)));
	#else
	tmp_lng=(long)current;
	tmp_lng^=(tmp_lng==(long)down && down==0)*((long)over^tmp_lng);
	current=(SDL_Surface*)(tmp_lng^((tmp_lng==0)*((long)pic^tmp_lng)));
	#endif
	//*/
#else
	if(current==down && down==NULL){
		current=over;
	}
	if(current==NULL){
		current=pic;
	}
#endif
}

void button::update(){
	updateBtn();
	draw(current);
}
