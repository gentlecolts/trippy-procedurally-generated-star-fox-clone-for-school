#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

typedef float FloatArray[6];

class GameObject
{
public:
    FloatArray *model;
    float xpos,ypos,xvel,yvel;
	GameObject(){
		//model=&playerModel;
		modelSize=0;
	}

	void render(){
		//glLoadIdentity();
		glTranslatef(xpos, ypos, 0);

		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glRotatef(xvel/maxV*90, 0.0f, 1.0f, 0.0f);

		glBegin(GL_TRIANGLES); // of the pyramid

		for(int i=0;i<modelSize;i++) {
			glColor3f(model[i][3],model[i][4],model[i][5]);
			glVertex3f(model[i][0],model[i][1],model[i][2]);
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
