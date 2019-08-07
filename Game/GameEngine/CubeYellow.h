#pragma once
#include "ColoredCube.h"

class CubeYellow : public ColoredCube
{
public:
    CubeYellow(float x, float y);
    void start();
    void step();
    void draw();
};

