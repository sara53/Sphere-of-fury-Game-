#include "Skull.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "Keyboard.h"
#include "CollisionBox.h"
#include "declarations.h"
#include "G.h"
using namespace std;


Skull::Skull(float x, float y, float r, float g, float b) : _Entity(x, y) {
    this->collisionBox = new CollisionBox(this, this->x, this->y, this->x + TILE_WIDTH, this->y + TILE_HEIGHT);
    this->isStatic = true;
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
    this->texture = G::getSkullTextureFromColor(color);
}



void Skull::start(){
    _Entity::start();

}


void Skull::step(){
    _Entity::step();

}

void Skull::draw(){
    _Entity::draw();

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(this->x + TILE_WIDTH/2.0, this->y + TILE_HEIGHT/2.0, TILE_WIDTH/2.0);
    G::drawCube(TILE_WIDTH/2.0, this->texture);
    glPopMatrix();
    glEnable(GL_LIGHTING);

}

float* Skull::getColor(){
    return this->color;
}
