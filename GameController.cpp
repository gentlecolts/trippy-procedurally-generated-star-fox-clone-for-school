#ifndef GAMEBAIJDONABDFONFANIBF_CPP
#define GAMEBAIJDONABDFONFANIBF_CPP

void setupGame() {
	//PlayerShip p;
    gameObjects[0]=new PlayerShip();

    for(int i=1;i<numGameObjects;i++) {
        gameObjects[i]=new EnemyShip();
    }

    /*
    cout<<gameObjects[0]->model[16].r<<endl;
    cout<<"WTFF?????"<<endl;
    //*/
}

void updateObjects() {
	for(int i=0;i<numGameObjects;i++) {
        gameObjects[i]->update();
    }
}

void renderObjects() {
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
    glScalef(0.3f,0.3f,0.3f);

    for(int i=0;i<numGameObjects;i++) {
        gameObjects[i]->render();
    }
}

#endif //GAMEBAIJDONABDFONFANIBF_CPP
