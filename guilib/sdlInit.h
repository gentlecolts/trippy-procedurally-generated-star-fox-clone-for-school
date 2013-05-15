#ifndef SDLINIT_H_INCLUDED
#define SDLINIT_H_INCLUDED

#if ogl
void glPreInit(){
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);//must be power of 2 for anti aliasing
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	/*
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,8);
	//*/

	/*
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);//Anti aliasing
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,2);//how much antialiasing
	//*/
}

void glInit(){
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	//GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat mat_diffuse[] = { 100.0, 100.0, 100.0, 1.0 };
	GLfloat light_position[] = {0,0,0,1};
	glShadeModel(GL_SMOOTH);
	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,1);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,1);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.125);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	glClearColor(0,0,0,0);

	glViewport(0,0,xmax,ymax);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//const float rar=(float)xmax/(float)ymax;
	//gluPerspective(viewangle,rar,1.0,1024.0);
	//gluPerspective(viewangle,1,1.0,-1);
	//glOrtho(0,xmax,ymax,0,1,-1);
	//glFrustum(0,xmax,ymax,0,d,2);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();

	GLenum error=glGetError();
	if(error!=GL_NO_ERROR){
		//printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		cout<<"Error initializing OpenGL! "<<gluErrorString(error)<<endl;
		exit(0x91d13d);//gl died );
	}
}
#endif

void initsdl(){
	putenv("SDL_VIDEO_WINDOW_POS=center");
	putenv("SDL_VIDEO_CENTER=1");

	#if ogl
	glPreInit();
	#endif
	SDL_Init(SDL_INIT_EVERYTHING);

	#if ogl
	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_HWPALETTE | SDL_HWACCEL | SDL_DOUBLEBUF | SDL_SRCALPHA | SDL_OPENGL);
	#else
	//screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_HWPALETTE | SDL_HWACCEL | SDL_DOUBLEBUF | SDL_SRCALPHA);
	screen=SDL_SetVideoMode(xmax,ymax,32,SDL_HWSURFACE | SDL_HWPALETTE | SDL_HWACCEL | SDL_DOUBLEBUF | SDL_SRCALPHA | SDL_ASYNCBLIT);
	#endif
	pixels=(uint32_t*)screen->pixels;

	picture::target=screen;///THIS IS IMPORTANT

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	#if ogl
	glInit();
	#endif
}

#endif // SDLINIT_H_INCLUDED
