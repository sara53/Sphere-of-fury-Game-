#include "ColorChanger.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "Keyboard.h"
#include "CollisionBox.h"
#include "declarations.h"
#include "G.h"
using namespace std;

ColorChanger::ColorChanger(float x, float y, float r, float g, float b) : _Entity(x, y) {
    this->collisionBox = new CollisionBox(this, this->x, this->y, this->x + TILE_WIDTH, this->y + TILE_HEIGHT);
    this->isStatic = true;
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
    this->texture = G::getChangerTextureFromColor(color);
}


void ColorChanger::start(){
    _Entity::start();

}


void ColorChanger::step(){
    _Entity::step();

}

void ColorChanger::draw(){
    _Entity::draw();

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(this->x + TILE_WIDTH/2.0, this->y + TILE_HEIGHT/2.0, TILE_WIDTH/2.0);
    G::drawCube(TILE_WIDTH/2.0, this->texture);
    glPopMatrix();
    glEnable(GL_LIGHTING);

}

float* ColorChanger::getColor(){
    return this->color;
}