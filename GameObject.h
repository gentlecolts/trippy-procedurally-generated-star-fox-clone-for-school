#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

struct vertex{
	float x,y,z;
	float r,g,b;

	vertex(float x2=0,float y2=0,float z2=0,float r2=0,float g2=0,float b2=0){
		x=x2;
		y=y2;
		z=z2;
		r=r2;
		g=g2;
		b=b2;
	}
};

class GameObject
{
public:
    vertex *model;
    float xpos,ypos,xvel,yvel;

    virtual void init(){}
	GameObject(){
		//model=&playerModel;
		//modelSize=0;
		//cout<<"penis"<<endl;
		init();
	}

	void render(){
		//cout<<modelSize<<endl;
		//glLoadIdentity();
		//glTranslatef(xpos, ypos, 0);

		//glRotatef(-90, 1.0f, 0.0f, 0.0f);
		//glRotatef(xvel/maxV*90, 0.0f, 1.0f, 0.0f);

		glBegin(GL_TRIANGLES); // of the pyramid

		for(int i=0;i<modelSize;i++) {
			glColor3f(model[i].r,model[i].g,model[i].b);
			glVertex3f(model[i].x,model[i].y,model[i].z);
		}

		glEnd();
	}

	virtual void update() {

	}
protected:
private:
	int modelSize;
};

#endif // GAMEOBJECT_H_INCLUDED
