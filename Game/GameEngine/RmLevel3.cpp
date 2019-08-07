#include "_Room.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "declarations.h"
#include "G.h"
#include "RmLevel3.h"
#include "RmLevel4.h"
using namespace std;

// constructor: Called before the room is ready
// can contain any preprocessing or initializations needed for the room
RmLevel3::RmLevel3() : _Room(3, "level3.txt") {
	this->borderWallTexture = G::TEX_WALL3;
	this->floorTexture = G::TEX_GRASS2;
}


// start: Called after the room and all its entities are ready
void RmLevel3::start() {
	_Room::start();

}

// step: Executed 60 times per second
void RmLevel3::step() {
	_Room::step();

}

// draw: Draw everything inside the room
void RmLevel3::draw() {
	_Room::draw();

}

void RmLevel3::win() {
	_Room::gotoRoom(new RmLevel4());
}