#pragma once
#include "_Room.h"

class RmLevel4 : public _Room {
public:
	RmLevel4();
	void start();
	void step();
	void draw();
	void win();
};