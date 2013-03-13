#ifndef GAMEBAIJDONABDFONFANIBF_CPP
#define GAMEBAIJDONABDFONFANIBF_CPP

void setupGame() {
	PlayerShip p;
    gameObjects[0]=&p;
}

void updateObjects() {
}

void renderObjects() {
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
    glTranslatef(0,0,-2);
    glScalef(0.3f,0.3f,0.3f);

    for(int i=0;i<numGameObjects;i++) {
        gameObjects[i]->render();
    }
}

#endif //GAMEBAIJDONABDFONFANIBF_CPP
