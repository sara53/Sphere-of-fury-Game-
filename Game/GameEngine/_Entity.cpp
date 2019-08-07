#include "_Entity.h"
#include <iostream>
#include "declarations.h"
#include "Player.h"
using namespace std;

int _Entity::count = 0;

_Entity::_Entity(float x, float y) {
    _Entity::count ++ ;
    this->x = x;
    this->y = y;
    this->collisionBox = nullptr;
    this->isStatic = false;
    this->collisionSection[0] = (int)y/TILE_HEIGHT;
    this->collisionSection[1] = (int)x/TILE_WIDTH;
}


_Entity::~_Entity(){
    if(this->collisionBox != nullptr){
	   delete this->collisionBox;
    }
}

void _Entity::bounceAgainstBorders(){
    if(this->x + this->hspeed < 0){
	   this->hspeed *= -1;
	   if(this->isInstanceOf<Player>()){
		  Player* player = dynamic_cast<Player*>(this);
		  player->setHorMovementDelay(Player::HOR_MOVEMENT_DELAY_MAX);
	   }
    } else if(this->x + TILE_WIDTH +this->hspeed > _Room::currentRoom->getRoomWidth()*TILE_WIDTH){
	   this->hspeed *= -1;
	   if(this->isInstanceOf<Player>()){
		  Player* player = dynamic_cast<Player*>(this);
		  player->setHorMovementDelay(Player::HOR_MOVEMENT_DELAY_MAX);
	   }
    }
    if(this->y + this->vspeed < 0){
	   this->vspeed *= -1;
    } else if(this->y + TILE_HEIGHT +this->vspeed > _Room::currentRoom->getRoomHeight()*TILE_HEIGHT){
	   this->vspeed *= -1;
    }
}


void _Entity::start(){
    
}

void _Entity::step(){

}

void _Entity::draw(){

}