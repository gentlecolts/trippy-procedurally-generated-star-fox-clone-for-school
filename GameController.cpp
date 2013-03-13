

void setupGame() {
    gameObjects[0]=PlayerShip();
}

void updateObjects() {
}

void renderObjects() {
    glTranslatef(0,0,-1);
    glScalef(0.3f,0.3f,0.3f);

}
