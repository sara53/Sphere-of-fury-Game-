#pragma once
#include "_Entity.h"
class Enemy : public _Entity
{
private:
    float angle;
public:
    Enemy(float x, float y);
    virtual void start();
    virtual void step();
    virtual void draw();
};

