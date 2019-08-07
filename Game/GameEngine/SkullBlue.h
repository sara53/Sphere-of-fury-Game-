#pragma once
#include "Skull.h"

class SkullBlue : public Skull
{
public:
    SkullBlue(float x, float y);
    void start();
    void step();
    void draw();
};

