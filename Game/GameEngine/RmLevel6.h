#pragma once
#include "_Room.h"

class RmLevel6 : public _Room {
public:
	RmLevel6();
	void start();
	void step();
	void draw();
	void win();
};