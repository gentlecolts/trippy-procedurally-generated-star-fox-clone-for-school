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

GLfloat light1[4];

class GameObject
{
public:
    vertex *model;
    float xpos,ypos,xvel,yvel;

    virtual void init(){}
	GameObject(){
		//model=&playerModel;
		//modelSize=0;
		init();

		light1[0]=0;
		light1[1]=0;
		light1[2]=-1.5;
		light1[3]=1;

		glLightfv(GL_LIGHT1, GL_POSITION, light1);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.125);
	}

	void render(){
		//cout<<modelSize<<endl;
		//glLoadIdentity();
		glTranslatef(xpos, ypos, 3);

		glScalef(0.3f,0.3f,0.3f);
		//glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glRotatef(-xvel/maxV*90*2/5, 0.0f, 0.0f, 1.0f);
		glRotatef(-yvel/maxV*90*2/5, 1.0f, 0.0f, 0.0f);
		/*
        cout<<"model:"<<endl;
        cout<<model<<endl;
        cout<<"model size:"<<endl;
        cout<<modelSize<<endl;
        cout<<"this:"<<endl;
        cout<<this<<endl;
        //*/

        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
		glBegin(GL_TRIANGLES); // of the pyramid

		for(int i=0;i<modelSize;i++) {
			glColor3f(model[i].r,model[i].g,model[i].b);
			glVertex3f(model[i].x,model[i].y,model[i].z);
		}

		glEnd();

		glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT0);
	}
	~GameObject(){delete[] model;}

	virtual void update() {

	}
protected:
	int modelSize;
private:
};

#endif // GAMEOBJECT_H_INCLUDED
