#pragma once
#include "ColoredCube.h"

class CubeRed : public ColoredCube
{
public:
    CubeRed(float x, float y);
    void start();
    void step();
    void draw();
};

