#pragma once
#include "_Entity.h"
class _Entity;

class CollisionBox
{
private:
    _Entity* owner;
    float x1;
    float y1;
    float w;
    float h;
    float xoffset;
    float yoffset;

public:
    CollisionBox(_Entity* owner, float x1, float y1, float x2, float y2);
    ~CollisionBox();
    void update(float x, float y);
    void draw();
    bool intersects(CollisionBox* other);
};

