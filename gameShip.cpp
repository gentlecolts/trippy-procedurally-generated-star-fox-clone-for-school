//
//  gameShip.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 4/25/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "gameShip.h"
#include "enemyWave.h"

/**
 GameShip::GameShip()
 Initializes the GameShip
 */
GameShip::GameShip() : GameObject() {
	next=NULL;
	parentWave=NULL;
	scheduledToDelete=false;
	previous=NULL;
}

char* GameShip::getType(){return "GameShip";}

/**
 void GameShip::uniqueRenderFirst()
 If it is the top node, scales itself by objScale, and disables the light for the terrain
 */
void GameShip::uniqueRenderFirst() {
	if(parent==NULL)
		glScalef(objScale,objScale,objScale);

	glDisable(GL_LIGHT0);
}

/**
 void GameShip::uniqueRenderLast()
 Reenables the light that was disabled; there is no need to undo the scaling as the OpenGL matrix stack has been popped
 */
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

/**
 void GameShip::destroy()
 Sets the ship to be destroyed the next time it is updated
 */
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

/**
 GameShip* GameShip::head()
 Returns the first node in the linked list
 */
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

/**
 GameShip::~GameShip()
 Notifies the parent wave that it has been destroyed
 */
GameShip::~GameShip() {
	if(parentWave!=NULL) {
		parentWave->remove(this);
		parentWave->release();
	}

}
