#pragma once
#include "CollisionBox.h"
#include "_Room.h"
#include "declarations.h"
class CollisionBox;

class _Entity {
private:
    
protected:

    bool isStatic;
    int collisionSection[2];
    float x;
    float y;
    CollisionBox* collisionBox;
    float hspeed;
    float vspeed;

public:
    static int count;

    _Entity(float x, float y);
    ~_Entity();
    void bounceAgainstBorders();
    virtual void start();
    virtual void step();
    virtual void draw();

    // template functions (defined in this header file)
    template <typename T> bool isInstanceOf();
    template <typename T> _Entity* checkStaticCollisionWith(float xNew, float yNew);
    template <typename T> _Entity* checkDynamicCollisionWith(float xNew, float yNew);
    
    // setters
    inline void setHspeed(float hspeed){this->hspeed = hspeed;}
    inline void setVspeed(float vspeed){this->vspeed = vspeed;}
    inline void reverseHspeed(){this->hspeed *= -1;}
    inline void reverseVspeed(){this->vspeed *= -1;}

    // getters
    inline float getX(){return this->x;}
    inline float getY(){return this->y;}
    inline CollisionBox* getCollisionBox(){return this->collisionBox;}
    inline bool checkStatic(){return this->isStatic;}
    inline int* getCollisionSection(){return this->collisionSection;}
    inline float getHspeed(){return this->hspeed;}
    inline float getVspeed(){return this->vspeed;}

};



////////////////////////////// Template Functions //////////////////////////////////

template <typename T> bool _Entity::isInstanceOf(){
    return (dynamic_cast<T*>(this) != nullptr);
}


template <typename T>
_Entity* _Entity::checkStaticCollisionWith(float xNew, float yNew){
    if (this->collisionBox == nullptr){
	   return nullptr;
    }
    this->collisionBox->update(xNew, yNew);
    int row = (int)yNew/TILE_HEIGHT; 
    int col = (int)xNew/TILE_WIDTH;

    for(int r = row-1; r <= row+1; r++){
	   if(r < 0 || r >= _Room::currentRoom->getRoomHeight()){
		  continue;
	   }
	   for(int c = col-1; c <= col+1; c++){
		  if(c < 0 || c >= _Room::currentRoom->getRoomWidth()){
			 continue;
		  }
		  _Entity* other = _Room::currentRoom->getStaticCollisionMap()[r][c];
		  if(other == nullptr){
			 continue;
		  }
		  if(other == this){
			 continue;
		  }
		  if (other->collisionBox == nullptr) {
			 continue;
		  }
		  if (!other->isInstanceOf<T>()){
			 continue;
		  }
		  if(this->collisionBox->intersects(other->collisionBox)){
			 this->collisionBox->update(this->x, this->y);
			 return other;
		  }
	   }
    }
    
    this->collisionBox->update(this->x, this->y);
    return nullptr;
}


template <typename T>
_Entity* _Entity::checkDynamicCollisionWith(float xNew, float yNew){
    if (this->collisionBox == nullptr){
	   return nullptr;
    }
    this->collisionBox->update(xNew, yNew);

    
    for (unsigned int i=0; i < _Room::currentRoom->getDynamicEntityList().size(); i++){
	   _Entity* other = _Room::currentRoom->getDynamicEntityList().at(i);
	   if(other == this){
		  continue;
	   }
	   if (other->collisionBox == nullptr) {
		  continue;
	   }
	   if (!other->isInstanceOf<T>()){
		  continue;
	   }
	   if(this->collisionBox->intersects(other->collisionBox)){
		  this->collisionBox->update(this->x, this->y);
		  return other;
	   }
    }


    this->collisionBox->update(this->x, this->y);
    return nullptr;
}