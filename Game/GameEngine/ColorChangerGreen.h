#pragma once
#include "ColorChanger.h"

class ColorChangerGreen : public ColorChanger
{
public:
    ColorChangerGreen(float x, float y);
    void start();
    void step();
    void draw();
};

