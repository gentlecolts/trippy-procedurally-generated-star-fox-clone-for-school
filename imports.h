#ifndef IMPORTS_H_INCLUDED
#define IMPORTS_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include <cmath>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL_image/SDL_image.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>
#endif

#endif // IMPORTS_H_INCLUDED
