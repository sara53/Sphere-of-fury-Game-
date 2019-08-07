#pragma once
#include "ColorChanger.h"

class ColorChangerBlue : public ColorChanger
{
public:
    ColorChangerBlue(float x, float y);
    void start();
    void step();
    void draw();
};

