#include "Enemy.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "Keyboard.h"
#include "CollisionBox.h"
#include "G.h"
#include "declarations.h"
#include "Camera.h"
#include "__Game.h"
#include <cmath>
#include "Wall.h"
#include "ColoredCube.h"
#include "ColorChanger.h"
#include "_Room.h"
#include "Skull.h"
using namespace std;

Enemy::Enemy(float x, float y) : _Entity(x, y) {
    this->collisionBox = new CollisionBox(this, this->x, this->y, 
	   this->x+TILE_WIDTH, this->y+TILE_WIDTH);
    this->hspeed = 0;
    this->vspeed = 0;
    this->angle = 0;
    
}


void Enemy::start(){
    _Entity::start();

}


void Enemy::step(){
    _Entity::step();
    
    // rotate blades
    this->angle += 6;
    if(this->angle > 360){
	   this->angle -= 360;
    }

    ////////////// Bounce against border walls ///////////////
    this->bounceAgainstBorders();

    _Entity* wall;
    _Entity* cube;
    _Entity* changer;
    _Entity* skull;
    if(abs(this->hspeed) > 0){
	   ////////////// Bounce against walls ///////////////
	   wall = this->checkStaticCollisionWith<Wall>(this->x + this->hspeed, this->y);
	   if(  wall != nullptr ){
		  this->hspeed *= -1;
	   }
	   ////////////// Bounce against skulls ///////////////
	   skull = this->checkStaticCollisionWith<Skull>(this->x + this->hspeed, this->y);
	   if(  skull != nullptr ){
		  this->hspeed *= -1;
	   }
	   ////////////// Bounce against color changer ///////////////
	   changer = this->checkStaticCollisionWith<ColorChanger>(this->x + this->hspeed, this->y);
	   if(  changer != nullptr ){
		  this->hspeed *= -1;
	   }
	   ////////////// Bounce against colored cube ///////////////
	   cube = this->checkStaticCollisionWith<ColoredCube>(this->x + this->hspeed, this->y);
	   if(  cube != nullptr ){
		  this->hspeed *= -1;
	   }
    }
    if(abs(this->vspeed) > 0){
	   ////////////// Bounce against walls ///////////////
	   wall = this->checkStaticCollisionWith<Wall>(this->x, this->y + this->vspeed);
	   if(  wall != nullptr ){
		  this->vspeed *= -1;
	   }
	   ////////////// Bounce against skulls ///////////////
	   skull = this->checkStaticCollisionWith<Skull>(this->x, this->y + this->vspeed);
	   if(  skull != nullptr ){
		  this->vspeed *= -1;
	   }
	   ////////////// Bounce color changer ///////////////
	   changer = this->checkStaticCollisionWith<ColorChanger>(this->x, this->y + this->vspeed);
	   if(  changer != nullptr ){
		  this->vspeed *= -1;
	   }
	   ////////////// Bounce against colored cube ///////////////
	   cube = this->checkStaticCollisionWith<ColoredCube>(this->x, this->y + this->vspeed);
	   if(  cube != nullptr ){
		  this->vspeed *= -1;
	   }
    }
    

    ////////////// Update position ///////////////
    this->x += this->hspeed;
    this->y += this->vspeed;
    
}

void Enemy::draw(){
    _Entity::draw();
    
    ////////////// Draw Enemy body ///////////////
    glPushMatrix();
    glTranslatef(this->x + TILE_WIDTH/2.0, this->y + TILE_HEIGHT/2.0, TILE_WIDTH/2.0);
    glRotatef(this->angle, 0, 0, 1);
    glScalef(1, 1, 0.5f/0.15f);
    G::drawCube(0.15*TILE_HEIGHT, G::TEX_ENEMY);
    glPopMatrix();

    ////////////// Draw Enemy blades ///////////////
    for(int i = 0; i < 4; i++){
	   glPushMatrix();
	   glTranslatef(this->x + TILE_WIDTH/2.0, this->y + TILE_HEIGHT/2.0, 0);
	   glRotatef(this->angle + 90*i, 0, 0, 1);
	   glEnable(GL_TEXTURE_2D);
	   glBindTexture(GL_TEXTURE_2D, G::TEX_ENEMY_BLADE);
	   glColor3f(1, 1, 1);
	   glBegin(GL_TRIANGLES);
		  glTexCoord2f(0.0f, 0.0f);
		  glVertex3f(-0.15*TILE_WIDTH, 0.15*TILE_HEIGHT, 0.5*TILE_HEIGHT);
		  glTexCoord2f(1.0f, 0.0f);
		  glVertex3f(+0.15*TILE_WIDTH, 0.15*TILE_HEIGHT, 0.5*TILE_HEIGHT);
		  glTexCoord2f(0.5f, 1.0f);
		  glVertex3f(0, 0.6*TILE_HEIGHT, 0.5*TILE_HEIGHT);
	   glEnd();
	   glDisable(GL_TEXTURE_2D);
	   glPopMatrix();
    }
}