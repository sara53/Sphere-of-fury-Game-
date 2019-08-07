#pragma once
#include <Windows.h>
#include <gl\glut.h>
#include "_Entity.h"

class ColorChanger : public _Entity{
protected:
   float color[3];
   GLuint texture;
public:
    ColorChanger(float x, float y, float r, float g, float b);
    void start();
    void step();
    void draw();
    float* getColor();
};

