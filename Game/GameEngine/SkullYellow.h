#pragma once
#include "Skull.h"

class SkullYellow : public Skull
{
public:
    SkullYellow(float x, float y);
    void start();
    void step();
    void draw();
};

