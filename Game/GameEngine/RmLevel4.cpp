#include "_Room.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "declarations.h"
#include "G.h"
#include "RmLevel4.h"
#include "RmLevel5.h"
using namespace std;

// constructor: Called before the room is ready
// can contain any preprocessing or initializations needed for the room
RmLevel4::RmLevel4() : _Room(4, "level4.txt") {
	this->borderWallTexture = G::TEX_WALL3;
	this->floorTexture = G::TEX_GRASS2;
}


// start: Called after the room and all its entities are ready
void RmLevel4::start() {
	_Room::start();

}

// step: Executed 60 times per second
void RmLevel4::step() {
	_Room::step();

}

// draw: Draw everything inside the room
void RmLevel4::draw() {
	_Room::draw();

}

void RmLevel4::win() {
	_Room::gotoRoom(new RmLevel5());
}