#pragma once
#include "ColoredCube.h"

class CubeGreen : public ColoredCube
{
public:
    CubeGreen(float x, float y);
    void start();
    void step();
    void draw();
};

