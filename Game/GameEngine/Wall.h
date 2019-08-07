#pragma once
#include "Obstacles.h"

class Wall : public Obstacles
{
public:
    Wall(float x, float y);
    void start();
    void step();
    void draw();
};

