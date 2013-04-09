#ifndef LASER_H_INCLUDED
#define LASER_H_INCLUDED

class GameObject;

class Laser
{
public:
    double xpos,ypos,zpos,xvel,yvel,zvel,xrot,yrot,zrot;

	Laser(double x, double y, double z, double xr, double yr, double zr);
	~Laser();

	void init(double x, double y, double z, double xr, double yr, double zr);
	void update();
	void render();
    bool collidesWithObject(GameObject* obj);
    bool collidesWithNoise();
protected:
private:
};

#endif // LASER_H_INCLUDED
