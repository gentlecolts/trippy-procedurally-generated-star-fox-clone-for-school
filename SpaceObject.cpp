#include "SpaceObject.h"
#include <iostream>

SpaceObject::SpaceObject()
{
    //ctor
}

SpaceObject::~SpaceObject()
{
    //dtor
}

void SpaceObject::render() {
    /*glTranslatef(camx*4/3, camy*4/3, 0);

    gl.glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gl.glRotatef(velX/maxV*90, 0.0f, 1.0f, 0.0f);

    gl.glBegin(GL.GL_TRIANGLES); // of the pyramid

    for(int i=0;i<modelSize;i++) {
        glColor3f(model[i][4],model[i][5],model[i][6]);
        glVertex3f(model[i][1],model[i][2],model[i][3]);

    }*/
}

void SpaceObject::update() {

}
