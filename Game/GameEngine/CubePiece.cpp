#include "CubePiece.h"
#include "_Entity.h"
#include "declarations.h"
#include "_Room.h"
#include "G.h"
#include "CollisionBox.h"
#include <iostream>
using namespace std;

CubePiece::CubePiece(float baseX, float baseY, int right, int front, int top, float color[3]) : _Entity(baseX, baseY) {
    this->x += right * 0.5 * TILE_WIDTH;
    this->y += front * 0.5 * TILE_HEIGHT;
    this->z = top * 0.5 * TILE_HEIGHT;
    this->gravity = 0.1;
    this->hspeed = right ? 1 : -1;
    this->vspeed = front ? 1 : -1;
    this->zspeed = top ? 1.5 : 0.7;
    for(int i = 0; i < 3; i++){
	   this->color[i] = color[i];
    }
}

void CubePiece::start(){
    _Entity::start();

}

void CubePiece::step(){
    _Entity::step();

    this->x += this->hspeed;
    this->y += this->vspeed;
    this->z += this->zspeed;
    this->zspeed -= this->gravity;
    if(this->z < -0.5 * TILE_HEIGHT){
	   _Room::currentRoom->removeEntity(this);
    }
}

void CubePiece::draw(){
    _Entity::draw();

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(this->x + TILE_WIDTH/4.0, this->y + TILE_HEIGHT/4.0, this->z + TILE_HEIGHT/4.0);
    glColor3fv(this->color);
    glutSolidCube(TILE_WIDTH/4.0);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}