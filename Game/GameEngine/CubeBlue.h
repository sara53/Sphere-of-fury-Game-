#pragma once
#include "ColoredCube.h"

class CubeBlue : public ColoredCube
{
public:
    CubeBlue(float x, float y);
    void start();
    void step();
    void draw();
};

