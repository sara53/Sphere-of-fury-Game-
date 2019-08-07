#include "_Room.h"
#include <Windows.h>
#include <GL\glut.h>
#include <iostream>
#include "declarations.h"
#include "G.h"
#include "RmLevel7.h"
#include "RmLevel1.h"
#include "__Game.h"
using namespace std;

// constructor: Called before the room is ready
// can contain any preprocessing or initializations needed for the room
RmLevel7::RmLevel7() : _Room(7, "level7.txt") {
	this->borderWallTexture = G::TEX_WALL3;
	this->floorTexture = G::TEX_GRASS2;
}


// start: Called after the room and all its entities are ready
void RmLevel7::start() {
	_Room::start();

}

// step: Executed 60 times per second
void RmLevel7::step() {
	_Room::step();

}

// draw: Draw everything inside the room
void RmLevel7::draw() {
    _Room::draw();

}

void RmLevel7::win() {
    __Game::gameWin();
}