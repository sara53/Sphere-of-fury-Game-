#pragma once
#include "_Room.h"

class RmLevel7 : public _Room {
public:
	RmLevel7();
	void start();
	void step();
	void draw();
	void win();
};