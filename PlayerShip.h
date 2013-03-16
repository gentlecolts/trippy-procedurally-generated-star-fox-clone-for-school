#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "SpaceObject.h"

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

class PlayerShip
{
public:
	PlayerShip(){
		//model=&playerModel;
		modelSize=18;
	}

	void render(){
		glTranslatef(0,0,-2);
		glScalef(0.3f,0.3f,0.3f);
		glTranslatef(camx, -camy, 0);

		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glRotatef(velX/maxV*90, 0.0f, 1.0f, 0.0f);

		glBegin(GL_TRIANGLES); // of the pyramid

		for(int i=0;i<modelSize;i++) {
			glColor3f(playerModel[i][3],playerModel[i][4],playerModel[i][5]);
			glVertex3f(playerModel[i][0],playerModel[i][1],playerModel[i][2]);
		}

			  // Font-face triangle
		  /*glColor3f(1.0f, 0.f, 0.0f); // Red
		  glVertex3f(0.0f, 2.0f, 0.0f);
		  glColor3f(0.0f, 1.0f, 0.0f); // Green
		  glVertex3f(0.0f, 0.0f, 0.5f);
		  glColor3f(0.0f, 0.0f, 1.0f); // Blue
		  glVertex3f(1.0f, -1.0f, 0.0f);

		  // Back-face triangle
		  glColor3f(1.0f, 0.0f, 0.0f); // Red
		  glVertex3f(0.0f, 2.0f, 0.0f);
		  glColor3f(0.0f, 1.0f, 0.0f); // Green
		  glVertex3f(0.0f, 0.0f, 0.5f);
		  glColor3f(0.0f, 0.0f, 1.0f); // Blue
		  glVertex3f(-1.0f, -1.0f, 0.0f);
			  // Font-face triangle
		  glColor3f(1.0f, 0.f, 0.0f); // Red
		  glVertex3f(0.0f, 2.0f, 0.0f);
		  glColor3f(0.0f, 1.0f, 0.0f); // Green
		  glVertex3f(0.0f, 0.0f, -0.5f);
		  glColor3f(0.0f, 0.0f, 1.0f); // Blue
		  glVertex3f(1.0f, -1.0f, 0.0f);

		  // Back-face triangle
		  glColor3f(1.0f, 0.0f, 0.0f); // Red
		  glVertex3f(0.0f, 2.0f, 0.0f);
		  glColor3f(0.0f, 1.0f, 0.0f); // Green
		  glVertex3f(0.0f, 0.0f, -0.5f);
		  glColor3f(0.0f, 0.0f, 1.0f); // Blue
		  glVertex3f(-1.0f, -1.0f, 0.0f);

		  glColor3f(0.0f, 1.0f, 0.0f); // Green
		  glVertex3f(0.0f, 0.0f, 0.5f);
		  glVertex3f(0.0f, 0.0f, -0.5f);
		  glColor3f(0.0f, 0.0f, 1.0f); // Blue
		  glVertex3f(-1.0f, -1.0f, 0.0f);

		  glColor3f(0.0f, 1.0f, 0.0f); // Green
		  glVertex3f(0.0f, 0.0f, 0.5f);
		  glVertex3f(0.0f, 0.0f, -0.5f);
		  glColor3f(0.0f, 0.0f, 1.0f); // Blue
		  glVertex3f(1.0f, -1.0f, 0.0f);*/

		glEnd();
	}
protected:
private:
	int modelSize;
};
#include "PlayerShip.h"
#endif // PLAYERSHIP_H
