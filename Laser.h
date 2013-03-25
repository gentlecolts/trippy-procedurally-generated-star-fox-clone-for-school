#ifndef LASER_H
#define LASER_H

class Laser
{
public:
    double xpos,ypos,zpos,xvel,yvel,zvel,xrot,yrot,zrot;

	void init(double x, double y, double z, double xr, double yr, double zr){

		xpos=x;
		ypos=y;
		zpos=z;

        xrot=xr;
        yrot=yr;
        zrot=zr;

        xvel=sin(xr)*cos(yr);
        yvel=sin(xr)*sin(yr);
<<<<<<< HEAD
        zvel=cos(xr);;
=======
        zvel=cos(xr);
>>>>>>> shit gettin mo and mo legit yo
	}

	Laser(double x, double y, double z, double xr, double yr, double zr){init(x,y,z,xr,yr,zr);}
	~Laser(){}

	void update() {
        xpos+=xvel;
        ypos-=yvel;
<<<<<<< HEAD
        zpos-=zvel;
=======
        zpos+=zvel;
>>>>>>> shit gettin mo and mo legit yo
	}

	void render() {
		glPushMatrix();
		glTranslatef(xpos, ypos, zpos);

		glScalef(0.3f,0.3f,0.3f);
		glRotatef(xrot,1.0,0,0);
		glRotatef(yrot,0.0,1.0,0);

        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
		glBegin(GL_QUADS); // of the pyramid

        glColor3f(1,0,0);
        glVertex3f(-.2,0,0);
        glVertex3f(.2,0,0);
        glVertex3f(.2,0,5);
        glVertex3f(-.2,0,5);

		glEnd();

		glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT0);

        glPopMatrix();
	}
protected:
private:
};
#endif // LASER_H

