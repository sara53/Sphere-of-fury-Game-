#pragma once
#include "Skull.h"

class SkullRed : public Skull
{
public:
    SkullRed(float x, float y);
    void start();
    void step();
    void draw();
};

