//
//  ImageConverter.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "ImageConverter.h"
#include "../imports.h"

int loadTexture(SDL_Surface *tex)
{
    GLuint texture;

    if(tex)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, tex->w, tex->h,
					 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        printf("OK\n");
        SDL_FreeSurface(tex);
    }
    else
    {
        printf("Failed\nQuitting...");
        SDL_Quit();
        exit(-1);
    }

    return texture;
}
