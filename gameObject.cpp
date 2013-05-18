
#include "gameObject.h"

#include "imports.h"

#include "camera.h"
#include "globals.h"
#include "GLHelper.h"
#include "gameController.h"
#include "Model.h"
#include "Animation.h"
#include "math.h"
#include "enemyWave.h"
#include "Matrix.h"

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
	player=false;
	modelSize=0;
	t=0;
	health=0;
	bigGun=false;
	score=50;
	
	pos=Vec3d(0,0,0);
	vel=Vec3d(0,0,0);
	rot=Vec3d(0,0,0);
}

/**
 void GameObject::render()
 Draw the model, calling theAnimation's transform methods, and uniqueRender() and uniqueRenderAfterPop()
 */
void GameObject::render() {
	//glDisable(GL_LIGHT0);
	
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	
	glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
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
		} else if(i%model->verticesPerFace()==0) {
			glNormal3f(model->normals[i/model->verticesPerFace()][0], model->normals[i/model->verticesPerFace()][1], model->normals[i/model->verticesPerFace()][2]);
		}
		
        if(invinceStart<0)
            glColor4f(model->colors[i][0],model->colors[i][1],model->colors[i][2],model->colors[i][3]);
		glVertex3f(model->vertices[i][0],model->vertices[i][1],model->vertices[i][2]);
		
		if(i%model->verticesPerFace()==model->verticesPerFace()-1 && theAnimation!=NULL) {
			glEnd();
			glPopMatrix();
		}
	}
	
	if(theAnimation==NULL)
		glEnd();
	
	uniqueRender();

	uniqueRenderLast();
	
	for(int i=0;i<model->numAttachPoints;i++) {
		if(attachPointsFilled[i])
			children[i]->render();
	}

	glPopMatrix();

	uniqueRenderAfterPop();
	
	//glEnable(GL_LIGHT0);
}

/**
 void GameObject::doUpdate(double dt)
 Calls setup if necessary, tick the animation, end the invincibility timer if it ran out, call update
 */
void GameObject::doUpdate(double dt) {
    if(!didSetup)
        setup();
	
    t+=dt;
	
	if(theAnimation!=NULL)
		theAnimation->tick(dt);

    if(invinceStart>=0 && clock()-invinceStart>invinceLength) {
        invinceStart=-1;
    }

    update(dt);
	
	//cout<<"start"<<endl;
	for(int i=0;i<model->numAttachPoints;i++) {
		//cout<<"i "<<i<<" filled "<<attachPointsFilled[i]<<endl;
		if(attachPointsFilled[i])
			children[i]->doUpdate(dt);
	}
	//cout<<"end"<<endl;
}

void GameObject::addUpHealth(int h) {
	if(parent!=NULL) {
		parent->addUpHealth(h);
	}
	
	health+=h;
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
//		cout<<"DFDSD "<<model->numAttachPoints<<endl;
		children=new GameObject*[model->numAttachPoints];
		
		attachPointsFilled=new bool[model->numAttachPoints];
		
		for(int i=0;i<model->numAttachPoints;i++) {
			attachPointsFilled[i]=false;
		}
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
            x=(model->vertices[i][0]*objScale+pos[0])/frameSize *grid2+grid2,
            y=(model->vertices[i][1]*objScale+pos[1])/frameSize *grid2+grid2,
            z=grid2-d*grid*((model->vertices[i][2]*objScale+pos[2])/frameSize+d/2);
        if(noise[precompindx(x,y,z+zshft)]>tolerance){
            return true;
        }
    }
    return false;
}

void GameObject::addChild(GameObject *child, int index) {
	addChild(child, index, Vec3d(0,0,0));
}

void GameObject::setPlayer(bool p) {
	player=p;
	
	if(didSetup) {
		for(int i=0;i<model->numAttachPoints;i++) {
			if(attachPointsFilled[i]) {
				children[i]->setPlayer(p);
			}
		}
	}
}

void GameObject::addChild(GameObject *child, int index, Vec3d angle) {
	if(!didSetup) {
		setup();
	}
	
	if(index==-1)
		index=numChildren;
	
//	cout<<"adding something to "<<this<<" at "<<index<<endl;
	
	numChildren++;
	
	children[index]=child;
	
	child->pos=model->attachPoints[index];
	
	child->rot=model->attachPointAngles[index]+angle;
	
	attachPointsFilled[index]=true;
	
	child->setPlayer(player);
	
	child->parent=this;
	
	addUpHealth(child->health);
}

int GameObject::getDamage(GameObject *other) {
	return 10;
}

/**
 void GameObject::setAnimation(Animation *anim)
 Sets the current animation, deletes the old one if necessary
 */
void GameObject::setAnimation(Animation *anim) {
	if(theAnimation!=NULL) {
//		cout<<"animation belongs to: "<<this<<endl;
		delete theAnimation;
	}
	
	theAnimation=anim;
}

Matrix GameObject::getMatrix() {
//	cout<<"CALL"<<endl;
	Matrix mat;
	if(parent!=NULL) {
		mat=parent->getMatrix();
//		cout<<"got parent matrix"<<endl;
	}
//	cout<<"parent matrix: "<<mat<<endl;
	
	mat=mat*Matrix(
				   Vec4d(1, 0, 0, pos[0]),				//translation
				   Vec4d(0, 1, 0, pos[1]),
				   Vec4d(0, 0, 1, pos[2]),
				   Vec4d(0, 0, 0, 1)
				   );
	
//	cout<<"matrix: "<<mat<<endl;
//	cout<<"my pos: "<<pos<<endl;
	
	mat=mat*Matrix(rot);
	
	if(parent==NULL) {
		mat=mat*Matrix(
					   Vec4d(objScale, 0, 0, 0),
					   Vec4d(0, objScale, 0, 0),
					   Vec4d(0, 0, objScale, 0),
					   Vec4d(0, 0, 0, 1)
		);
	}
	
//	cout<<"rot: "<<rot<<endl;
//	cout<<"rot matrix: "<<Matrix(rot)<<endl;
	
	return mat;
}

Vec3d GameObject::absoluteAngle() {
	//cout<<"MATRIX: "<<getMatrix()<<endl;
	Matrix mat=getMatrix();
	Vec3d diff=mat*Vec4d(0, 0, 1, 1)-mat*Vec4d(0, 0, 0, 1);
	
//	cout<<"diff: "<<diff<<endl;
	
	return invGetVector(diff);
}

Vec3d GameObject::absolutePosition() {
	if(parent!=NULL) {
		/*
		Vec3d parentPos=parent->absolutePosition();
		Vec3d ang=parent->absoluteAngle();

		Vec3d dir=pos;
		dir=rotate(dir,Vec3d(1,0,0),ang[0]);
		dir=rotate(dir,Vec3d(0,1,0),ang[1]);
		dir=rotate(dir,Vec3d(0,0,1),ang[2]);
		
		return parentPos+dir*objScale;		//completely wrong
		 */
		
		Matrix parentMat=parent->getMatrix();
		return parentMat*pos;
	}
	//cout<<"pos: "<<pos<<endl;
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
	//cout<<"obj: "<<obj<<endl;
	Vec3d diff=pos-obj->pos;

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
void GameObject::doFire() {}


/**
 void GameObject::fireWeapon()
 Creates a laser at the position, direction
 */
void GameObject::fireWeapon() {
	if(didSetup) {
		if(!bigGun)
			doFire();
		
		for(int i=0;i<model->numAttachPoints;i++) {
			if(attachPointsFilled[i])
				children[i]->fireWeapon();
		}
	}
}

void GameObject::fireBigGuns() {
	if(didSetup) {
		if(bigGun)
			doFire();
		
		for(int i=0;i<model->numAttachPoints;i++) {
			if(attachPointsFilled[i])
				children[i]->fireBigGuns();
		}
	}
}


/**
 GameObject::~GameObject()
 Deletes theAnimation
 */
GameObject::~GameObject() {
//	cout<<"deleting something! @"<<this<<endl;
	delete theAnimation;
	delete[] children;
}
