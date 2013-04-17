#include "playerShip.h"

#include "math.h"
#include "imports.h"
#include "Model.h"
#include "vec3f.h"


PlayerShip::PlayerShip(int n) : GameObject(n) {
	init();
}

void PlayerShip::init(){
    modelSize=18;

    /*model=new vertex[modelSize];
    model[0]=vertex(0.0f, 0.0f, -2.0f, 1.0f, 0.f, 0.0f);
    model[1]=vertex(0.0f, 0.5f, -0.0f, 0.0f, 1.0f, 0.0f);
    model[2]=vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[3]=vertex(0.0f, 0.0f, -2.0f, 1.0f, 0.f, 0.0f);
    model[4]=vertex(0.0f, -0.5f, -0.0f, 0.0f, 1.0f, 0.0f);
    model[5]=vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[6]=vertex(0.0f, 0.0f, -2.0f, 1.0f, 0.f, 0.0f);
    model[7]=vertex(0.0f, 0.5f, -0.0f, 0.0f, 1.0f, 0.0f);
    model[8]=vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[9]=vertex(0.0f, 0.0f, -2.0f, 1.0f, 0.f, 0.0f);
    model[10]=vertex(0.0f, -0.5f, -0.0f, 0.0f, 1.0f, 0.0f);
    model[11]=vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[12]=vertex(0.0f, 0.5f, -0.0f, 0.0f, 1.0f, 0.0f);//lost track here
    model[13]=vertex(0.0f, -0.5f, -0.0f, 0.0f, 1.0f, 0.0f);
    model[14]=vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    model[15]=vertex(0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[16]=vertex(0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
    model[17]=vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);*/
	
	model=new Model(modelSize);
	
	model->addVertex(Vec3f(0.0f, 0.0f, -2.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, 0.5f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(1.0f, 0.0f, 1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, -2.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, -0.5f, -0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(1.0f, 0.0f, 1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, -2.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, 0.5f, -0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(-1.0f, 0.0f, 1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(0.0f, 0.0f, -2.0f));
	model->addColor(Vec3f(1.0f, 0.f, 0.0f));
	model->addVertex(Vec3f(0.0f, -0.5f, -0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(-1.0f, 0.0f, 1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(0.0f, 0.5f, -0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(0.0f, -0.5f, -0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(-1.0f, 0.0f, 1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	model->addVertex(Vec3f(0.0f, 0.5f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(0.0f, -0.5f, 0.0f));
	model->addColor(Vec3f(0.0f, 1.0f, 0.0f));
	model->addVertex(Vec3f(1.0f, 0.0f, 1.0f));
	model->addColor(Vec3f(0.0f, 0.0f, 1.0f));
	
	model->computeNormals();

    zpos=-playerOffset;
}

void PlayerShip::uniqueRenderAfterPop() {
    glPushMatrix();

	double vect[3];
	getVector(xrot,yrot,vect);

    /*double x=-sin(radians(yrot));
    double y=sin(radians(xrot))*cos(radians(yrot));
	double z=-cos(radians(xrot))*cos(radians(yrot*/

	double x=vect[0];
    double y=vect[1];
	double z=vect[2];

    double dist=2;

    glTranslatef(x*dist+xpos,y*dist+ypos,z*dist+zpos);

    glLineWidth(3);

    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);


    double halfLength=objScale;

    glVertex3f(halfLength,halfLength,0);
    glVertex3f(-halfLength,halfLength,0);
    glVertex3f(-halfLength,halfLength,0);
    glVertex3f(-halfLength,-halfLength,0);
    glVertex3f(-halfLength,-halfLength,0);
    glVertex3f(halfLength,-halfLength,0);
    glVertex3f(halfLength,-halfLength,0);
    glVertex3f(halfLength,halfLength,0);

    glEnd();

    glTranslatef(x*dist,y*dist,z*dist);

    glBegin(GL_LINES);

    glVertex3f(halfLength,halfLength,0);
    glVertex3f(-halfLength,halfLength,0);
    glVertex3f(-halfLength,halfLength,0);
    glVertex3f(-halfLength,-halfLength,0);
    glVertex3f(-halfLength,-halfLength,0);
    glVertex3f(halfLength,-halfLength,0);
    glVertex3f(halfLength,-halfLength,0);
    glVertex3f(halfLength,halfLength,0);

    glEnd();
    glPopMatrix();
}

void PlayerShip::update(double dt) {
	handleKeyInput(dt);
	
	double vec[3];
	
	getVector(xrot, yrot, vec);
	
	xvel=vec[0]*maxV;
	yvel=vec[1]*maxV;
	zvel=vec[2]*maxV;
	
	xpos+=xvel*dt;
    ypos+=yvel*dt;
	
	xpos=max(min((double)xpos,1.0*noiseScale),-1.0*noiseScale);
	ypos=max(min((double)ypos,1.0*noiseScale),-1.0*noiseScale);

    /*zrot=-xvel/maxV*18;//90*2/5;
    yrot=-xvel/maxV*36;
    xrot=yvel/maxV*36;*/


    if(invinceStart<0) {
        bool hit=false;

        for(int i=0;i<gameObjects.size();i++) {
            if(this!=gameObjects.at(i) && collidesWithObject(gameObjects.at(i))) {
                hit=true;
                break;
            }
        }
        if(hit || collidesWithNoise()) {
            invinceStart=clock();
            //xvel=0;
            //xvel=0;
        }
    }
}

void PlayerShip::handleKeyInput(double dt) {
	if(leftmov){
		yrot+=accel*dt;
	} else if(rightmov){
		yrot-=accel*dt;
	} else {
		if(abs(yrot)-accel*dt>0)
			yrot-=accel*dt*signum(yrot);
		else
			yrot=0;
	}
	if(upmov){
		xrot+=accel*dt;
	} else if(downmov){
		xrot-=accel*dt;
	} else {
		if(abs(xrot)-accel*dt>0)
			xrot-=accel*dt*signum(xrot);
		else
			xrot=0;
	}

	yrot=max(min((double)yrot, angleCap),-angleCap);
	xrot=max(min((double)xrot, angleCap),-angleCap);
}


/*if(leftmov){
 if(upmov!=downmov){//aka xor operator, deal w/ it
 xvel-=accel*rt2*dt;
 }else{
 xvel-=accel*dt;
 }
 } else if(rightmov){
 if(upmov!=downmov){
 xvel+=accel*rt2*dt;
 }else{
 xvel+=accel*dt;
 }
 } else {
 if(abs(xvel)-accel*dt>0)
 xvel-=accel*dt*signum(xvel);
 else
 xvel=0;
 }
 if(upmov){
 if(leftmov!=rightmov){
 yvel+=accel*rt2*dt;
 }else{
 yvel+=accel*dt;
 }
 } else if(downmov){
 if(leftmov!=rightmov){
 yvel-=accel*rt2*dt;
 }else{
 yvel-=accel*dt;
 }
 } else {
 if(abs(yvel)-accel*dt>0)
 yvel-=accel*dt*signum(yvel);
 else
 yvel=0;
 }

 /*/
