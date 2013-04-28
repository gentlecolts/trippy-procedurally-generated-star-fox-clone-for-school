#include "gameObject.h"

#include "imports.h"

#include "camera.h"
#include "GLHelper.h"
#include "gameController.h"
#include "Model.h"
#include "Animation.h"
#include "math.h"
#include "enemyWave.h"

#include <iostream>

/**
 GameObject::GameObject(int n)
 Initialize
 */
GameObject::GameObject() {
	invinceStart=-1;
	didSetup=false;
	avgDist=-100;
	theAnimation=NULL;
	children=NULL;
	numChildren=0;
	parent=NULL;
	attachPointsFilled=NULL;
	
	pos=Vec3f(0,0,0);
	vel=Vec3f(0,0,0);
	rot=Vec3f(0,0,0);
}

/**
 void GameObject::render()
 Draw the model, calling theAnimation's transform methods, and uniqueRender() and uniqueRenderAfterPop()
 */
void GameObject::render() {
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);

	glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
	glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rot[2], 0.0f, 0.0f, 1.0f);

	uniqueRenderFirst();
	
	if(theAnimation==NULL)
		glBegin(model->type); // of the pyramid
	else
		theAnimation->doModelTransform();

    if(invinceStart>=0)
        glColor3f(1.0,0,0);

	for(int i=0;i<modelSize;i++) {
		if(i%model->verticesPerFace()==0 && theAnimation!=NULL) {
			glPushMatrix();
			theAnimation->doTriangleTransform(i);
			glBegin(model->type);
		} else if(i%3==0) {
			glNormal3f(model->normals[i/model->verticesPerFace()][0], model->normals[i/model->verticesPerFace()][1], model->normals[i/model->verticesPerFace()][2]);
		}
		
        if(invinceStart<0)
            glColor3f(model->colors[i][0],model->colors[i][1],model->colors[i][2]);
		glVertex3f(model->vertices[i][0],model->vertices[i][1],model->vertices[i][2]);
		
		if(i%3==2 && theAnimation!=NULL) {
			glEnd();
			glPopMatrix();
		}
	}
	
	if(theAnimation==NULL)
		glEnd();
	
	uniqueRender();

	uniqueRenderLast();
	
	for(int i=0;i<numChildren;i++) {
		children[i]->render();
	}

	glPopMatrix();

	uniqueRenderAfterPop();
}

/**
 void GameObject::doUpdate(double dt)
 Calls setup if necessary, tick the animation, end the invincibility timer if it ran out, call update
 */
void GameObject::doUpdate(double dt) {
    if(!didSetup)
        setup();
	
	if(theAnimation!=NULL)
		theAnimation->tick(dt);

    if(invinceStart>=0 && clock()-invinceStart>invinceLength) {
        invinceStart=-1;
    }

    update(dt);
	
	for(int i=0;i<numChildren;i++) {
		children[i]->doUpdate(dt);
	}
}

/**
 void GameObject::setup()
 Do setup that needs to be done after initialization: calculating the average vertex distance
 */
void GameObject::setup() {
    didSetup=true;
	
    avgDist=0;
    for(int i=0;i<modelSize;i++) {
		for(int j=0;j<3;j++) {
			avgDist+=abs(model->vertices[i][j]);
		}
    }
    avgDist/=model->verticesPerFace()*modelSize;
    avgDist*=objScale;
	
	if(model->numAttachPoints>0) {
		children=new GameObject*[model->numAttachPoints];
	}
	
	afterSetup();
}

/**
 bool GameObject::collidesWithNoise()
 Does hacky collision detection with the noise by checking at each vertex of the model
 */
bool GameObject::collidesWithNoise() {
    for(int i=0;i<modelSize;i++) {
        const double
            x=(model->vertices[i][0]*objScale+pos[0])/noiseScale *grid2+grid2,
            y=(model->vertices[i][1]*objScale+pos[1])/noiseScale *grid2+grid2,
            z=grid2-d*grid*((model->vertices[i][2]*objScale+pos[2])/noiseScale+d/2);
        if(noise[precompindx(x,y,z+zshft)]>tolerance){
            return true;
        }
    }
    return false;
}

void GameObject::addChild(GameObject *child) {
	children[numChildren]=child;
	
	child->pos=model->attachPoints[numChildren];
	/*child->xpos=model->attachPoints[numChildren][0];
	child->ypos=model->attachPoints[numChildren][1];
	child->zpos=model->attachPoints[numChildren][2];*/
	
	child->rot=model->attachPointAngles[numChildren];
	/*child->xrot=model->attachPointAngles[numChildren][0];
	child->yrot=model->attachPointAngles[numChildren][1];
	child->zrot=model->attachPointAngles[numChildren][2];*/
									
	numChildren++;
}

/**
 void GameObject::setAnimation(Animation *anim)
 Sets the current animation, deletes the old one if necessary
 */
void GameObject::setAnimation(Animation *anim) {
	if(theAnimation!=NULL) {
		delete theAnimation;
	}
	
	theAnimation=anim;
}

Vec3f GameObject::absoluteAngle() {
	if(parent!=NULL) {
		Vec3f parentAngle=parent->absoluteAngle();
		return Vec3f(parentAngle+rot);
	}
	return rot;
}

Vec3f GameObject::absolutePosition() {
	if(parent!=NULL) {
		Vec3f parentPos=parent->absolutePosition();
		Vec3f ang=parent->absoluteAngle();

		Vec3f dir=pos;
		dir=rotate(dir,Vec3f(1,0,0),rot[0]);
		dir=rotate(dir,Vec3f(1,0,0),rot[0]);
		dir=rotate(dir,Vec3f(1,0,0),rot[0]);
		
		return parentPos+dir*objScale;		//completely wrong
	}
	return pos;
}

void GameObject::destroy() {
	delete this;
}

/**
 bool GameObject::collidesWithObject(GameObject* obj)
 Does collision detection with another object using two spheres with radius of avgDist
 */
bool GameObject::collidesWithObject(GameObject* obj) {      //crappy method
    /*double xD=xpos-obj->xpos;
    double yD=ypos-obj->ypos;
    double zD=zpos-obj->zpos;*/
	Vec3f diff=pos-obj->pos;

    return diff.magnitude()<avgDist+obj->avgDist;
}

void GameObject::init(){}					//Do setup for subclasses
void GameObject::update(double dt){}		//Update for subclasses
void GameObject::uniqueRender(){}			//If a subclass wants to do its own drawing after rendering the model
void GameObject::uniqueRenderAfterPop(){}	//If a subclass wants to do its own drawing with no transforms applied
bool GameObject::isDone(){return false;}	//For checking when enemies are done
void GameObject::uniqueRenderLast(){}
void GameObject::uniqueRenderFirst(){}
void GameObject::afterSetup(){}


/**
 void GameObject::fireWeapon()
 Creates a laser at the position, direction
 */
void GameObject::fireWeapon() {
    addLaser(new Laser(pos[0],pos[1],pos[2],rot[0],rot[1],rot[2]));
	
	for(int i=0;i<numChildren;i++) {
		children[i]->fireWeapon();
	}
}

/**
 GameObject::~GameObject()
 Deletes theAnimation
 */
GameObject::~GameObject() {
	//cout<<"deleting something!"<<endl;
	delete theAnimation;
	delete[] children;
}
