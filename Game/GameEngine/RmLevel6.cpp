#include "_Room.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "declarations.h"
#include "G.h"
#include "RmLevel6.h"
#include "RmLevel7.h"
using namespace std;

// constructor: Called before the room is ready
// can contain any preprocessing or initializations needed for the room
RmLevel6::RmLevel6() : _Room(6, "level6.txt") {
	this->borderWallTexture = G::TEX_WALL3;
	this->floorTexture = G::TEX_GRASS2;
}


// start: Called after the room and all its entities are ready
void RmLevel6::start() {
	_Room::start();

}

// step: Executed 60 times per second
void RmLevel6::step() {
	_Room::step();

}

// draw: Draw everything inside the room
void RmLevel6::draw() {
	_Room::draw();

}

void RmLevel6::win() {
	_Room::gotoRoom(new RmLevel7());
}