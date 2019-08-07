#include "ColoredCube.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "Keyboard.h"
#include "CollisionBox.h"
#include "declarations.h"
#include "G.h"
#include "CubePiece.h"
using namespace std;

int ColoredCube::count = 0;


ColoredCube::ColoredCube(float x, float y, float r, float g, float b) : _Entity(x, y) {
    this->collisionBox = new CollisionBox(this, this->x, this->y, this->x + TILE_WIDTH, this->y + TILE_HEIGHT);
    this->isStatic = true;
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
    this->texture = G::getCubeTextureFromColor(color);
    ColoredCube::count++;
}



void ColoredCube::start(){
    _Entity::start();

}


void ColoredCube::step(){
    _Entity::step();

}

void ColoredCube::draw(){
    _Entity::draw();

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(this->x + TILE_WIDTH/2.0, this->y + TILE_HEIGHT/2.0, TILE_WIDTH/2.0);
    G::drawCube(TILE_WIDTH/2.0, this->texture);
    glPopMatrix();
    glEnable(GL_LIGHTING);

}

float* ColoredCube::getColor(){
    return this->color;
}

void ColoredCube::createPieces(){
    for(int i = 0; i < 2; i++){
	   for(int j = 0; j < 2; j++){
		  for(int k = 0; k < 2; k++){
			 _Room::currentRoom->addEntity(new CubePiece(this->x, this->y, i, j, k, this->color));
		  }
	   }
    }
}