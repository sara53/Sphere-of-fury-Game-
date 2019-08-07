#include "Wall.h"
#include "Obstacles.h"
#include "CollisionBox.h"
#include "declarations.h"
#include <Windows.h>
#include <gl\glut.h>
#include "G.h"

Wall::Wall(float x, float y): Obstacles(x, y){
    this->collisionBox = new CollisionBox(this, this->x, this->y, this->x + TILE_WIDTH, this->y + TILE_HEIGHT);
}


void Wall::start(){
    _Entity::start();

}


void Wall::step(){
    _Entity::step();

}

void Wall::draw(){
    _Entity::draw();

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(this->x + TILE_WIDTH/2.0, this->y + TILE_HEIGHT/2.0, TILE_WIDTH/2.0);
    G::drawCube(TILE_WIDTH/2.0, G::TEX_WALL3);
    glPopMatrix();
    glEnable(GL_LIGHTING);

}

