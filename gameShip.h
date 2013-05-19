//
//  gameShip.h
//  HelloSDL
//
//  Created by Jonah Chazan on 4/25/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__gameShip__
#define __HelloSDL__gameShip__

#include <iostream>

#include "GameObject.h"

class GameShip : public GameObject {
private:
	GameShip *next;
protected:
public:
	GameShip *previous;
	EnemyWave* parentWave;
	bool scheduledToDelete;
	
	GameShip* destroyAndGetNext();
	GameShip* getNext();
	GameShip* head();
	void setNext(GameShip *n);
	void deleteAndDeleteChildren();
	void appendObject(GameShip *obj);
	void destroy();
	void uniqueRenderFirst();
	void uniqueRenderLast();
	
	virtual ~GameShip();
	GameShip();
};

#endif /* defined(__HelloSDL__gameShip__) */
