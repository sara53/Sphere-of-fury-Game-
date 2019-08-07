#include <iostream>
#include "_Entity.h"
#include "RoomBuilder.h"
#include <string>
#include "_Room.h"
#include "declarations.h"
#include <algorithm>
#include "Player.h"
#include "Wall.h"
#include "CubeBlue.h"
#include "CubeRed.h"
#include "CubeYellow.h"
#include "CubeGreen.h"
#include "ColorChangerBlue.h"
#include "ColorChangerRed.h"
#include "ColorChangerYellow.h"
#include "ColorChangerGreen.h"
#include "SkullRed.h"
#include "SkullGreen.h"
#include "SkullBlue.h"
#include "SkullYellow.h"
#include "RmLevel1.h"
#include "RmLevel2.h"
#include "RmLevel3.h"
#include "RmLevel4.h"
#include "RmLevel5.h"
#include "RmLevel6.h"
#include "RmLevel7.h"
#include "EnemyHor.h"
#include "EnemyVer.h"
#include "EnemyAll.h"
#include "G.h"
#include "__Game.h"
using namespace std;

// static variables definition (possibly giving them initial value)
_Room* _Room::currentRoom = nullptr;
bool _Room::entityRemovedItself = false;


// constructor
_Room::_Room(int roomNumber, char filename[]){
    strcpy_s(this->filename, filename);
    this->currentStaticEntityIndex = 0;
    this->currentDynamicEntityIndex = 0;
    this->borderWallTexture = G::TEX_WALL2;
    this->hasFloor = true;
    this->floorTexture = G::TEX_GRASS;
    ColoredCube::count = 0;
    this->roomNumber = roomNumber;
}

_Room::~_Room(){
    while(this->staticEntityList.size() > 0){
	   this->removeEntity(this->staticEntityList.at(0));
    }
    while(this->dynamicEntityList.size() > 0){
	   this->removeEntity(this->dynamicEntityList.at(0));
    }
    for(int i = 0; i < this->roomHeight; i++){
	   delete [] this->staticCollisionMap[i];
    }
    delete [] this->staticCollisionMap;
}


// initDimensionsAndCollisionSections: Initializes room width and height. After that it initializes the 
// static collision map to represent the collision sections
void _Room::initDimensionsAndCollisionSections(int w, int h){
    this->roomWidth = w;
    this->roomHeight = h;
    this->staticCollisionMap = new _Entity** [h];
    for(int i = 0; i < h; i++){
	   this->staticCollisionMap[i] = new _Entity* [w];
	   for(int j = 0; j < w; j++){
		  this->staticCollisionMap[i][j] = nullptr;
	   }
    }
}


// prepare: This function is called once the room is created and is ready but the entities of the room are not ready yet
// In this functions, the entities are created
// After all entities are created, we invoke the start() function of each entity
// After all entities execute their start() function, we call start() for this room
// it's called from gotoRoom() after the constructor finishes and after the _Room::currentRoom is assigned
void _Room::prepare(){
    RoomBuilder::buildRoom(this->filename);
    this->currentStaticEntityIndex = 0;
    while(this->currentStaticEntityIndex < this->staticEntityList.size()){
	   _Entity* e = this->staticEntityList.at(this->currentStaticEntityIndex);
	   e->start();
	   this->currentStaticEntityIndex ++ ;
    }
    this->currentDynamicEntityIndex = 0;
    while(this->currentDynamicEntityIndex < this->dynamicEntityList.size()){
	   _Entity* e = this->dynamicEntityList.at(this->currentDynamicEntityIndex);
	   e->start();
	   this->currentDynamicEntityIndex ++ ;
    }
    this->start();
}


// start: Executed when this room and all its entities are ready
void _Room::start(){
    __Game::isGameOver = false;
}

// step: This function contains the main logic of the Room
// it's executed at a fixed FPS rate (which is equal to the FPS static constant of the __Game class)
void _Room::step(){
    this->currentStaticEntityIndex = 0;
    while(this->currentStaticEntityIndex < this->staticEntityList.size()){
	   _Entity* e = this->staticEntityList.at(this->currentStaticEntityIndex);
	   _Room::entityRemovedItself = false;
	   e->step();
	   if(!_Room::entityRemovedItself){
		  CollisionBox* cbox = e->getCollisionBox(); 
		  if(cbox != nullptr){
			 cbox->update(e->getX(), e->getY());
		  }
	   }
	   this->currentStaticEntityIndex ++ ;
    }
    this->currentDynamicEntityIndex = 0;
    while(this->currentDynamicEntityIndex < this->dynamicEntityList.size()){
	   _Entity* e = this->dynamicEntityList.at(this->currentDynamicEntityIndex);
	   _Room::entityRemovedItself = false;
	   e->step();
	   if(!_Room::entityRemovedItself){
		  CollisionBox* cbox = e->getCollisionBox(); 
		  if(cbox != nullptr){
			 cbox->update(e->getX(), e->getY());
		  }
	   }
	   this->currentDynamicEntityIndex ++ ;
    }
    // check win
    if(ColoredCube::count == 0){
	   this->win();
    }
}


// draw: Draw eerything inside the room
void _Room::draw(){

    //**************************** draw floor ****************************//
    if(this->hasFloor){
	   /////////// Floor and texture dimensions ///////////
	   float wdth = this->roomWidth * TILE_WIDTH;
	   float height = this->roomHeight * TILE_HEIGHT;
	   float texWidth = 50;
	   float texHeight = 50;

	   ////////// Draw Floor //////////////////////////////
	   glDisable(GL_LIGHTING);
	   G::beginTexture(this->floorTexture);
	   glBegin(GL_QUADS);
		  glTexCoord2f(0, 0);
		  glVertex3f(0, 0, 0);
		  glTexCoord2f(wdth/texWidth, 0);
		  glVertex3f(wdth, 0, 0);
		  glTexCoord2f(wdth/texWidth, height/texHeight);
		  glVertex3f(wdth, height, 0);
		  glTexCoord2f(0, height/texHeight);
		  glVertex3f(0, height, 0);
	   glEnd();
	   G::endTexture();
	   glEnable(GL_LIGHTING);
    }

    //*************************** draw border walls *****************************//
    this->drawBorderWalls();

    //*************************** draw entities *****************************//
    this->currentStaticEntityIndex = 0;
    while(this->currentStaticEntityIndex < this->staticEntityList.size()){
	   _Entity* e = this->staticEntityList.at(this->currentStaticEntityIndex);
	   e->draw();
	   if(SHOW_COLLISION_BOXES == 1){
		  CollisionBox* cbox = e->getCollisionBox(); 
		  if(cbox != nullptr){
			 cbox->draw();
		  }
	   }
	   this->currentStaticEntityIndex ++ ;
    }
    this->currentDynamicEntityIndex = 0;
    while(this->currentDynamicEntityIndex < this->dynamicEntityList.size()){
	   _Entity* e = this->dynamicEntityList.at(this->currentDynamicEntityIndex);
	   e->draw();
	   if(SHOW_COLLISION_BOXES == 1){
		  CollisionBox* cbox = e->getCollisionBox(); 
		  if(cbox != nullptr){
			 cbox->draw();
		  }
	   }
	   this->currentDynamicEntityIndex ++ ;
    }
}


void _Room::drawBorderWalls(){
    //*************************** draw border walls *****************************//
    // side = 0: north, 1: east, 2: south: 3: west
    for(int side = 0; side < 4; side++){
	   if(side == 0){
		  glDisable(GL_LIGHTING);
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(-TILE_WIDTH, this->roomHeight*TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, this->roomHeight*TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, this->roomHeight*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f(-TILE_WIDTH, this->roomHeight*TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(-TILE_WIDTH, this->roomHeight*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, this->roomHeight*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f(-TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(-TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f(-TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  glEnable(GL_LIGHTING);
	   } else if(side == 1){
		  glDisable(GL_LIGHTING);
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(this->roomWidth*TILE_WIDTH, -TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f(this->roomWidth*TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f(this->roomWidth*TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f(this->roomWidth*TILE_WIDTH, -TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(this->roomWidth*TILE_WIDTH, -TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f(this->roomWidth*TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, -TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, -TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, -TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  glEnable(GL_LIGHTING);
	   } else if(side == 2){
		  glDisable(GL_LIGHTING);
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(-TILE_WIDTH, 0, 0);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, 0, 0);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, 0, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f(-TILE_WIDTH, 0, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(-TILE_WIDTH, 0, TILE_HEIGHT);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, 0, TILE_HEIGHT);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, -TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f(-TILE_WIDTH, -TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(-TILE_WIDTH, -TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, -TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f((this->roomWidth+1)*TILE_WIDTH, -TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f(-TILE_WIDTH, -TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  glEnable(GL_LIGHTING);
	   } else if(side == 3){
		  glDisable(GL_LIGHTING);
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(0, -TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f(0, (this->roomHeight+1)*TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f(0, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f(0, -TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(0, -TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f(0, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f(-TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f(-TILE_WIDTH, -TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  G::beginTexture(this->borderWallTexture);
		  glBegin(GL_QUADS);
			 glTexCoord2f(0, 0);
			 glVertex3f(-TILE_WIDTH, -TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 0);
			 glVertex3f(-TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, 0);
			 glTexCoord2f(this->roomWidth+2, 1);
			 glVertex3f(-TILE_WIDTH, (this->roomHeight+1)*TILE_HEIGHT, TILE_HEIGHT);
			 glTexCoord2f(0, 1);
			 glVertex3f(-TILE_WIDTH, -TILE_HEIGHT, TILE_HEIGHT);
		  glEnd();
		  G::endTexture();
		  glEnable(GL_LIGHTING);
	   }
    }
}

void _Room::win(){

}

void _Room::restart(){
    switch(this->roomNumber){
	   case 1:
		  _Room::gotoRoom(new RmLevel1());
		  break;
	   case 2:
		  _Room::gotoRoom(new RmLevel2());
		  break;
	   case 3:
		   _Room::gotoRoom(new RmLevel3());
		   break;
	   case 4:
		   _Room::gotoRoom(new RmLevel4());
		   break;
	   case 5:
		   _Room::gotoRoom(new RmLevel5());
		   break;
	   case 6:
		   _Room::gotoRoom(new RmLevel6());
		   break;
	   case 7:
		   _Room::gotoRoom(new RmLevel7());
		   break;
    }
}

// addEntity: add entity to this room
void _Room::addEntity(_Entity* newEntity){
    if(newEntity->checkStatic()){
	   this->staticEntityList.push_back(newEntity);
	   int i = newEntity->getCollisionSection()[0];
	   int j = newEntity->getCollisionSection()[1];
	   this->staticCollisionMap[i][j] = newEntity;
    } else {
	   this->dynamicEntityList.push_back(newEntity);
    }
}


// removeEntity: remove an entity from this room
void _Room::removeEntity(_Entity* e){
    if(e->checkStatic()){
	   int i = e->getCollisionSection()[0];
	   int j = e->getCollisionSection()[1];
	   this->staticCollisionMap[i][j] = nullptr;
	   unsigned int pos = std::find(this->staticEntityList.begin(), 
		  this->staticEntityList.end(), e) - this->staticEntityList.begin();
	   this->staticEntityList.erase(this->staticEntityList.begin()+pos);
	   if(pos == this->currentStaticEntityIndex){
		  _Room::entityRemovedItself = true;
	   }
	   if(pos <= this->currentStaticEntityIndex){
		  this->currentStaticEntityIndex--;
	   }
	   
    }
    else {
	   unsigned int pos = std::find(this->dynamicEntityList.begin(), 
		  this->dynamicEntityList.end(), e) - this->dynamicEntityList.begin();
	   this->dynamicEntityList.erase(this->dynamicEntityList.begin()+pos);
	   if(pos == this->currentDynamicEntityIndex){
		  _Room::entityRemovedItself = true;
	   }
	   if(pos <= this->currentDynamicEntityIndex){
		  this->currentDynamicEntityIndex--;
	   }
	   
    }
    delete e;
}


// createEntityFromChar: You may override this function in derived room classes in order 
// to map the text file symbols to their corresponding entity classes
// createEntityFromChar: maps the characters of the room text file to game entities
void _Room::createEntityFromChar(char cha, float x, float y){
    

    //----------------- player ----------------------//
    if(cha == 'o'){
	   _Room::currentRoom->addEntity(new Player(x, y));
    }
    


    //---------------- obstacles -------------------//
    if(cha == 'x'){
	   _Room::currentRoom->addEntity(new Wall(x, y));
    }
    

    //---------------- colored cubes -------------------//
    if(cha == 'r'){
	   _Room::currentRoom->addEntity(new CubeRed(x, y));
    }
    if(cha == 'g'){
	   _Room::currentRoom->addEntity(new CubeGreen(x, y));
    }
    if(cha == 'b'){
	   _Room::currentRoom->addEntity(new CubeBlue(x, y));
    }
    if(cha == 'y'){
	   _Room::currentRoom->addEntity(new CubeYellow(x, y));
    }
    
    //---------------- color changers -------------------//
    if(cha == 'R'){
	   _Room::currentRoom->addEntity(new ColorChangerRed(x, y));
    }
    if(cha == 'G'){
	   _Room::currentRoom->addEntity(new ColorChangerGreen(x, y));
    }
    if(cha == 'B'){
	   _Room::currentRoom->addEntity(new ColorChangerBlue(x, y));
    }
    if(cha == 'Y'){
	   _Room::currentRoom->addEntity(new ColorChangerYellow(x, y));
    }


    //---------------- skulls -------------------//
    if(cha == '1'){
	   _Room::currentRoom->addEntity(new SkullRed(x, y));
    }
    if(cha == '2'){
	   _Room::currentRoom->addEntity(new SkullGreen(x, y));
    }
    if(cha == '3'){
	   _Room::currentRoom->addEntity(new SkullBlue(x, y));
    }
    if(cha == '4'){
	   _Room::currentRoom->addEntity(new SkullYellow(x, y));
    }
    

    //---------------- enemies -------------------//
    if(cha == 'e'){
	   _Room::currentRoom->addEntity(new Enemy(x, y));
    }
    if(cha == 'h'){
	   _Room::currentRoom->addEntity(new EnemyHor(x, y));
    }
    if(cha == 'v'){
	   _Room::currentRoom->addEntity(new EnemyVer(x, y));
    }
    if(cha == 'a'){
	   _Room::currentRoom->addEntity(new EnemyAll(x, y));
    }
}


// gotoRoom: Call this function to go to a new room
void _Room::gotoRoom(_Room* newRoom){
    delete _Room::currentRoom;
    _Room::currentRoom = newRoom;
    newRoom->prepare();

}
