#pragma once
#include "_Room.h"

class RmLevel1 : public _Room {
public:
    RmLevel1();
    void start();
    void step();
    void draw();
    void win();
};

