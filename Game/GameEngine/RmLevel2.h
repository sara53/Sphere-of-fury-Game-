#pragma once
#include "_Room.h"

class RmLevel2 : public _Room {
public:
    RmLevel2();
    void start();
    void step();
    void draw();
    void win();
};

