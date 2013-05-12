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
	registerHoverShipType();
	registerRamShipType();
	
	registerBasicStrutType();
	registerRotateStrutType();
	registerAimingStrutType();
}

