//
//  ObjectFactoryRegister.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/6/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "ObjectFactoryRegister.h"
#include "RegisterEnemies.h"
#include "RegisterStruts.h"
#include "RegisterWeapons.h"

/*
 TODO:
 
 Hovership √
 Ramship √
 (trackingShip)
 
 AimingStrut √
 BasicStrut √
 (ShotgunStrut)
 RotateStrut √
 
 BasicGun
 (beamGun)
 (grenadeLauncher)
 (rocketLauncher)
 */


void registerAll() {
	objects=new vector<ObjectType *>;
	enemies=new vector<ObjectType *>;
	attachments=new vector<ObjectType *>;
	weapons=new vector<ObjectType *>;
	bombs=new vector<ObjectType *>;
	
	registerHoverShipType();
	registerRamShipType();
	registerTrackingShipType();
	
	registerBasicGunType();
	
	registerBasicStrutType();
	registerRotateStrutType();
	registerAimingStrutType();
}

