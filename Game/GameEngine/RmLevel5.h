#pragma once
#include "_Room.h"

class RmLevel5 : public _Room {
public:
	RmLevel5();
	void start();
	void step();
	void draw();
	void win();
};