#include "RmLevel1.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "Player.h"
#include "declarations.h"
#include "G.h"
#include "Wall.h"
#include "CubeBlue.h"
#include "CubeRed.h"
#include "CubeYellow.h"
#include "CubeGreen.h"
#include "RmLevel2.h"
using namespace std;


// constructor: Called before the room is ready
// can contain any preprocessing or initializations needed for the room
RmLevel1::RmLevel1(): _Room(1, "level1.txt") {
    this->borderWallTexture = G::TEX_WALL3;
    this->floorTexture = G::TEX_GRASS2;
}


// start: Called after the room and all its entities are ready
void RmLevel1::start(){
    _Room::start();
    
}

// step: Executed 60 times per second
void RmLevel1::step(){
    _Room::step();
    
}

// draw: Draw everything inside the room
void RmLevel1::draw(){
    _Room::draw();

    
}

void RmLevel1::win(){
    _Room::gotoRoom(new RmLevel2());
}