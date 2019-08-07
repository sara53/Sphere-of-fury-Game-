#include "RmLevel2.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "declarations.h"
#include "G.h"
#include "RmLevel3.h"
using namespace std;

// constructor: Called before the room is ready
// can contain any preprocessing or initializations needed for the room
RmLevel2::RmLevel2(): _Room(2, "level2.txt") {
    this->borderWallTexture = G::TEX_WALL3;
    this->floorTexture = G::TEX_GRASS2;
}


// start: Called after the room and all its entities are ready
void RmLevel2::start(){
    _Room::start();
    
}

// step: Executed 60 times per second
void RmLevel2::step(){
    _Room::step();
    
}

// draw: Draw everything inside the room
void RmLevel2::draw(){
    _Room::draw();
    
}

void RmLevel2::win(){
    cout << "win2" << endl;
    _Room::gotoRoom(new RmLevel3());
}