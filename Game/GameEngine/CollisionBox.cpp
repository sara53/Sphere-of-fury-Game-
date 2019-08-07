#include "CollisionBox.h"
#include "_Entity.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "CubePiece.h"
using namespace std;


CollisionBox::CollisionBox(_Entity* owner, float x1, float y1, float x2, float y2){
    this->owner = owner;
    this->x1 = x1;
    this->y1 = y1;
    this->w = x2 - x1;
    this->h = y2 - y1;
    this->xoffset = this->x1 - this->owner->getX();
    this->yoffset = this->y1 - this->owner->getY();
}

CollisionBox::~CollisionBox(){

}


void CollisionBox::update(float x, float y){
    this->x1 = x + this->xoffset;
    this->y1 = y + this->yoffset;
}

void CollisionBox::draw(){
    glColor3f(1, 0, 1);
    glBegin(GL_LINE_LOOP);
	   glVertex3f(this->x1, this->y1, 0);
	   glVertex3f(this->x1+this->w, this->y1, 0);
	   glVertex3f(this->x1+this->w, this->y1+this->h, 0);
	   glVertex3f(this->x1, this->y1+this->h, 0);
    glEnd();
}


bool CollisionBox::intersects(CollisionBox* other){
	return (other->x1 < this->x1 + this->w
		&& other->x1 + other->w > this->x1
		&& other->y1 < this->y1 + this->h
		&& other->y1 + other->h > this->y1);
}