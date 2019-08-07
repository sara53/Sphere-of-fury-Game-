#pragma once
#include "_Entity.h"
#include <Windows.h>
#include <GL\glut.h>

class CubePiece : public _Entity
{
private:
    float gravity;
    float hspeed;
    float vspeed;
    float zspeed;
    float z;
    float color[3];
public:
    CubePiece(float baseX, float baseY, int right, int front, int top, float color[3]);
    void start();
    void step();
    void draw();
};

