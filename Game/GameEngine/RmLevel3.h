#pragma once
#include "_Room.h"

class RmLevel3 : public _Room {
public:
	RmLevel3();
	void start();
	void step();
	void draw();
	void win();
};

