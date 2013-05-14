//
//  gameShip.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/25/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "gameShip.h"
#include "enemyWave.h"

GameShip::GameShip(int n) : GameObject() {
	next=NULL;
	parentWave=NULL;
	scheduledToDelete=false;
	previous=NULL;
	
	index=n;
}

void GameShip::uniqueRenderFirst() {
	if(parent==NULL)
		glScalef(objScale,objScale,objScale);
	
	glDisable(GL_LIGHT0);
}

void GameShip::uniqueRenderLast() {
	glEnable(GL_LIGHT0);
}

/**
 GameShip* GameShip::getNext()
 Returns next
 */
GameShip* GameShip::getNext() {
	return next;
}

/**
 GameShip* GameShip::setNext()
 Sets next, sets that next's previous to this
 */
void GameShip::setNext(GameShip *n) {
	next=n;
	if(n!=NULL)
		n->previous=this;
}

/**
 void GameShip::appendObject(GameShip *obj)
 Adds an object to end of the linked list
 */
void GameShip::appendObject(GameShip *obj) {
	if(next!=NULL) {
		next->appendObject(obj);
	} else {
		next=obj;
		obj->previous=this;
	}
}

void GameShip::destroy() {
	scheduledToDelete=true;
}

/**
 void GameShip::deleteAndDeleteChildren()
 Deletes it and all of its children
 */
void GameShip::deleteAndDeleteChildren() {
	if(next!=NULL)
		next->deleteAndDeleteChildren();
	
	delete this;
}

GameShip* GameShip::head() {
	if(previous!=NULL)
		return previous->head();
	else
		return this;
}

/**
 GameShip* GameShip::destroyAndGetNext()
 Sets its previous's next to next and returns that, then deletes this
 */
GameShip* GameShip::destroyAndGetNext() {
	if(previous!=NULL)
		previous->setNext(next);
	else {
		if(next!=NULL)
			next->previous=NULL;
	}
	
	delete this;
	
	return next;
}

GameShip::~GameShip() {
	if(parent!=0)
		cout<<"parent: "<<parentWave<<endl;
	
	if(parentWave!=NULL) {
		parentWave->remove(this);
		parentWave->release();
	}
	
}
