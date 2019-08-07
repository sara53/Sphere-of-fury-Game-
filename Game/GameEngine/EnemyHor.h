#pragma once
#include "Enemy.h"

class EnemyHor : public Enemy{

public:
    EnemyHor(float x, float y);
    void start();
    void step();
    void draw();
};

