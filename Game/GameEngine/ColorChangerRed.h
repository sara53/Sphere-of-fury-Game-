#pragma once
#include "ColorChanger.h"

class ColorChangerRed : public ColorChanger
{
public:
    ColorChangerRed(float x, float y);
    void start();
    void step();
    void draw();
};

