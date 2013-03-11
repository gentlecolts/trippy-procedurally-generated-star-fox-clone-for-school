#include "PlayerShip.h"

float playerModel[18][6]={
        {0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f},
        {0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f},
        {0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f},
        {0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 2.0f, 0.0f, 1.0f, 0.f, 0.0f},
        {0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f},
    };

PlayerShip::PlayerShip()
{
    //model=&playerModel;
    modelSize=15;
}

PlayerShip::~PlayerShip()
{
    //dtor
}

void PlayerShip::render() {
    glTranslatef(camx*4/3, camy*4/3, 0);

    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glRotatef(velX/maxV*90, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES); // of the pyramid

    for(int i=0;i<modelSize;i++) {
        glColor3f(playerModel[i][4],playerModel[i][5],playerModel[i][6]);
        glVertex3f(playerModel[i][1],playerModel[i][2],playerModel[i][3]);

    }
}
