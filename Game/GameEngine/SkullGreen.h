#pragma once
#include "Skull.h"

class SkullGreen : public Skull
{
public:
    SkullGreen(float x, float y);
    void start();
    void step();
    void draw();
};

