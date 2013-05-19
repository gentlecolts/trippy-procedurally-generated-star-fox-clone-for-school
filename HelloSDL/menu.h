//
//  menu.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/14/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__menu__
#define __HelloSDL__menu__

#include <iostream>
#include "../guilib/guilib.h"

class button;

void launchMenu();
void play(button* b);

extern button *playButton, *creditsButton, *settingsButton, *quitButton;

//void launchPause();
//void renderPause();

#endif /* defined(__HelloSDL__menu__) */
