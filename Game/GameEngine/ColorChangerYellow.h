#pragma once
#include "ColorChanger.h"

class ColorChangerYellow : public ColorChanger
{
public:
    ColorChangerYellow(float x, float y);
    void start();
    void step();
    void draw();
};

