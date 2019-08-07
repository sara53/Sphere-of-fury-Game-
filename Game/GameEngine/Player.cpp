#include "Player.h"
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
#include "Enemy.h"
using namespace std;

Player::Player(float x, float y) : _Entity(x, y) {
    this->collisionBox = new CollisionBox(this, this->x + 0.15 * TILE_WIDTH, this->y + 0.15 * TILE_HEIGHT, 
	   this->x + 0.85 * TILE_WIDTH, this->y + 0.85 * TILE_HEIGHT);
    this->hspeed = 0;
    this->vspeed = 1;
    this->vspeedBase = this->vspeed;
    this->direction = 0;
    this->rotation = 0;
    this->speed = 0;
    this->color[0] = 0;
    this->color[1] = 0;
    this->color[2] = 1;
    this->horMovementDelay = 0;
    this->speedScale = 1.0f;
    __Game::player = this;
}


void Player::start(){
    _Entity::start();

}


void Player::step(){
    _Entity::step();

    ////////////// Move ///////////////
    if(horMovementDelay == 0){
	   if(Keyboard::left){
		  this->hspeed -= 0.3;
		  if(this->hspeed < -2){
			 this->hspeed = -2;
		  }
	   } else if(Keyboard::right){
		  this->hspeed += 0.3;
		  if(this->hspeed > +2){
			 this->hspeed = +2;
		  }
	   }
    }

    ///////////////// vspeed control ///////////////////
    this->speedScale = 1.0f;
    if(Keyboard::space){
	   this->speedScale = 2.0f;
    }
    float sgn = 1.0f;
    if(this->vspeed < 0){
	   sgn = -1.0f;
    }
    this->vspeed = sgn * this->vspeedBase * this->speedScale;


    /////////// Horizontal movement delay ///////////
    if(horMovementDelay > 0){
	   horMovementDelay --;
    }


    ////////////// Friction ///////////////
    this->hspeed *= 0.90;
    if(abs(this->hspeed) < 0.01){
	   this->hspeed = 0;
    }
  

    ////////////// Direction, Speed, and rotation ///////////////
    if(abs(this->hspeed) > 0 || abs(this->vspeed) > 0){
	   this->direction = atan2(this->vspeed, this->hspeed)*180.0/PI;
    }
    this->speed = sqrt((double)this->hspeed*this->hspeed + (double)this->vspeed*this->vspeed);
    this->rotation += this->speed*2;
    if(this->rotation > 360){
	   this->rotation -= 360;
    }


    ////////////// Bounce against walls ///////////////
    _Entity* wall;
    wall = this->checkStaticCollisionWith<Wall>(this->x + this->hspeed, this->y);
    if(  wall != nullptr ){
	   this->hspeed *= -1;
	   horMovementDelay = Player::HOR_MOVEMENT_DELAY_MAX;
    }
    wall = this->checkStaticCollisionWith<Wall>(this->x, this->y + this->vspeed);
    if(  wall != nullptr ){
	   this->vspeed *= -1;
    }
    

    ////////////// Bounce against border walls ///////////////
    this->bounceAgainstBorders();
    

    //////////////// check collision with enemies
    _Entity* enemy = this->checkDynamicCollisionWith<Enemy>(this->x + this->hspeed, this->y);
    if(  enemy != nullptr ){
	   __Game::gameOver();
	   return;
    }
    enemy = this->checkDynamicCollisionWith<Enemy>(this->x, this->y + this->vspeed);
    if(  enemy != nullptr ){
	   __Game::gameOver();
	   return;
    }


    ////////////// Check collision with Skulls ///////////////
    _Entity* skull = this->checkStaticCollisionWith<Skull>(this->x + this->hspeed, this->y);
    if(  skull != nullptr ){
	   this->hspeed *= -1;
	   horMovementDelay = Player::HOR_MOVEMENT_DELAY_MAX;
	   float* otherColor = (dynamic_cast<Skull*>(skull))->getColor();
	   if(G::getCubeTextureFromColor(otherColor) == G::getCubeTextureFromColor(this->color)){
		  __Game::gameOver();
		  return;
	   }
    }
    skull = this->checkStaticCollisionWith<Skull>(this->x, this->y + this->vspeed);
    if(  skull != nullptr ){
	   this->vspeed *= -1;
	   float* otherColor = (dynamic_cast<Skull*>(skull))->getColor();
	   if(G::getCubeTextureFromColor(otherColor) == G::getCubeTextureFromColor(this->color)){
		  __Game::gameOver();
		  return;
	   }
    }

    

    ///////////////// Check change color ///////////////////////
    _Entity* changer = this->checkStaticCollisionWith<ColorChanger>(this->x + this->hspeed, this->y);
    if(  changer != nullptr ){
	   this->hspeed *= -1;
	   horMovementDelay = Player::HOR_MOVEMENT_DELAY_MAX;
	   float* otherColor = (dynamic_cast<ColorChanger*>(changer))->getColor();
	   this->color[0] = otherColor[0];
	   this->color[1] = otherColor[1];
	   this->color[2] = otherColor[2];
    }
    changer = this->checkStaticCollisionWith<ColorChanger>(this->x, this->y + this->vspeed);
    if(  changer != nullptr ){
	   this->vspeed *= -1;
	   float* otherColor = (dynamic_cast<ColorChanger*>(changer))->getColor();
	   this->color[0] = otherColor[0];
	   this->color[1] = otherColor[1];
	   this->color[2] = otherColor[2];
    }



    ////////////// Check collision with colored cubes ///////////////
    _Entity* cube = this->checkStaticCollisionWith<ColoredCube>(this->x + this->hspeed, this->y);
    if(  cube != nullptr ){
	   this->hspeed *= -1;
	   horMovementDelay = Player::HOR_MOVEMENT_DELAY_MAX;
	   float* otherColor = (dynamic_cast<ColoredCube*>(cube))->getColor();
	   if(G::getCubeTextureFromColor(otherColor) == G::getCubeTextureFromColor(this->color)){
		  (dynamic_cast<ColoredCube*>(cube))->createPieces();
		  _Room::currentRoom->removeEntity(cube);
		  ColoredCube::count--;
	   }
    }
    cube = this->checkStaticCollisionWith<ColoredCube>(this->x, this->y + this->vspeed);
    if(  cube != nullptr ){
	   this->vspeed *= -1;
	   float* otherColor = (dynamic_cast<ColoredCube*>(cube))->getColor();
	   if(G::getCubeTextureFromColor(otherColor) == G::getCubeTextureFromColor(this->color)){
		  (dynamic_cast<ColoredCube*>(cube))->createPieces();
		  _Room::currentRoom->removeEntity(cube);
		  ColoredCube::count--;
	   }
    }



    ////////////// Update position ///////////////
    this->x += this->hspeed;
    this->y += this->vspeed;
  
}

void Player::draw(){
    _Entity::draw();
    
    ////////////// Draw ball affected by lighting ///////////////
    glPushMatrix();
    glTranslatef(this->x + TILE_WIDTH/2.0, this->y + TILE_HEIGHT/2.0, TILE_WIDTH/2.0);
    glRotatef(this->direction, 0, 0, 1);
    glRotatef(this->rotation, 0, 1, 0);
    glColor3fv(color);
    glutSolidSphere(0.7*TILE_WIDTH/2.0, 20, 20);
    glPopMatrix();
}